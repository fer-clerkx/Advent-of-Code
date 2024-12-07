#include "puzzleBase.h"
#include <vector>
#include <string>

class puzzle04 : public puzzleBase {
public:
    puzzle04();

private:
    int getSolutionA();
    int getSolutionB();
    void parseInput();
    int checkXMAS(int row, int col);
    bool checkXMASRecursive(int row, int col, int rowIncr, int colIncr,
                            std::string::const_iterator wordIter);
    bool checkMAS(int row, int col);

    std::vector<std::string> input;
    const std::string word = "XMAS";
};
