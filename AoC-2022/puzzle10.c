#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "puzzle10.h"

#define INPUT_FILE "input/input10.txt"
#define INPUT_LENGTH 140
#define SPRITE_WIDTH 3
#define LIT_PIXEL '#'
#define DARK_PIXEL '.'
#define CRT_WIDTH 40
#define CRT_HEIGHT 6

#define CHECK(X) do { \
	if (X) { \
		fprintf(stderr, "ERROR :%d -- %s\n", __LINE__, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} \
} while(0)

void printPuzzle10(void) {
	t_instruction program[INPUT_LENGTH];
	parseInput10(INPUT_FILE, program);

	const int solutionA = solvePuzzle10A(program);
	printf("Puzzle 10 part A: %d\n", solutionA);
	printf("Puzzle 10 part B:\n");
	solvePuzzle10B(program);
}

void parseInput10(const char *FILENAME, t_instruction *program) {
	FILE *fp = fopen(FILENAME, "r");
	CHECK(fp == NULL);

	for (int i = 0; i < INPUT_LENGTH; i++) {
		char buffer[10];
		CHECK( fgets(buffer, 10, fp) == NULL );
		if ( strncmp(buffer, "noop", 4) == 0 ) {
			program[i].inst = NOOP;
		} else {
			program[i].inst = ADDX;
			program[i].oper = strtol(buffer+5, NULL, 10);
			CHECK(program[i].oper == 0 && errno != 0);
		}
	}

	CHECK( fclose(fp) == EOF );
}

int solvePuzzle10A(t_instruction *program) {
	int cycle = 0;
	int x = 1;
	int score = 0;

	for (int i = 0; i < INPUT_LENGTH; i++) {
		if (program[i].inst == NOOP) {
			cycle++;
			if (cycle % 40 == 20)
				score += x*cycle;
		} else {
			cycle++;
			if (cycle % 40 == 20)
				score += x*cycle;
			cycle++;
			if (cycle % 40 == 20)
				score += x*cycle;
			x += program[i].oper;
		}
	}
	return score;
}

void solvePuzzle10B(t_instruction *program) {
	int x = 1;
	int instCount = 0;
	int instCycle = 0;

	for (int i = 0; i < CRT_WIDTH*CRT_HEIGHT; i++) {
		if ((i % CRT_WIDTH) - x < 2 && (i % CRT_WIDTH) - x > -2)
			printf("%c", LIT_PIXEL);
		else
			printf("%c", DARK_PIXEL);
		if (i % 40 == CRT_WIDTH-1)
			printf("\n");

		CHECK(instCount == INPUT_LENGTH);
		if (program[instCount].inst == NOOP) {
			instCount++;
		} else {
			if (instCycle == 0) {
				instCycle++;
			} else {
				instCycle = 0;
				x += program[instCount].oper;
				instCount++;
			}
		}
	}
}