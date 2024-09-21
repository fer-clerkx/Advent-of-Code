#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "puzzle04.h"

#define INPUT_FILE "input/input04.txt"
#define INPUT_LENGTH 1000

void printPuzzle04(void) {
	t_pair_assign assignments[INPUT_LENGTH];
	parseInput04(INPUT_FILE, assignments);

	int solutionA = solvePuzzle04A(assignments);
	printf("Puzzle 04 part A: %d\n", solutionA);
	int solutionB = solvePuzzle04B(assignments);
	printf("Puzzle 04 part B: %d\n", solutionB);
}

void parseInput04(const char *FILENAME, t_pair_assign *assignments) {
	FILE *fp = fopen(FILENAME, "r");
	if ( fp == NULL ) {
		fprintf(stderr, "Couldn't open input file %s: %s", FILENAME, strerror(errno));
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < INPUT_LENGTH; i++) {
		t_pair_assign pair;
		if ( fscanf(fp, "%d %*c %d %*c %d %*c %d", &pair.lower[0],
		&pair.upper[0], &pair.lower[1], &pair.upper[1]) == 0 ) {
			fprintf(stderr, "Couldn't read from input file %s: %s", FILENAME, strerror(errno));
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		assignments[i] = pair;
	}

	fclose(fp);
}

int solvePuzzle04A(const t_pair_assign *assignments) {
	int score = 0;
	for (int i = 0; i < INPUT_LENGTH; i++) {
		t_pair_assign pair = assignments[i];
		// First pair containts second pair
		if ( (pair.lower[0] <= pair.lower[1]) && (pair.upper[0] >= pair.upper[1]) )
			score++;
		// Second pair contains first pair
		else if ( (pair.lower[1] <= pair.lower[0]) && (pair.upper[1] >= pair.upper[0]) )
			score++;
	}

	return score;
}

int solvePuzzle04B(const t_pair_assign *assignments) {
	int score = 0;
	for (int i = 0; i < INPUT_LENGTH; i++) {
		t_pair_assign pair = assignments[i];
		// First pair lower within second pair range
		if ( (pair.lower[0] >= pair.lower[1]) && (pair.lower[0] <= pair.upper[1]) )
			score++;
		// First pair upper within second pair range
		else if ( (pair.upper[0] >= pair.lower[1]) && (pair.upper[0] <= pair.upper[1]) )
			score++;
		// Second pair lower within first pair range
		else if ( (pair.lower[1] >= pair.lower[0]) && (pair.lower[1] <= pair.upper[0]) )
			score++;
		// Second pair upper within first pair range
		else if ( (pair.upper[1] >= pair.lower[0]) && (pair.upper[1] <= pair.upper[0]) )
			score++;
	}

	return score;
}