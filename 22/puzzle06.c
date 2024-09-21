#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "puzzle06.h"

#define INPUT_FILE "input/input06.txt"
#define INPUT_LENGTH 4095

void printPuzzle06(void) {
	char buffer[INPUT_LENGTH+1];
	parseInput06(INPUT_FILE, buffer);

	const int solutionA = solvePuzzle06A(buffer);
	printf("Puzzle 06 part A: %d\n", solutionA);
	const int solutionB = solvePuzzle06B(buffer);
	printf("Puzzle 06 part B: %d\n", solutionB);
}

void parseInput06(const char *FILENAME, char *buffer) {
	FILE *fp = fopen(FILENAME, "r");
	if ( fp == NULL ) {
		fprintf(stderr, "Couldn't open %s: %s", FILENAME, strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ( fgets(buffer, INPUT_LENGTH+1, fp) == NULL ) {
		fprintf(stderr, "Couldn't read from %s: %s", FILENAME, strerror(errno));
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	fclose(fp);
}

int solvePuzzle06A(const char *buffer) {
	#define mapLength 'z'-'a'+1
	const int markerLength = 4;
	unsigned char map[mapLength] = {0};

	for (int i = 0; i < markerLength-1; i++) {
		map[buffer[i]-'a']++;
	}

	unsigned char uniqueCount;
	for (int i = markerLength-1; i < INPUT_LENGTH; i++) {
		map[buffer[i]-'a']++;

		uniqueCount = 0;
		for (int j = 0; j < mapLength; j++) {
			if (map[j] > 0)
				uniqueCount++;
		}
		if (uniqueCount == markerLength)
			return i+1;

		map[buffer[i-markerLength+1]-'a']--;
	}

	fprintf(stderr, "Couldn't find solution for puzzle 06 part B\n");
	exit(EXIT_FAILURE);
}

int solvePuzzle06B(const char *buffer) {
	#define mapLength 'z'-'a'+1
	const int markerLength = 14;
	unsigned char map[mapLength] = {0};

	for (int i = 0; i < markerLength-1; i++) {
		map[buffer[i]-'a']++;
	}

	unsigned char uniqueCount;
	for (int i = markerLength-1; i < INPUT_LENGTH; i++) {
		map[buffer[i]-'a']++;

		uniqueCount = 0;
		for (int j = 0; j < mapLength; j++) {
			if (map[j] > 0)
				uniqueCount++;
		}
		if (uniqueCount == markerLength)
			return i+1;

		map[buffer[i-markerLength+1]-'a']--;
	}

	fprintf(stderr, "Couldn't find solution for puzzle 06 part B\n");
	exit(EXIT_FAILURE);
}