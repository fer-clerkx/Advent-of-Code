#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "puzzle08.h"

#define INPUT_FILE "input/input08.txt"
#define INPUT_SIZE 99
// #define INPUT_FILE "input/test.txt"
// #define INPUT_SIZE 5

#define CHECK(X) do { \
	if (X) { \
		fprintf(stderr, "ERROR :%d -- %s\n", __LINE__, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} \
} while(0)

void printPuzzle08(void) {
	unsigned char **trees = malloc(INPUT_SIZE*sizeof(unsigned char *));
	CHECK(trees == NULL);
	for (int i = 0; i < INPUT_SIZE; i++) {
		trees[i] = malloc(INPUT_SIZE);
		CHECK(trees[i] == NULL);
	}

	parseInput08(INPUT_FILE, trees);

	const int solutionA = solvePuzzle08A(trees);
	printf("Puzzle 08 part A: %d\n", solutionA);
	const int solutionB = solvePuzzle08B(trees);
	printf("Puzzle 08 part B: %d\n", solutionB);

	free08(trees);
}

void parseInput08(const char *FILENAME, unsigned char **trees) {
	FILE *fp = fopen(FILENAME, "r");
	CHECK(fp == NULL);

	for (int i = 0; i < INPUT_SIZE; i++) {
		char line[INPUT_SIZE+2];
		CHECK( fgets(line, INPUT_SIZE+2, fp) == NULL );
		for (int j = 0; j < INPUT_SIZE; j++)
			trees[i][j] = line[j] - '0';
	}

	CHECK( fclose(fp) == EOF );
}

int solvePuzzle08A(unsigned char **trees) {
	int score = INPUT_SIZE*2 + (INPUT_SIZE-2)*2;
	bool grid[INPUT_SIZE-2][INPUT_SIZE-2];
	for (int i = 0; i < INPUT_SIZE-2; i++) {
		for (int j = 0; j < INPUT_SIZE-2; j++)
			grid[i][j] = false;
	}

	// Horizontal
	for (int i = 1; i < INPUT_SIZE-1; i++) {
		// Left to right
		int rowMax = trees[i][0];
		for (int j = 1; j < INPUT_SIZE-1; j++) {
			if (trees[i][j] > rowMax) {
				grid[i-1][j-1] = true;
				rowMax = trees[i][j];
			}
		}

		// Right to left
		rowMax = trees[i][INPUT_SIZE-1];
		for (int j = INPUT_SIZE-2; j > 0; j--) {
			if (trees[i][j] > rowMax) {
				grid[i-1][j-1] = true;
				rowMax = trees[i][j];
			}
		}
	}

	// Vertical
	for (int i = 1; i < INPUT_SIZE-1; i++) {
		// Top to bottom
		int colMax = trees[0][i];
		for (int j = 1; j < INPUT_SIZE-1; j++) {
			if (trees[j][i] > colMax) {
				grid[j-1][i-1] = true;
				colMax = trees[j][i];
			}
		}

		// Right to left
		colMax = trees[INPUT_SIZE-1][i];
		for (int j = INPUT_SIZE-2; j > 0; j--) {
			if (trees[j][i] > colMax) {
				grid[j-1][i-1] = true;
				colMax = trees[j][i];
			}
		}
	}

	for (int i = 0; i < INPUT_SIZE-2; i++) {
		for (int j = 0; j < INPUT_SIZE-2; j++)
			score += grid[i][j];
	}

	return score;
}

int solvePuzzle08B(unsigned char **trees) {
	t_scenicScore scenicScore[INPUT_SIZE][INPUT_SIZE];
	int score = 0;

	// Horizontal
	for (int i = 0; i < INPUT_SIZE; i++) {
		for (int j = 0; j < INPUT_SIZE; j++) {
			int tree = trees[i][j];
			// Left
			if (j == 0)
				scenicScore[i][j].left = 0;
			else {
				for (int k = j-1; k >= 0; k--) {
					if (trees[i][k] >= tree) {
						scenicScore[i][j].left = j-k;
						break;
					} else if (k == 0)
						scenicScore[i][j].left = j;
				}
			}
			// Right
			if (j == INPUT_SIZE-1)
				scenicScore[i][j].right = 0;
			else {
				for (int k = j+1; k < INPUT_SIZE; k++) {
					if (trees[i][k] >= tree) {
						scenicScore[i][j].right = k-j;
						break;
					} else if (k == INPUT_SIZE-1)
						scenicScore[i][j].right = k-j;
				}
			}
		}
	}

	// Vertical
	for (int i = 0; i < INPUT_SIZE; i++) {
		for (int j = 0; j < INPUT_SIZE; j++) {
			int tree = trees[j][i];
			// Up
			if (j == 0)
				scenicScore[j][i].up = 0;
			else {
				for (int k = j-1; k >= 0; k--) {
					if (trees[k][i] >= tree) {
						scenicScore[j][i].up = j-k;
						break;
					} else if (k == 0)
						scenicScore[j][i].up = j;
				}
			}
			// Down
			if (j == INPUT_SIZE-1)
				scenicScore[j][i].down = 0;
			else {
				for (int k = j+1; k < INPUT_SIZE; k++) {
					if (trees[k][i] >= tree) {
						scenicScore[j][i].down = k-j;
						break;
					} else if (k == INPUT_SIZE-1)
						scenicScore[j][i].down = k-j;
				}
			}
		}
	}

	for (int i = 0; i < INPUT_SIZE; i++) {
		for (int j = 0; j < INPUT_SIZE; j++) {
			t_scenicScore curTree = scenicScore[i][j];
			int curScore = curTree.up*curTree.down*curTree.left*curTree.right;
			if (curScore > score)
				score = curScore;
		}
	}

	return score;
}

void free08(unsigned char **trees) {
	for (int i = 0; i < INPUT_SIZE; i++)
		free(trees[i]);
	free(trees);
}