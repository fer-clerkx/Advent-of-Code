#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#define INPUT_FILE "24/input/input01.txt"

int main() {
    std::ifstream inputFile(INPUT_FILE);
    size_t inputSize = 0;
    char line[256];
    while (inputFile.getline(line, 256, '\n')) {inputSize++;}
    inputFile.close();
    inputFile.open(INPUT_FILE);

    std::vector<int> leftList, rightList;
    leftList.reserve(inputSize);
    rightList.reserve(inputSize);
    int leftNumber, rightNumber;
    while (inputFile >> leftNumber >> rightNumber) {
        leftList.push_back(leftNumber);
        rightList.push_back(rightNumber);
    }

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    int sum = 0;
    for (int i = 0; i < inputSize; i++)
        sum += std::abs(leftList[i] - rightList[i]);
    std::cout << "Solution A: " << sum << '\n';

    return 0;
}
