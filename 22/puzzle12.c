#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "puzzle12.h"

#define USE_REAL_INPUT 0

#define INPUT_FILE_REAL "input/input12.txt"
#define GRID_HEIGHT_REAL -1
#define GRID_WIDTH_REAL -1
#define INPUT_FILE_TEST "input/test.txt"
#define GRID_HEIGHT_TEST 5
#define GRID_WIDTH_TEST 8

#define INPUT_FILE (USE_REAL_INPUT ? INPUT_FILE_REAL : INPUT_FILE_TEST)
#define GRID_HEIGHT (USE_REAL_INPUT ? GRID_HEIGHT_REAL : GRID_HEIGHT_TEST)
#define GRID_WIDTH (USE_REAL_INPUT ? GRID_WIDTH_REAL : GRID_WIDTH_TEST)

#define ANSWER_A_TEST -1
#define ANSWER_A_REAL -1
#define ANSWER_B_TEST -1
#define ANSWER_B_REAL -1

#define ANSWER_A (USE_REAL_INPUT ? ANSWER_A_REAL : ANSWER_A_TEST)
#define ANSWER_B (USE_REAL_INPUT ? ANSWER_B_REAL : ANSWER_B_TEST)

#define CHECK(X) do { \
	if (X) { \
		fprintf(stderr, "ERROR :%d -- %s\n", __LINE__, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} \
} while(0)

void printPuzzle12(void) {
	char **grid = malloc(GRID_HEIGHT*sizeof(char *));
	CHECK(grid == NULL);
	for (int i = 0; i < GRID_HEIGHT; i++) {
		grid[i] = malloc(GRID_WIDTH+1);
		CHECK(grid[i] == NULL);
	}
	parseInput12(INPUT_FILE, grid);

	for (int i = 0; i < GRID_HEIGHT; i++) {
		printf("%s\n", grid[i]);
	}
	printf("\n\n");

	const int solutionA = solvePuzzle12A();
	printf("Puzzle 12 part A: %d\t%s\n", solutionA, (solutionA == ANSWER_A) ? "Correct" : "Incorrect");
	const int solutionB = solvePuzzle12B();
	printf("Puzzle 12 part B: %d\t%s\n", solutionB, (solutionB == ANSWER_B) ? "Correct" : "Incorrect");
}

void parseInput12(const char *FILENAME, char **grid) {
	FILE *fp = fopen(FILENAME, "r");
	CHECK(fp == NULL);

	for (int i = 0; i < GRID_HEIGHT; i++)
		CHECK(fscanf(fp, "%s\n", grid[i]) != 1);

	CHECK( fclose(fp) == EOF );
}

int solvePuzzle12A() {
	return 0;
}

int solvePuzzle12B() {
	return 0;
}