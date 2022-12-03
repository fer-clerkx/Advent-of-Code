#include "Utils.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void ReadLines(const char *fileName, char **strArr, int maxLen, int maxSize) {
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL) {
		fprintf(stderr, "Error opening %s: %s", fileName, strerror(errno));
		exit(-1);
	}
	for (int i = 0; i < maxSize; i++) {
		if( fgets(strArr[i], maxLen, fp) == NULL ) {
			break;
		}
	}
	fclose(fp);
}