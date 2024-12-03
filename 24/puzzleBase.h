#ifndef _PUZZLE_BASE
#define _PUZZLE_BASE

class puzzleBase {
public:
    void printSolutionA();
    void printSolutionB();
private:
    virtual int getSolutionA() = 0;
    virtual int getSolutionB() = 0;
};

#endif  // _PUZZLE_BASE