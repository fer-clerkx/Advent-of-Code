#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "puzzle07.h"

#define INPUT_FILE "input/input07.txt"
#define INPUT_LENGTH 1013
#define DIR_SIZE_THRESHOLD 100000
#define TOTAL_SPACE 70000000
#define TARGET_UNUSED_SPACE 30000000

#define CHECK(X) do { \
	if (X) { \
		fprintf(stderr, "ERROR :%d -- %s\n", __LINE__, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} \
} while(0)

void printPuzzle07(void) {
	t_dir *top = malloc(sizeof(t_dir));
	CHECK(top == NULL);

	parseInput07(INPUT_FILE, top);


	const int solutionA = solvePuzzle07A(top);
	printf("Puzzle 07 part A: %d\n", solutionA);
	const int solutionB = solvePuzzle07B(top);
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

	CHECK( fclose(fp) == EOF );
}

void parseHelper07(FILE *fp, t_dir *dir, int *lineNumber) {
	char line[25];
	while (*lineNumber < INPUT_LENGTH) {
		(*lineNumber)++;
		CHECK( fgets(line, 25, fp) == NULL );

		char *token = strtok(line, " \n");
		CHECK(token == NULL);

		if (token[0] == '$') {
			token = strtok(NULL, " \n");
			CHECK(token == NULL);
			
			// Ignore ls command
			if ( strcmp(token, "ls") == 0 )
				;
			// cd command
			else {
				token = strtok(NULL, " \n");
				CHECK(token == NULL);

				if ( strcmp(token, "..") == 0 )
					return;
				else {
					for (int i = 0; i < dir->dirCount; i++) {
						if ( strcmp(token, dir->dirName[i]) == 0 ) {
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

			// Expand dirName array
			dir->dirName = realloc(dir->dirName, (dir->dirCount+1)*sizeof(char *));
			CHECK(dir->dirName == NULL);

			// Allocate new dirName string
			dir->dirName[dir->dirCount] = malloc(15);
			CHECK(dir->dirName[dir->dirCount] == NULL);
			strncpy(dir->dirName[dir->dirCount], token, 15);

			// Expand dir array
			dir->dir = realloc(dir->dir, (dir->dirCount+1)*sizeof(t_dir *));
			CHECK(dir->dir == NULL);

			// Allocate new dir struct
			t_dir *newDir = malloc(sizeof(t_dir));
			CHECK(newDir == NULL);
			memset(newDir, 0, sizeof(t_dir));
			dir->dir[dir->dirCount] = newDir;
			dir->dirCount++;

		// new file
		} else {
			// Expand fileSize array
			dir->fileSize = realloc(dir->fileSize, (dir->fileCount+1)*sizeof(int));
			CHECK(dir->fileSize == NULL);
			dir->fileSize[dir->fileCount] = strtol(token, NULL, 10);

			// Expand fileName array
			dir->fileName = realloc(dir->fileName, (dir->fileCount+1)*sizeof(char *));
			CHECK(dir->fileName == NULL);

			token = strtok(NULL, " \n");
			CHECK(token == NULL);

			// Allocate new fileName string
			dir->fileName[dir->fileCount] = malloc(15);
			CHECK(dir->fileName[dir->fileCount] == NULL);
			strncpy(dir->fileName[dir->fileCount], token, 15);

			dir->fileCount++;
		}
	}
}

int solvePuzzle07A(const t_dir *top) {
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

	return dirSize;
}

int solvePuzzle07B(const t_dir *top) {
	int *dirSizeArray = NULL;
	int arraySize = 0;

	const int USED_SPACE = solvePuzzle07B_Helper(top, &dirSizeArray, &arraySize);
	const int TO_FREE_SPACE = TARGET_UNUSED_SPACE - (TOTAL_SPACE - USED_SPACE);

	int minDirSize = INT_MAX;
	for (int i = 0; i < arraySize; i++) {
		int dirSize = dirSizeArray[i];
		if (dirSize >= TO_FREE_SPACE && dirSize < minDirSize)
			minDirSize = dirSize;
	}
	free(dirSizeArray);

	return minDirSize;
}

int solvePuzzle07B_Helper(const t_dir *dir, int **dirSizeArray, int *arraySize) {
	int dirSize = 0;
	for (int i = 0; i < dir->dirCount; i++) {
		dirSize += solvePuzzle07B_Helper(dir->dir[i], dirSizeArray, arraySize);
	}

	for (int i = 0; i < dir->fileCount; i++) {
		dirSize += dir->fileSize[i];
	}

	(*arraySize)++;
	*dirSizeArray = realloc(*dirSizeArray, (*arraySize)*sizeof(int));
	CHECK(*dirSizeArray == NULL);
	(*dirSizeArray)[(*arraySize)-1] = dirSize;

	return dirSize;
}

void free07(t_dir *dir) {
	for (int i = 0; i < dir->dirCount; i++) {
		free07(dir->dir[i]);
		free(dir->dir[i]);
		free(dir->dirName[i]);
	}
	free(dir->dir);
	free(dir->dirName);

	for (int i = 0; i < dir->fileCount; i++) {
		free(dir->fileName[i]);
	}
	free(dir->fileName);
	free(dir->fileSize);
}