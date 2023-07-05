#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "puzzle11.h"

#define USE_REAL_INPUT 0

#define INPUT_FILE_REAL "input/input11.txt"
#define NUM_MONKEYS_REAL 8
#define INPUT_FILE_TEST "input/test.txt"
#define NUM_MONKEYS_TEST 4

#define INPUT_FILE (USE_REAL_INPUT ? INPUT_FILE_REAL : INPUT_FILE_TEST)
#define NUM_MONKEYS (USE_REAL_INPUT ? NUM_MONKEYS_REAL : NUM_MONKEYS_TEST)

#define ROUNDS_A 20
#define ROUNDS_B 10000

#define ANSWER_A_TEST 10605
#define ANSWER_A_REAL 66124
#define ANSWER_B_TEST 2713310158
#define ANSWER_B_REAL 19309892877

#define ANSWER_A (USE_REAL_INPUT ? ANSWER_A_REAL : ANSWER_A_TEST)
#define ANSWER_B (USE_REAL_INPUT ? ANSWER_B_REAL : ANSWER_B_TEST)

#define CHECK(X) do { \
	if (X) { \
		fprintf(stderr, "ERROR :%d -- %s\n", __LINE__, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} \
} while(0)

void printPuzzle11(void) {
	t_monkey monkeys[NUM_MONKEYS];
	t_monkey monkeys_copy[NUM_MONKEYS];
	parseInput11(INPUT_FILE, monkeys);
	memcpy(monkeys_copy, monkeys, sizeof(t_monkey)*NUM_MONKEYS);
	for (int i = 0; i < NUM_MONKEYS; i++) {
		monkeys_copy[i].items = malloc(sizeof(long)*monkeys_copy[i].numItems);
		CHECK(monkeys_copy[i].items == NULL);
		memcpy(monkeys_copy[i].items, monkeys[i].items, sizeof(long)*monkeys[i].numItems);
	}

	const int solutionA = solvePuzzle11A(monkeys_copy);
	printf("Puzzle 11 part A: %d\t%s\n", solutionA, (solutionA == ANSWER_A) ? "Correct" : "Incorrect");
	const long solutionB = solvePuzzle11B(monkeys);
	printf("Puzzle 11 part B: %ld\t%s\n", solutionB, (solutionB == ANSWER_B) ? "Correct" : "Incorrect");

	for (int i = 0; i < NUM_MONKEYS; i++) {
		if (monkeys[i].numItems > 0)
			free(monkeys[i].items);
		if (monkeys_copy[i].numItems > 0)
			free(monkeys_copy[i].items);
	}
}

// function has some kind of bug, occasionally incorrectly parsing data
void parseInput11(const char *FILENAME, t_monkey *monkeys) {
	FILE *fp = fopen(FILENAME, "r");
	CHECK(fp == NULL);

	for (int i = 0; i < NUM_MONKEYS; i++) {
		char buffer[55];
		t_monkey monkey;
		CHECK( fgets(buffer, 55, fp) == NULL ); // Ignore "Monkey X:" line
		CHECK( fgets(buffer, 55, fp) == NULL );
		monkey.items = NULL;
		monkey.numItems = 0;

		char *num = strtok(buffer+18, ", \n");
		while (num != NULL) {
			monkey.numItems++;
			monkey.items = realloc(monkey.items, monkey.numItems*sizeof(monkey.items[0]));
			CHECK(monkey.items == NULL);
			monkey.items[monkey.numItems-1] = strtol(num, NULL, 10);
			CHECK(errno != 0);
			num = strtok(NULL, ", \n");
		}

		CHECK( fscanf(fp, "  Operation: new = old %c %s\n", (char *) &(monkey.operator), buffer) != 2 );
		if ( strcmp(buffer, "old") == 0 )
			monkey.operand = -1;
		else {
			monkey.operand = strtol(buffer, NULL, 10);
			CHECK(errno != 0);
		}
		CHECK( fscanf(fp, "  Test: divisible by %d\n", &(monkey.test_operand)) != 1 );
		CHECK( fscanf(fp, "    If true: throw to monkey %d\n", &(monkey.monkeyTrue)) != 1 );
		CHECK( fscanf(fp, "    If false: throw to monkey %d\n", &(monkey.monkeyFalse)) != 1 );
		monkeys[i] = monkey;
	}

	CHECK( fclose(fp) == EOF );
}

int solvePuzzle11A(t_monkey *monkeys) {
	int inspectCount[NUM_MONKEYS] = {0};
	for (int i = 0; i < ROUNDS_A; i++) {
		for (int j = 0; j < NUM_MONKEYS; j++) {
			t_monkey *monkey = monkeys + j;
			inspectCount[j] += monkey->numItems;
			while (monkey->numItems > 0) {
				if (monkey->operator == ADD)
					monkey->items[0] += (monkey->operand == -1) ? monkey->items[0] : monkey->operand;
				else
					monkey->items[0] *= (monkey->operand == -1) ? monkey->items[0] : monkey->operand;
				monkey->items[0] /= 3;
				t_monkey *destMonkey;
				if (monkey->items[0] % monkey->test_operand == 0)
					destMonkey = &(monkeys[monkey->monkeyTrue]);
				else
					destMonkey = &(monkeys[monkey->monkeyFalse]);

				destMonkey->numItems++;
				destMonkey->items = realloc(destMonkey->items, (destMonkey->numItems)*sizeof(monkey->items[0]));
				CHECK(destMonkey->items == NULL);
				destMonkey->items[destMonkey->numItems-1] = monkey->items[0];

				if (monkey->numItems > 1)
					memmove(monkey->items, monkey->items + 1, (monkey->numItems-1)*sizeof(monkey->items[0]));
				monkey->numItems--;
				monkey->items = realloc(monkey->items, monkey->numItems*sizeof(monkey->items[0]));
				CHECK(monkey->items == NULL && monkey->numItems > 0);
			}
		}
	}
	qsort(inspectCount, NUM_MONKEYS, sizeof(inspectCount[0]), comp11);
	return inspectCount[0] * inspectCount[1];
}

long solvePuzzle11B(t_monkey *monkeys) {
	// Calculate item division number
	int divisor = 1;
	for (int i = 0; i < NUM_MONKEYS; i++)
		divisor *= monkeys[i].test_operand;

	int inspectCount[NUM_MONKEYS] = {0};
	for (int i = 0; i < ROUNDS_B; i++) {
		for (int j = 0; j < NUM_MONKEYS; j++) {
			t_monkey *monkey = monkeys + j;
			inspectCount[j] += monkey->numItems;
			while (monkey->numItems > 0) {
				if (monkey->operator == ADD)
					monkey->items[0] += (monkey->operand == -1) ? monkey->items[0] : monkey->operand;
				else
					monkey->items[0] *= (monkey->operand == -1) ? monkey->items[0] : monkey->operand;
				monkey->items[0] %= divisor;
				t_monkey *destMonkey;
				if (monkey->items[0] % monkey->test_operand == 0)
					destMonkey = &(monkeys[monkey->monkeyTrue]);
				else
					destMonkey = &(monkeys[monkey->monkeyFalse]);

				destMonkey->numItems++;
				destMonkey->items = realloc(destMonkey->items, (destMonkey->numItems)*sizeof(monkey->items[0]));
				CHECK(destMonkey->items == NULL);
				destMonkey->items[destMonkey->numItems-1] = monkey->items[0];

				if (monkey->numItems > 1)
					memmove(monkey->items, monkey->items + 1, (monkey->numItems-1)*sizeof(monkey->items[0]));
				monkey->numItems--;
				monkey->items = realloc(monkey->items, monkey->numItems*sizeof(monkey->items[0]));
				CHECK(monkey->items == NULL && monkey->numItems > 0);
			}
		}
	}

	qsort(inspectCount, NUM_MONKEYS, sizeof(inspectCount[0]), comp11);

	return (long)inspectCount[0] * (long)inspectCount[1];
}

// Sort in descending order
int comp11(const void *a, const void *b) {
	if (*((int *)a) < *((int *)b))
		return 1;
	else if (*((int *)a) == *((int *)b))
		return 0;
	else
		return -1;
}