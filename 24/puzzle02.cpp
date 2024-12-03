#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

void parseInput(std::vector<std::vector<int>>& reportList);
int getSolutionA(std::vector<std::vector<int>>& reportList);
int getSolutionB(std::vector<std::vector<int>>& reportList);
bool checkReport(const std::vector<int>& report);
bool checkReportWithBadLevel(const std::vector<int>& report);
bool checkWindow(std::vector<int>::const_iterator it);

#define INPUT_FILE "24/input/input02.txt"

int main() {
    std::vector<std::vector<int>> reportList;
    parseInput(reportList);

    std::cout << "Solution A: " << getSolutionA(reportList) << '\n';
    std::cout << "Solution B: " << getSolutionB(reportList) << '\n';

    return 0;
}

int getSolutionA(std::vector<std::vector<int>>& reportList) {
    int solutionA = 0;
    for (const std::vector<int>& report : reportList) {
        solutionA += checkReport(report);
    }
    return solutionA;
}

int getSolutionB(std::vector<std::vector<int>>& reportList) {
    int solutionB = 0;
    for (const std::vector<int>& report : reportList) {
        solutionB += checkReportWithBadLevel(report);
    }
    return solutionB;
}

bool checkReport(const std::vector<int>& report) {
    for (auto it = report.begin(); it < report.end() - 2; it++)
        if (!checkWindow(it))
            return false;
    return true;
}

bool checkReportWithBadLevel(const std::vector<int>& report) {
    bool safe = true;
    for (int i = 0; i < report.size() - 2; i++) {
        if (checkWindow(report.begin() + i))
            continue;
        for (int j = 0; j < 3; j++) {
            std::vector<int> reportCopy = report;
            reportCopy.erase(reportCopy.begin() + i + j);
            if (checkReport(reportCopy))
                return true;
        }
        return false;
    }
    return true;
}

bool checkWindow(std::vector<int>::const_iterator it) {
    int diff12 = *it - *std::next(it);
    int diff23 = *std::next(it) - *std::next(it, 2);
    if ((diff12 ^ diff23) < 0)  // Check if two numbers have different sign
        return false;
    if (std::abs(diff12) > 3 || std::abs(diff23) > 3)
        return false;
    if (diff12 == 0 || diff23 == 0)
        return false;
    return true;
}

void parseInput(std::vector<std::vector<int>>& reportList) {
    std::ifstream inputFile(INPUT_FILE);
    size_t inputSize = 0;
    char line[256];
    while (inputFile.getline(line, 256, '\n')) {inputSize++;}
    inputFile.close();
    inputFile.open(INPUT_FILE);

    reportList.resize(inputSize);
    for (auto& report : reportList) {
        while (inputFile.peek() != '\n') {
            int level;
            inputFile >> level;
            report.push_back(level);
        }
        inputFile.ignore(1);
    }
}
