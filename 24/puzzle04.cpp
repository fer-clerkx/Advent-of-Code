#include "puzzle04.h"
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

#define INPUT_FILE "input/input04.txt"

puzzle04::puzzle04() {
    parseInput();
}

int puzzle04::getSolutionA() {
    int solution = 0;
    for (int row = 0; row < input.size(); row++)
        for (int col = 0; col < input[row].size(); col++)
            solution += checkXMAS(row, col);
    return solution;
}

int puzzle04::getSolutionB() {
    int solution = 0;
    for (int row = 1; row < input.size()-1; row++)
        for (int col = 1; col < input[0].size()-1; col++)
            solution += checkMAS(row, col);
    return solution;
}

void puzzle04::parseInput() {
    std::ifstream inputFile(INPUT_FILE);
    std::string inputLine;
    while (std::getline(inputFile, inputLine, '\n'))
        input.push_back (inputLine);
}

int puzzle04::checkXMAS(int row, int col) {
    if (input[row][col] != word[0])
        return false;
    int correctWords = 0;
    for (int rowIncrement = -1; rowIncrement < 2; rowIncrement++) {
        for (int colIncrement = -1; colIncrement < 2; colIncrement++) {
            if (rowIncrement == 0 & colIncrement == 0)
                continue;
            correctWords += checkXMASRecursive(row, col, rowIncrement,
                                               colIncrement, word.begin()+1);
        }
    }
    return correctWords;
}

bool puzzle04::checkXMASRecursive(int row, int col, int rowIncr, int colIncr,
                                  std::string::const_iterator wordIter) {
    int newRow = row+rowIncr;
    int newCol = col+colIncr;
    if (newRow < 0 | newRow >= input.size() | newCol < 0
                                            | newCol >= input[newRow].size())
        return false;
    if (input[newRow][newCol] != *wordIter)
        return false;
    if (wordIter == word.end()-1)
        return true;
    if(checkXMASRecursive(newRow, newCol, rowIncr, colIncr, std::next(wordIter)))
        return true;
    return false;
}

bool puzzle04::checkMAS(int row, int col) {
    if (input[row][col] != 'A')
        return false;

    char topLeft = input[row-1][col-1];
    if (topLeft != 'M' & topLeft != 'S')
        return false;
    if (input[row+1][col+1] != (topLeft == 'M' ? 'S' : 'M'))
        return false;

    char topRight = input[row-1][col+1];
    if (topRight != 'M' & topRight != 'S')
        return false;
    if (input[row+1][col-1] != (topRight == 'M' ? 'S' : 'M'))
        return false;

    return true;
}