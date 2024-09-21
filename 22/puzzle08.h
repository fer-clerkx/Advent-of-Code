#ifndef _PUZZLE08_H
#define _PUZZLE08_H

typedef struct {
	unsigned char left, right, up, down;
} t_scenicScore;

void printPuzzle08(void);
void parseInput08(const char *FILENAME, unsigned char **trees);
int solvePuzzle08A(unsigned char **trees);
int solvePuzzle08B(unsigned char **trees);
void free08(unsigned char **trees);

#endif //_PUZZLE08_H