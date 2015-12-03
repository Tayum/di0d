#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) {
	int *i = (int*)malloc(sizeof(int));
	int *first = (int*)calloc(1, sizeof(int));
	int *last = (int*)calloc(1, sizeof(int));
	char *string = (char*)malloc(sizeof(char) * 100);
	printf("Enter your string, please:\n");
	gets(string);
	for (*i = strlen(string); *i >= 0; (*i)--) {
		if (isdigit(string[*i]) != 0) {
			*first = string[*i] - 48;
		}
	}
	for (*i = 0; *i<=strlen(string); (*i)++) {
		if (isdigit(string[*i]) != 0) {
			*last = string[*i] - 48;
		}
	}
	printf("%i", *first-*last);
	free(string);
	free(last);
	free(first);
	free(i);
	getch();
	return 0;
}