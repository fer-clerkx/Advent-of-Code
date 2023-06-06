#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "puzzle07.h"

// #define INPUT_FILE "input/input07.txt"
#define INPUT_FILE "input/test.txt"
#define INPUT_LENGTH 23
#define DIR_SIZE_THRESHOLD 100000

#define CHECK(X) ({ \
	if (X) {
		fprintf(stderr, "ERROR :%d -- %s\n", __LINE__, strerror(errno)); \
		exit(EXIT_FAILURE); \
	}
})

void printPuzzle07(void) {
	t_dir *top = malloc(sizeof(t_dir));
	if (top == NULL) {
		fprintf(stderr, "Couldn't allocate memory for top: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	printf("debug\n");
	parseInput07(INPUT_FILE, top);

	printf("Hello world0\n");

	const int solutionA = solvePuzzle07A(top);
	printf("Puzzle 07 part A: %d\n", solutionA);
	const int solutionB = solvePuzzle07B();
	printf("Puzzle 07 part B: %d\n", solutionB);

	free07(top);
}

void parseInput07(const char *FILENAME, t_dir *top) {
	FILE *fp = fopen(FILENAME, "r");
	CHECK(fp == NULL);

	char buffer[10];
	CHECK( fgets(buffer, 10, fp) == NULL );

	top->dirCount = 0;
	top->dirName = NULL;
	top->dir = NULL;
	top->fileCount = 0;
	top->fileName = NULL;
	top->fileSize = NULL;
	int lineNumber = 1;

	parseHelper07(fp, top, &lineNumber);

	printf("done\n");

	CHECK( fclose(fp) == EOF );
	printf("done2\n");
}

void parseHelper07(FILE *fp, t_dir *dir, int *lineNumber) {
	char line[25];
	while (*lineNumber < INPUT_LENGTH) {
		(*lineNumber)++;
		CHECK( fgets(line, 25, fp) == NULL );
		printf("debug1\n");

		char *token = strtok(line, " \n");
		CHECK(token == NULL);
		printf("debug2\n");

		if (token[0] == '$') {
			token = strtok(NULL, " \n");
			CHECK(token == NULL);
			printf("debug3\n");
			
			// Ignore ls command
			if ( strcmp(token, "ls") == 0 )
				;
			// cd command
			else {
				token = strtok(NULL, " \n");
				CHECK(token == NULL);
				printf("debug4\n");

				if ( strcmp(token, "..") == 0 )
					return;
				else {
					for (int i = 0; i < dir->dirCount; i++) {
						if ( strcmp(token, dir->dirName[i]) == 0 ) {
							printf("debug5a\n");
							parseHelper07(fp, dir->dir[i], lineNumber);
							break;
						}
					}
				}
			}

		// new directory
		} else if ( strcmp(token, "dir") == 0 ) {
			token = strtok(NULL, " \n");
			CHECK(token == NULL);
			printf("debug5\n");

			// Expand dirName array
			dir->dirName = realloc(dir->dirName, (dir->dirCount+1)*sizeof(char *));
			CHECK(dir->dirName == NULL);
			printf("debug6\n");

			// Allocate new dirName string
			dir->dirName[dir->dirCount] = malloc(15);
			CHECK(dir->dirName[dir->dirCount] == NULL);
			printf("debug7\n");
			strncpy(dir->dirName[dir->dirCount], token, 15);

			// Expand dir array
			dir->dir = realloc(dir->dir, (dir->dirCount+1)*sizeof(t_dir *));
			CHECK(dir->dir == NULL);
			printf("debug8\n");

			// Allocate new dir struct
			dir->dir[dir->dirCount] = malloc(sizeof(t_dir));
			CHECK(dir->dir[dir->dirCount] == NULL);
			printf("debug9\n");
			dir->dirCount++;

		// new file
		} else {
			// Expand fileSize array
			dir->fileSize = realloc(dir->fileSize, (dir->dirCount+1)*sizeof(int));
			CHECK(dir->fileSize == NULL);
			printf("debug10\n");
			dir->fileSize[dir->fileCount] = strtol(token, NULL, 10);

			// Expand fileName array
			dir->fileName = realloc(dir->fileName, (dir->dirCount+1)*sizeof(char *));
			CHECK(dir->fileName == NULL);
			printf("debug11\n");

			token = strtok(NULL, " \n");
			CHECK(token == NULL);
			printf("debug12\n");

			// Allocate new fileName string
			dir->fileName[dir->fileCount] = malloc(15);
			CHECK(dir->fileName[dir->fileCount] == NULL);
			printf("debug13\n");
			strncpy(dir->fileName[dir->fileCount], token, 15);

			dir->fileCount++;
		}
		printf("Completed line %d\n", *lineNumber);
	}
}


int solvePuzzle07A(const t_dir *top) {
	printf("Hello world\n");
	int score = 0;
	solvePuzzle07A_Helper(top, &score);
	return score;
}

int solvePuzzle07A_Helper(const t_dir *dir, int *globalCount) {
	int dirSize = 0;
	
	for (int i = 0; i < dir->dirCount; i++) {
		dirSize += solvePuzzle07A_Helper(dir->dir[i], globalCount);
	}

	for (int i = 0; i < dir->fileCount; i++) {
		dirSize += dir->fileSize[i];
	}

	if (dirSize < DIR_SIZE_THRESHOLD)
		*globalCount += dirSize;

	printf("dirSize = %d\n globalCount = %d\n", dirSize, *globalCount);

	return dirSize;
}

int solvePuzzle07B() {
	return 0;
}

void free07(t_dir *dir) {
	for (int i = 0; i < dir->dirCount; i++) {
		free07(dir->dir[i]);
		free(dir->dir[i]);
		free(dir->dirName[i]);
	}
	free(dir->dir);
	free(dir->dirName);

	for (int i = 0; i < dir->fileCount; i++)
		free(dir->fileName[i]);
	free(dir->fileName);
	free(dir->fileSize);
}