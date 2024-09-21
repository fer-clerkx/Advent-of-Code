#ifndef _PUZZLE05_H
#define _PUZZLE05_H

typedef struct {
	int amount, src, dest;
} t_procedure;

void printPuzzle05(void);
void parseInput05(const char *FILENAME, char **stacks, int *stackDepth, t_procedure *procedures);
void solvePuzzle05A(char **stacks, int *stackDepth, const t_procedure *procedures, char *topCrates);
void solvePuzzle05B(char **stacks, int *stackDepth, const t_procedure *procedures, char *topCrates);

#endif //_PUZZLE05_H