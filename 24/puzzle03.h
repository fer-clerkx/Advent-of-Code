#include "puzzleBase.h"
#include <string>
#include <regex>

class puzzle03 : public puzzleBase {
public:
    puzzle03();

private:
    int getSolutionA();
    int getSolutionB();
    void parseInput();
    bool findInstruction(std::smatch& match);
    int executeInstruction(std::smatch& instructionMatch);

    std::string memory;
    bool ignoreMultiplication;
};
