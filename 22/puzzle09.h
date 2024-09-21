#ifndef _PUZZLE09_H
#define _PUZZLE09_H

typedef struct {
	enum t_direction {UP, DOWN, RIGHT, LEFT} direction;
	int steps;
} t_motion;

void printPuzzle09(void);
void parseInput09(const char *FILENAME, t_motion *motions);
int solvePuzzle09A(t_motion *motions);
int solvePuzzle09B(t_motion *motions);

#endif //_PUZZLE09_H