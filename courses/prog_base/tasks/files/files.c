#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fprocess(const char * pread, const char * pwrite) {
	int a, b;
	char c;
	int result;
	int i;
	char clip[100];
	FILE * fr = fopen(pread, "r");
	FILE * fw = fopen(pwrite, "w");
	for (i = 1; i <= 15; i++) {
		fgets(clip, 100, fr);
	}
	sscanf(clip, "%i %c %i", &a, &c, &b);
	switch (c) {
	case '+':
		result = a + b;
		fprintf(fw, "%i", result);
		break;
	case '-':
		result = a - b;
		fprintf(fw, "%i", result);
		break;
	case '*':
		result = a*b;
		fprintf(fw, "%i", result);
		break;
	default:
		fprintf(fw, "WRONG OPERATOR!");
		break;
	}
	fclose(fr);
	fclose(fw);
}