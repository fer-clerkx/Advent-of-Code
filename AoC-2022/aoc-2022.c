#include <stdlib.h>
#include <stdio.h>
#include "aoc-2022.h"

int main(int argc, char **argv) {
	int select;
	if(argc == 2) {
		select = atoi(argv[1]);
	} else {
		select = 2;
	}

	switch(select) {
		case 1:
			printPuzzle01();
			break;
		case 2:
			printPuzzle02();
			break;
		default:
			printf("Enter valid select value\n");
			break;
	}
	return 0;
}