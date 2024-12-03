#include "puzzleBase.h"
#include <vector>

class puzzle02 : public puzzleBase {
private:
    int getSolutionA();
    int getSolutionB();
    void parseInput(std::vector<std::vector<int>>& reportList);
    bool checkReport(const std::vector<int>& report);
    bool checkReportWithBadLevel(const std::vector<int>& report);
    bool checkWindow(std::vector<int>::const_iterator it);
};