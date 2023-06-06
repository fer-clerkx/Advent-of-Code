#ifndef _PUZZLE07_H
#define _PUZZLE07_H

typedef struct t_dir {
	int dirCount;
	char **dirName;
	struct t_dir **dir;
	int fileCount;
	char **fileName;
	int *fileSize;
} t_dir;

void printPuzzle07(void);
void parseInput07(const char *FILENAME, t_dir *top);
void parseHelper07(FILE *fp, t_dir *dir, int *lineNumber);
int solvePuzzle07A(const t_dir *top);
int solvePuzzle07A_Helper(const t_dir *dir, int *globalCount);
int solvePuzzle07B();
void free07(t_dir *dir);

#endif //_PUZZLE07_H