#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int firstEl(int index, char string[], int size);
int lastEl(int index, char string[], int size);

int main(void) {
	char string[100];
	printf("Please, enter your string:\n");
	gets(string);
	int last;
	int first = firstEl(0, string, strlen(string));
	if (first == -1) {
		puts("-1");
	}
	else {
		last = lastEl(strlen(string) - 1, string, strlen(string));
		if (first >= last) {
			printf("%c\n", first);
		}
		else {
			printf("%c\n", last);
		}
	}
	printf("Press any key to exit the program...");
	getch();
	return 0;
}

int firstEl(int index, char string[], int size) {
	if (index == size) {
		return -1;
	}
	else if (isxdigit(string[index]) != 0) {
		return string[index];
	}
	else {
		return firstEl(index + 1, string, size);
	}
}

int lastEl(int index, char string[], int size) {
	if (index == -1) {
		return -1;
	}
	else if (isxdigit(string[index]) != 0) {
		return string[index];
	}
	else {
		return lastEl(index - 1, string, size);
	}
}