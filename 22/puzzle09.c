#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "puzzle09.h"

#define INPUT_FILE "input/input09.txt"
#define INPUT_LENGTH 2000
#define GRID_EXPAND_STEP 5
#define NUM_KNOTS 10

#define CHECK(X) do { \
	if (X) { \
		fprintf(stderr, "ERROR :%d -- %s\n", __LINE__, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} \
} while(0)

void printPuzzle09(void) {
	t_motion motions[INPUT_LENGTH];
	parseInput09(INPUT_FILE, motions);

	const int solutionA = solvePuzzle09A(motions);
	printf("Puzzle 09 part A: %d\n", solutionA);
	const int solutionB = solvePuzzle09B(motions);
	printf("Puzzle 09 part B: %d\n", solutionB);
}

void parseInput09(const char *FILENAME, t_motion *motions) {
	FILE *fp = fopen(FILENAME, "r");
	CHECK(fp == NULL);

	for (int i = 0; i < INPUT_LENGTH; i++) {
		char direction;
		CHECK( fscanf(fp, "%c %d\n", &direction, &(motions[i].steps)) != 2 );
		switch (direction) {
			case 'U':
				motions[i].direction = UP;
				break;
			case 'D':
				motions[i].direction = DOWN;
				break;
			case 'R':
				motions[i].direction = RIGHT;
				break;
			case 'L':
				motions[i].direction = LEFT;
				break;
		}
	}

	CHECK( fclose(fp) == EOF );
}

int solvePuzzle09A(t_motion *motions) {
	bool **grid = malloc(sizeof(bool *));
	CHECK(grid == NULL);
	*grid = calloc(1, sizeof(bool));
	CHECK(*grid == NULL);
	int yN_Limit = 0, yP_Limit = 0;
	int xN_Limit = 0, xP_Limit = 0;
	int xHead = 0, yHead = 0;
	int xTail = 0, yTail = 0;
	int score = 0;

	for (int i = 0; i < INPUT_LENGTH; i++) {
		for (int j = 0; j < motions[i].steps; j++) {
			switch(motions[i].direction) {

				case UP:
					yHead++;
					// Check if more top rows need to be added
					if (yHead > yP_Limit) {
						yP_Limit += GRID_EXPAND_STEP;
						grid = realloc(grid, (yN_Limit+yP_Limit+1)*sizeof(bool *));
						CHECK(grid == NULL);
						// Initialize new rows to 0
						for (int k = yN_Limit+yP_Limit+1-GRID_EXPAND_STEP; k < yN_Limit+yP_Limit+1; k++) {
							grid[k] = calloc((xN_Limit+xP_Limit+1), sizeof(bool));
							CHECK(grid[k] == NULL);
						}
					}
					// Update tail position
					if (yHead - yTail > 1) {
						yTail++;
						xTail = xHead;
					}
					break;

				case DOWN:
					yHead--;
					// Check if more bottom rows need to be added
					if (yHead < -1*yN_Limit) {
						yN_Limit += 5;
						grid = realloc(grid, (yN_Limit+yP_Limit+1)*sizeof(bool *));
						CHECK(grid == NULL);
						// Move old rows up by GRID_EXPAND_STEP rows
						for (int k = yN_Limit+yP_Limit-GRID_EXPAND_STEP; k >= 0; k--)
							grid[k+GRID_EXPAND_STEP] = grid[k];
						// Initialize new rows to 0
						for (int k = 0; k < GRID_EXPAND_STEP; k++) {
							grid[k] = calloc((xN_Limit+xP_Limit+1), sizeof(bool));
							CHECK(grid[k] == NULL);
						}
					}
					// Update tail position
					if (yTail - yHead > 1) {
						yTail--;
						xTail = xHead;
					}
					break;

				case RIGHT:
					xHead++;
					// Check if more right columns need to be added
					if (xHead > xP_Limit) {
						xP_Limit += GRID_EXPAND_STEP;
						for (int k = 0; k < yN_Limit+yP_Limit+1; k++) {
							grid[k] = realloc(grid[k], (xN_Limit+xP_Limit+1)*sizeof(bool));
							CHECK(grid[k] == NULL);
							// Initialize new columns to 0
							memset(grid[k]+xN_Limit+xP_Limit+1-GRID_EXPAND_STEP, 0, GRID_EXPAND_STEP*sizeof(bool));
						}
					}
					// Update tail position
					if (xHead - xTail > 1) {
						xTail++;
						yTail = yHead;
					}
					break;

				case LEFT:
					xHead--;
					// Check if more left columns need to be added
					if (xHead < -1*xN_Limit) {
						xN_Limit += GRID_EXPAND_STEP;
						for (int k = 0; k < yN_Limit+yP_Limit+1; k++) {
							grid[k] = realloc(grid[k], (xN_Limit+xP_Limit+1)*sizeof(bool));
							CHECK(grid[k] == NULL);
							// Move old columns to the right by GRID_EXPAND_STEP columns
							memmove(grid[k]+GRID_EXPAND_STEP, grid[k], (xN_Limit+xP_Limit+1-GRID_EXPAND_STEP)*sizeof(bool));
							// Initialize new columsn to 0
							memset(grid[k], 0, GRID_EXPAND_STEP*sizeof(bool));
						}
					}
					// Update tail position
					if (xTail - xHead > 1) {
						xTail--;
						yTail = yHead;
					}
					break;
			}
			grid[yN_Limit+yTail][xN_Limit+xTail] = true;
		}
	}

	for (int i = 0; i < yN_Limit+yP_Limit+1; i++) {
		for (int j = 0; j < xN_Limit+xP_Limit+1; j++)
			score += grid[i][j];
		free(grid[i]);
	}
	free(grid);

	return score;
}

int solvePuzzle09B(t_motion *motions) {
	bool **grid = malloc(sizeof(bool *));
	CHECK(grid == NULL);
	*grid = calloc(1, sizeof(bool));
	CHECK(*grid == NULL);
	int yN_Limit = 0, yP_Limit = 0;
	int xN_Limit = 0, xP_Limit = 0;
	int xKnot[NUM_KNOTS] = {0}, yKnot[NUM_KNOTS] = {0};
	int score = 0;

	for (int i = 0; i < INPUT_LENGTH; i++) {
		for (int j = 0; j < motions[i].steps; j++) {
			switch(motions[i].direction) {

				case UP:
					yKnot[0]++;
					// Check if more top rows need to be added
					if (yKnot[0] > yP_Limit) {
						yP_Limit += GRID_EXPAND_STEP;
						grid = realloc(grid, (yN_Limit+yP_Limit+1)*sizeof(bool *));
						CHECK(grid == NULL);
						// Initialize new rows to 0
						for (int k = yN_Limit+yP_Limit+1-GRID_EXPAND_STEP; k < yN_Limit+yP_Limit+1; k++) {
							grid[k] = calloc((xN_Limit+xP_Limit+1), sizeof(bool));
							CHECK(grid[k] == NULL);
						}
					}
					break;

				case DOWN:
					yKnot[0]--;
					// Check if more bottom rows need to be added
					if (yKnot[0] < -1*yN_Limit) {
						yN_Limit += 5;
						grid = realloc(grid, (yN_Limit+yP_Limit+1)*sizeof(bool *));
						CHECK(grid == NULL);
						// Move old rows up by GRID_EXPAND_STEP rows
						for (int k = yN_Limit+yP_Limit-GRID_EXPAND_STEP; k >= 0; k--)
							grid[k+GRID_EXPAND_STEP] = grid[k];
						// Initialize new rows to 0
						for (int k = 0; k < GRID_EXPAND_STEP; k++) {
							grid[k] = calloc((xN_Limit+xP_Limit+1), sizeof(bool));
							CHECK(grid[k] == NULL);
						}
					}
					break;

				case RIGHT:
					xKnot[0]++;
					// Check if more right columns need to be added
					if (xKnot[0] > xP_Limit) {
						xP_Limit += GRID_EXPAND_STEP;
						for (int k = 0; k < yN_Limit+yP_Limit+1; k++) {
							grid[k] = realloc(grid[k], (xN_Limit+xP_Limit+1)*sizeof(bool));
							CHECK(grid[k] == NULL);
							// Initialize new columns to 0
							memset(grid[k]+xN_Limit+xP_Limit+1-GRID_EXPAND_STEP, 0, GRID_EXPAND_STEP*sizeof(bool));
						}
					}
					break;

				case LEFT:
					xKnot[0]--;
					// Check if more left columns need to be added
					if (xKnot[0] < -1*xN_Limit) {
						xN_Limit += GRID_EXPAND_STEP;
						for (int k = 0; k < yN_Limit+yP_Limit+1; k++) {
							grid[k] = realloc(grid[k], (xN_Limit+xP_Limit+1)*sizeof(bool));
							CHECK(grid[k] == NULL);
							// Move old columns to the right by GRID_EXPAND_STEP columns
							memmove(grid[k]+GRID_EXPAND_STEP, grid[k], (xN_Limit+xP_Limit+1-GRID_EXPAND_STEP)*sizeof(bool));
							// Initialize new columsn to 0
							memset(grid[k], 0, GRID_EXPAND_STEP*sizeof(bool));
						}
					}
					break;
			}

			// Update tail position
			for (int k = 0; k < NUM_KNOTS-1; k++) {
				int xDif = xKnot[k] - xKnot[k+1];
				int yDif = yKnot[k] - yKnot[k+1];

				// Diagonal
				if (abs(yDif) > 1 && abs(xDif) > 1) {
					yKnot[k+1] += yDif/2;
					xKnot[k+1] += xDif/2;
				// Vertical
				} else if (abs(yDif) > 1) {
					yKnot[k+1] += yDif/2;
					xKnot[k+1] = xKnot[k];
				// Horizontal
				} else if (abs(xDif) > 1) {
					xKnot[k+1] += xDif/2;
					yKnot[k+1] = yKnot[k];
				}
			}
			grid[yN_Limit+yKnot[NUM_KNOTS-1]][xN_Limit+xKnot[NUM_KNOTS-1]] = true;
		}
	}

	for (int i = 0; i < yN_Limit+yP_Limit+1; i++) {
		for (int j = 0; j < xN_Limit+xP_Limit+1; j++)
			score += grid[i][j];
		free(grid[i]);
	}
	free(grid);

	return score;
}