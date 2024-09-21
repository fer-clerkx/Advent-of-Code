#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "puzzle05.h"

#define INPUT_FILE "input/input05.txt"
#define INPUT_STACKS 9
#define INPUT_STACK_DEPTH 8
#define INPUT_PROCEDURES 502

void printPuzzle05(void) {
	char *stacks[INPUT_STACKS];
	int stackDepth[INPUT_STACKS];
	t_procedure procedures[INPUT_PROCEDURES];

	for (int i = 0; i < INPUT_STACKS; i++) {
		stacks[i] = malloc(INPUT_STACKS*INPUT_STACK_DEPTH);
		if (stacks[i] == NULL) {
			fprintf(stderr, "Couldn't allocate memory for stacks: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	parseInput05(INPUT_FILE, stacks, stackDepth, procedures);

	char *stacksCopy[INPUT_STACKS];
	for (int i = 0; i < INPUT_STACKS; i++) {
		stacksCopy[i] = malloc(INPUT_STACKS*INPUT_STACK_DEPTH);
		if (stacksCopy[i] == NULL) {
			fprintf(stderr, "Couldn't allocate memory for stacks copy: %s", strerror(errno));
			exit(EXIT_FAILURE);
		}
		memcpy(stacksCopy[i], stacks[i], stackDepth[i]);
	}

	int stackDepthCopy[INPUT_STACKS];
	memcpy(stackDepthCopy, stackDepth, sizeof(int)*INPUT_STACKS);

	char solutionA[INPUT_STACKS+1];
	solvePuzzle05A(stacksCopy, stackDepthCopy, procedures, solutionA);
	printf("Puzzle 05 part A: %s\n", solutionA);
	char solutionB[INPUT_STACKS+1];
	solvePuzzle05B(stacks, stackDepth, procedures, solutionB);
	printf("Puzzle 05 part B: %s\n", solutionB);

	for (int i = 0; i < INPUT_STACKS; i++) {
		free(stacks[i]);
		free(stacksCopy[i]);
	}
}

void parseInput05(const char *FILENAME, char **stacks, int *stackDepth, t_procedure *procedures) {
	FILE *fp = fopen(FILENAME, "r");
	if ( fp == NULL ) {
		fprintf(stderr, "Couldn't open %s: %s", FILENAME, strerror(errno));
		exit(EXIT_FAILURE);
	}

	const int stackBufferSize = INPUT_STACKS*4+1;
	char stackBuffer[stackBufferSize];
	memset(stackDepth, 0, sizeof(int)*INPUT_STACKS);
	for (int i = 0; i < INPUT_STACK_DEPTH; i++) {
		if ( fgets(stackBuffer, stackBufferSize, fp) == NULL ) {
			fprintf(stderr, "Couldn't read %s line %d: %s", FILENAME, i, strerror(errno));
			fclose(fp);
			exit(EXIT_FAILURE);
		}

		for (int j = 0; j < INPUT_STACKS; j++) {
			char crate = stackBuffer[j*4+1];
			if (crate != ' ') {
				stacks[j][INPUT_STACK_DEPTH-i-1] = crate;
				if (stackDepth[j] == 0)
					stackDepth[j] = INPUT_STACK_DEPTH-i;
			}
		}
	}

	for (int i = 0; i < 2; i++) {
		if ( fgets(stackBuffer, stackBufferSize, fp) == NULL ) {
			fprintf(stderr, "Couldn't read %s line %d: %s", FILENAME, i+INPUT_STACK_DEPTH+1, strerror(errno));
			fclose(fp);
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < INPUT_PROCEDURES; i++) {
		if ( fscanf(fp, "%*s %d %*s %d %*s %d", &procedures[i].amount,
		&procedures[i].src, &procedures[i].dest) != 3) {
			fprintf(stderr, "Couldn't read %s line %d: %s", FILENAME, i+INPUT_STACK_DEPTH+3, strerror(errno));
			fclose(fp);
			exit(EXIT_FAILURE);
		}
	}

	fclose(fp);
}

void solvePuzzle05A(char **stacks, int *stackDepth, const t_procedure *procedures, char *topCrates) {
	for (int i = 0; i < INPUT_PROCEDURES; i++) {
		int amount = procedures[i].amount;
		int src = procedures[i].src;
		int dest = procedures[i].dest;
		for (int j = 0; j < amount; j++) {
			stacks[dest-1][stackDepth[dest-1]+j] = stacks[src-1][stackDepth[src-1]-j-1];
		}
		stackDepth[src-1] -= amount;
		stackDepth[dest-1] += amount;
	}

	for (int i = 0; i < INPUT_STACKS; i++) {
		topCrates[i] = stacks[i][stackDepth[i]-1];
	}
	topCrates[INPUT_STACKS] = '\0';
}

void solvePuzzle05B(char **stacks, int *stackDepth, const t_procedure *procedures, char *topCrates) {
	for (int i = 0; i < INPUT_PROCEDURES; i++) {
		int amount = procedures[i].amount;
		int src = procedures[i].src;
		int dest = procedures[i].dest;
		for (int j = 0; j < amount; j++) {
			stacks[dest-1][stackDepth[dest-1]+j] = stacks[src-1][stackDepth[src-1]-amount+j];
		}
		stackDepth[src-1] -= amount;
		stackDepth[dest-1] += amount;
	}

	for (int i = 0; i < INPUT_STACKS; i++) {
		topCrates[i] = stacks[i][stackDepth[i]-1];
	}
	topCrates[INPUT_STACKS] = '\0';
}