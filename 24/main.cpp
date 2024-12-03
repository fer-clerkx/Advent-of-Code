#include "main.h"
#include <string>

int main(int argc, char **argv) {
    int day = argc > 1 ? std::stoi(argv[1]) : 3;
    puzzleBase* puzzle;
    switch (day) {
    case 1:
        puzzle = new puzzle01();
        break;
    case 2:
        puzzle = new puzzle02();
        break;
    case 3:
        puzzle = new puzzle03();
        break;
    }
    puzzle->printSolutionA();
    puzzle->printSolutionB();
    return 0;
}
