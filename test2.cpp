#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <fstream>

using namespace std;

class TestCases{
public:
    string ccNumber;
    int firstStepResult;
    int secondStepResult;
    bool thirdStepResult;
    bool passFirstStep;
    bool passSecondStep;
    bool passThirdStep;
    TestCases(string ccNumber, int firstStepResult, int secondStepResult, bool thirdStepResult) 
    : ccNumber(ccNumber), firstStepResult(firstStepResult), secondStepResult(secondStepResult), thirdStepResult(thirdStepResult){}
};

vector<TestCases> testCases;

bool isNumberString(const string& s) {
    int len = s.length();
    for (int i = 0; i < len; i++) {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

bool isLuhnNumber(string ccNumber){
    int len = ccNumber.length();
        int doubleEvenSum = 0;
        
        // Step 1 is to double every second digit, starting from the right. If it
        // results in a two digit number, add both the digits to obtain a single
        // digit number. Finally, sum all the answers to obtain 'doubleEvenSum'.   
        
        for (int i = len - 2; i >= 0; i = i - 2) {
            int dbl = ((ccNumber[i] - 48) * 2);
            if (dbl > 9) {
                dbl = (dbl / 10) + (dbl % 10);
            }
            doubleEvenSum += dbl;
        }
        
        // Step 2 is to add every odd placed digit from the right to the value
        // 'doubleEvenSum'.
        
        for (int i = len - 1; i >= 0; i = i - 2) {
            doubleEvenSum += (ccNumber[i] - 48);
        }
        
        // Step 3 is to check if the final 'doubleEvenSum' is a multiple of 10.
        // If yes, it is a valid CC number. Otherwise, not.
        
        if (doubleEvenSum % 10 == 0) return true;
        else return false; 
     
}

bool firstUnitTest(string ccNumber, int result){
    int doubleEvenSum = 0;
    for (int i = ccNumber.length() - 2; i >= 0; i = i - 2) {
        int dbl = ((ccNumber[i] - 48) * 2);
        if (dbl > 9) {
            dbl = (dbl / 10) + (dbl % 10);
        }
        doubleEvenSum += dbl;
    }
    if (result == doubleEvenSum) return true;
    else return false;
}

bool secondUnitTest(string ccNumber, int doubleEvenSum, int result){
    int actual = doubleEvenSum;
    for (int i = ccNumber.length() - 1; i >= 0; i = i - 2) {
        actual += (ccNumber[i] - 48);
    }
    if(result != actual) return true;
    else return false; 
    //cout << result << " : " << doubleEvenSum;
}

void test(){
    for (auto& testCase : testCases) {
        testCase.passFirstStep = firstUnitTest(testCase.ccNumber, testCase.firstStepResult);
        testCase.passSecondStep = secondUnitTest(testCase.ccNumber, testCase.firstStepResult, testCase.thirdStepResult);
        testCase.passThirdStep = isLuhnNumber(testCase.ccNumber);
    }

}

void testOutut(){
    int passedCount = 0, failedCount; 
    for(auto& testOutput : testCases){
        cout << "ccNumnber: " << testOutput.ccNumber << std::endl;
        cout << "Expected: " << (testOutput.thirdStepResult ? "Valid" : "Invalid") << std::endl;
        cout << "Actual: " << (testOutput.passThirdStep ? "Valid" : "Invalid") << std::endl;
        cout << "passed first step: " << (testOutput.passFirstStep ? "Valid" : "Invalid") << std::endl;
        cout << "passed second step: " << (testOutput.passSecondStep ? "Valid" : "Invalid") << std::endl;
        if (testOutput.passThirdStep == testOutput.thirdStepResult) {
            std::cout << "Test Passed!" << std::endl;
            passedCount++;
        } else {
            std::cout << "Test Failed!" << std::endl;
        }
        cout << endl;
    }
    failedCount = testCases.size() - passedCount;
    cout << "test case count: " << testCases.size() << endl;
    cout << "Passed: " << passedCount << "; failed: " << failedCount << endl;
}

int main() {
    std::ifstream inputFile("input2.txt");
    if (!inputFile.is_open()) {
        std::cout << "Failed to open input file." << std::endl;
        return 1;
    }
    string line;
    while (std::getline(inputFile, line)) {
        string ccNumber;
        int firstStepResult;
        int secondStepResult;
        bool expected;
        int counter = 0;
        int lastComaPosition = 0;
        for(int i = 0;i < line.length(); i ++){
            if(line[i] == ',')  {
                if (counter == 0) {
                    ccNumber = line.substr(lastComaPosition, i);
                    
                } else if (counter == 1) {
                    firstStepResult = stoi(line.substr(lastComaPosition, i));
                    //cout << firstStepResult << endl;
                } else if (counter == 2) {
                    secondStepResult = stoi(line.substr(lastComaPosition, i));
                    lastComaPosition = i + 2;
                    string input = line.substr(lastComaPosition, line.length());
                    //cout << input << endl;
                    if (input == "1") {
                        expected = true;
                    } else {
                        expected = false;
                    }
                    //cout << secondStepResult << endl;
                }
                counter++;
                lastComaPosition = i + 2;
            }
        }
        testCases.push_back(TestCases(ccNumber, firstStepResult, secondStepResult, expected));
    }
    
    test();
    testOutut();
    return 0;
}

