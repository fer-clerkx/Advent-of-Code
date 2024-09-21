#ifndef _PUZZLE10_H
#define _PUZZLE10_H

typedef struct {
	enum t_inst {NOOP, ADDX} inst;
	int oper;
} t_instruction;

void printPuzzle10(void);
void parseInput10(const char *FILENAME, t_instruction *program);
int solvePuzzle10A(t_instruction *program);
void solvePuzzle10B(t_instruction *program);

#endif //_PUZZLE10_H