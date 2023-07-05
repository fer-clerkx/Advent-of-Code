#include <stdlib.h>
#include <stdio.h>
#include "aoc-2022.h"

int main(int argc, char **argv) {
	int select;
	if(argc == 2) {
		select = atoi(argv[1]);
	} else {
		select = 11;
	}

	switch(select) {
		case 1:
			printPuzzle01();
			break;
		case 2:
			printPuzzle02();
			break;
		case 3:
			printPuzzle03();
			break;
		case 4:
			printPuzzle04();
			break;
		case 5:
			printPuzzle05();
			break;
		case 6:
			printPuzzle06();
			break;
		case 7:
			printPuzzle07();
			break;
		case 8:
			printPuzzle08();
			break;
		case 9:
			printPuzzle09();
			break;
		case 10:
			printPuzzle10();
			break;
		case 11:
			printPuzzle11();
			break;
		default:
			printf("Enter valid select value\n");
			break;
	}
	return 0;
}