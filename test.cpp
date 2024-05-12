#include <iostream>
#include <fstream>
#include <string>
#include "luhn.h"

using namespace std;

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cout << "Failed to open input file." << std::endl;
        return 1;
    }

    std::string line;
    std::string ccNumber;
    std::string expectedResult;
    int testCount = 0;
    int successCount = 0;

    while (std::getline(inputFile, line)) {
        std::size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) {
            std::cout << "Invalid input format: " << line << std::endl;
            continue;
        }

        ccNumber = line.substr(0, commaPos);
        expectedResult = line.substr(commaPos + 1);

        bool expected = (expectedResult == "0");

        bool actual = luhnAlgo(ccNumber);

        std::cout << "CC Number: " << ccNumber << std::endl;
        std::cout << "Expected: " << (expected ? "Valid" : "Invalid") << std::endl;
        std::cout << "Actual: " << (actual ? "Valid" : "Invalid") << std::endl;

        if (actual == expected) {
            std::cout << "Test Passed!" << std::endl;
            successCount++;
        } else {
            std::cout << "Test Failed!" << std::endl;
        }

        std::cout << std::endl;

        testCount++;
    }

    inputFile.close();

    std::cout << "Total tests: " << testCount << std::endl;
    std::cout << "Tests passed: " << successCount << std::endl;
    std::cout << "Tests failed: " << (testCount - successCount) << std::endl;

    return 0;
}