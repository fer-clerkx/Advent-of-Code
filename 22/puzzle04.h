#ifndef _PUZZLE04_H
#define _PUZZLE04_H

typedef struct {
	int lower[2];
	int upper[2];
} t_pair_assign;

void printPuzzle04(void);
void parseInput04(const char *FILENAME, t_pair_assign *assignments);
int solvePuzzle04A(const t_pair_assign *assignments);
int solvePuzzle04B(const t_pair_assign *assignments);

#endif //_PUZZLE04_H