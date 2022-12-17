#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "aoc-2022.h"

static int solvePuzzle02A( char **input );
static int solvePuzzle02B( char **input );

#define INPUTFILE "input/input02.txt"
#define INPUTLEN 5
#define INPUTSIZE 2501

void printPuzzle02( void ) {
	//Read input file
	char *input[INPUTSIZE];
	for (int i = 0; i < INPUTSIZE; i++) {
		input[i] = malloc(INPUTLEN);
	}
	ReadLines(INPUTFILE, input, INPUTLEN, INPUTSIZE);

	int solutionA = solvePuzzle02A(input);
	printf("Puzzle 02 Part One: %d\n", solutionA);
	int solutionB = solvePuzzle02B(input);
	printf("Puzzle 02 Part Two: %d\n", solutionB);
	for (int i = 0; i < INPUTSIZE; i++) {
		free(input[i]);
	}
}

static int solvePuzzle02A( char **input ) {
	int totalScore = 0;
	for (int i = 0; i < INPUTSIZE; i++) {
		int roundScore = 0;
		switch(input[i][2]) {
		case 'X':	//My choice is rock
			roundScore += 1;
			switch(input[i][0]) {
			case 'A':
				roundScore += 3;
				break;
			case 'B':
				roundScore += 0;
				break;
			case 'C':
				roundScore += 6;
				break;
			}
			break;
		case 'Y':	//My choice is paper
			roundScore += 2;
			switch(input[i][0]) {
			case 'A':
				roundScore += 6;
				break;
			case 'B':
				roundScore += 3;
				break;
			case 'C':
				roundScore += 0;
				break;
			}
			break;
		case 'Z':	//My choice is scissors
			roundScore += 3;
			switch(input[i][0]) {
			case 'A':
				roundScore += 0;
				break;
			case 'B':
				roundScore += 6;
				break;
			case 'C':
				roundScore += 3;
				break;
			}
			break;
		}
		totalScore += roundScore;
	}
	return totalScore;
}

static int solvePuzzle02B( char **input ) {
	int totalScore = 0;
	for (int i = 0; i < INPUTSIZE; i++) {
		int roundScore = 0;
		switch(input[i][2]) {
		case 'X':	//I need to lose
			switch(input[i][0]) {
			case 'A':
				roundScore += 3;
				break;
			case 'B':
				roundScore += 1;
				break;
			case 'C':
				roundScore += 2;
				break;
			}
			break;
		case 'Y':	//I need to draw
			roundScore += 3;
			switch(input[i][0]) {
			case 'A':
				roundScore += 1;
				break;
			case 'B':
				roundScore += 2;
				break;
			case 'C':
				roundScore += 3;
				break;
			}
			break;
		case 'Z':	//I need to win
			roundScore += 6;
			switch(input[i][0]) {
			case 'A':
				roundScore += 2;
				break;
			case 'B':
				roundScore += 3;
				break;
			case 'C':
				roundScore += 1;
				break;
			}
			break;
		}
		totalScore += roundScore;
	}
	return totalScore;
}