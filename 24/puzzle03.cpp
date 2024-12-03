#include "puzzle03.h"
#include <string>
#include <fstream>
#include <regex>
#include <utility>

#define INPUT_FILE "input/input03.txt"

puzzle03::puzzle03() {
    ignoreMultiplication = false;
}

int puzzle03::getSolutionA() {
    parseInput();
    std::smatch instructionMatch;
    int solution = 0;
    while (findInstruction(instructionMatch)) {
        solution += executeInstruction(instructionMatch);
        memory = instructionMatch.suffix();
    }
    return solution;
}

int puzzle03::getSolutionB() {
    parseInput();
    std::smatch instructionMatch;
    int solution = 0;
    while (findInstruction(instructionMatch)) {
        int incrementValue = executeInstruction(instructionMatch);
        solution += (ignoreMultiplication) ? 0 : incrementValue;
        memory = instructionMatch.suffix();
    }
    return solution;
}

void puzzle03::parseInput() {
    std::ifstream inputFile(INPUT_FILE);
    size_t inputSize = 0;
    while (inputFile.ignore(256))
        inputSize += inputFile.gcount();
    inputFile.close();
    inputFile.open(INPUT_FILE);

    memory.reserve(inputSize);
    char buff[256];
    while (inputFile.get(buff, 256, EOF))
        memory.append(buff);
}

bool puzzle03::findInstruction(std::smatch& match) {
    std::regex instructionRegex("mul\\((\\d+),(\\d+)\\)|do(n't)?\\(\\)");
    return std::regex_search(memory, match, instructionRegex);
}

int puzzle03::executeInstruction(std::smatch& instructionMatch) {
    int incrementValue = 0;
    switch (instructionMatch.str(0)[2]) {
    case 'l': {
        int leftValue = std::stoi(instructionMatch.str(1));
        int rightValue = std::stoi(instructionMatch.str(2));
        incrementValue = leftValue * rightValue;
        break;
    }
    case '(':
        ignoreMultiplication = false;
        break;
    case 'n':
        ignoreMultiplication = true;
        break;
    }
    return incrementValue;
}
