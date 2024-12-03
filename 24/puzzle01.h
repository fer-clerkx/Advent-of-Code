#include "puzzleBase.h"
#include <vector>

class puzzle01 : public puzzleBase {
private:
    int getSolutionA();
    int getSolutionB();
    void parseInput(std::vector<int>& leftList, std::vector<int>& rightList);
};