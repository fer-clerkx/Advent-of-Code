#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "puzzle03.h"

#define INPUTFILE "input/input03.txt"
#define INPUTLENGTH 300
#define INPUTSIZE 55
#define BIT_MASK 0x7 //0b111

void printPuzzle03( void ) {
	char *items[INPUTLENGTH];
	for (int i = 0; i < INPUTLENGTH; i++)
		items[i] = malloc(INPUTSIZE);

	parseInput03(INPUTFILE, items);

	int solutionA = solvePuzzle03A(items);
	printf("Puzzle 03 Part One: %d\n", solutionA);

	int solutionB = solvePuzzle03B(items);
	printf("Puzzle 03 Part Two: %d\n", solutionB);

	for (int i = 0; i < INPUTLENGTH; i++)
		free(items[i]);
}

void parseInput03(const char *FILENAME, char **items) {
	FILE *fp = fopen(FILENAME, "r");
	if(fp == NULL) {
		fprintf(stderr, "Error opening %s: %s", FILENAME, strerror(errno));
		exit(-1);
	}

	for(int i = 0; i < INPUTLENGTH; i++) {
		if ( fscanf(fp, "%s", items[i]) == 0 ) {
			fprintf(stderr, "Error reading line %d from file %s", i+1, FILENAME);
			fclose(fp);
			exit(-1);
		}
	}

	fclose(fp);
}

int solvePuzzle03A( char **items ) {
	int score = 0;
	int sackSize;
	char item;
	bool map[128] = {false};

	for (int i = 0; i < INPUTLENGTH; i++) {
		sackSize = strlen(items[i]);

		// Check first half
		for (int j = 0; j < sackSize/2; j++) {
			item = items[i][j];
			map[(int)item] = true;
		}

		// Check second half
		for (int j = sackSize/2; j < sackSize; j++) {
			item = items[i][j];
			if (map[(int)item] == true) {
				if ( islower(item) )
					score += item - 'a' + 1;
				else
					score += item - 'A' + 27;
				break;
			}
		}

		memset(map, false, sizeof(map));
	}

	return score;
}

int solvePuzzle03B( char **items ) {
	int score = 0;
	int sackSize;
	char item;
	int map[128] = {0};

	for (int i = 0; i < INPUTLENGTH; i++) {
		sackSize = strlen(items[i]);

		for (int j = 0; j < sackSize; j++) {
			item = items[i][j];
			map[(int)item] |= 1 << ((i+1)%3);

			// Check if first 3 bits are set
			if ((map[(int)item] & BIT_MASK) == BIT_MASK) {
				if ( islower(item) )
					score += item - 'a' + 1;
				else
					score += item - 'A' + 27;
				break;
			}
		}

		// Reset map after checking group
		if ((i+1) % 3 == 0)
			memset(map, 0, sizeof(map));
	}

	return score;
}