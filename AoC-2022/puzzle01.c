#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "aoc-2022.h"

static int solvePuzzle01A( char **input );
static int solvePuzzle01B( char **input );

static const char INPUTFILE[] = "input/input01.txt";
static const int INPUTLEN = 7;
static const int INPUTSIZE = 2252;

void printPuzzle01( void ) {
	//Read input file
	char *input[INPUTSIZE];
	for (int i = 0; i < INPUTSIZE; i++) {
		input[i] = malloc(INPUTLEN);
	}
	ReadLines(INPUTFILE, input, INPUTLEN, INPUTSIZE);

	int solutionA = solvePuzzle01A(input);
	printf("Puzzle 01 Part One: %d\n", solutionA);
	int solutionB = solvePuzzle01B(input);
	printf("Puzzle 01 Part Two: %d\n", solutionB);
}

static int solvePuzzle01A( char **input ) {
	//Get largest calorie count
	int maxCalories = 0;
	int localCalories = 0;
	for (int i = 0; i < INPUTSIZE; i++) {
		int calories = atoi(input[i]);
		localCalories += calories;
		//Check for empty or last line
		if(calories == 0 || i == INPUTSIZE-1) {
			if(localCalories > maxCalories) {
				maxCalories = localCalories;
			}
			localCalories = 0;
		}
	}
	return maxCalories;
}

static int solvePuzzle01B( char **input ) {
	//Get largest calorie count
	int maxCalories[3] = {0};
	int localCalories = 0;
	for (int i = 0; i < INPUTSIZE; i++) {
		int calories = atoi(input[i]);
		localCalories += calories;
		//Check for empty or last line
		if(calories == 0 || i == INPUTSIZE-1) {
			//Find lowest calorie count and index in top 3
			int lowestCalories = maxCalories[0];
			int lowestIndex = 0;
			for (int j = 1; j < 3; j++) {
				if(maxCalories[j] < lowestCalories) {
					lowestCalories = maxCalories[j];
					lowestIndex = j;
				}
			}
			//Replace smallest value from top 3
			if(localCalories > lowestCalories) {
				maxCalories[lowestIndex] = localCalories;
			}
			localCalories = 0;
		}
	}
	//Get sum of top 3 calories
	int top3Sum = 0;
	for (int i = 0; i < 3; i++) {
		top3Sum += maxCalories[i];
	}
	return top3Sum;
}