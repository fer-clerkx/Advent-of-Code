class puzzleBase {
public:
    void printSolutionA();
    void printSolutionB();
private:
    virtual int getSolutionA() = 0;
    virtual int getSolutionB() = 0;
};