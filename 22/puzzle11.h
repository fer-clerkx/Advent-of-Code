#ifndef _PUZZLE11_H
#define _PUZZLE11_H

typedef struct {
	long *items;
	int numItems;
	enum t_operation {ADD = '+', MULT = '*'} operator;
	int operand;
	int test_operand;
	int monkeyTrue;
	int monkeyFalse;
} t_monkey;

void printPuzzle11(void);
void parseInput11(const char *FILENAME, t_monkey *monkeys);
int solvePuzzle11A(t_monkey *monkeys);
long solvePuzzle11B(t_monkey *monkeys);
int comp11(const void *a, const void *b);

#endif //_PUZZLE11_H