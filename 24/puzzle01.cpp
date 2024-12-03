#include "puzzle01.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <unordered_map>

#define INPUT_FILE "input/input01.txt"

int puzzle01::getSolutionA() {
    std::vector<int> leftList, rightList;
    parseInput(leftList, rightList);

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    int solutionA = 0;
    for (int i = 0; i < leftList.size(); i++)
        solutionA += std::abs(leftList[i] - rightList[i]);
    return solutionA;
}

int puzzle01::getSolutionB() {
    std::vector<int> leftList, rightList;
    parseInput(leftList, rightList);

    std::unordered_map<int, int> rightMap;
    for (int &elem : rightList)
        rightMap[elem] += 1;

    int solutionB = 0;
    for (int leftNumber : leftList)
        solutionB += leftNumber * rightMap[leftNumber];
    return solutionB;
}

void puzzle01::parseInput(std::vector<int>& leftList, std::vector<int>& rightList) {
    std::ifstream inputFile(INPUT_FILE);
    size_t inputSize = 0;
    char line[256];
    while (inputFile.getline(line, 256, '\n')) {inputSize++;}
    inputFile.close();
    inputFile.open(INPUT_FILE);

    leftList.reserve(inputSize);
    rightList.reserve(inputSize);
    int leftNumber, rightNumber;
    while (inputFile >> leftNumber >> rightNumber) {
        leftList.push_back(leftNumber);
        rightList.push_back(rightNumber);
    }
}
