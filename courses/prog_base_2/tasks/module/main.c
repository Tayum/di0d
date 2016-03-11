#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "source.h"


int main(void) {
	const int size = 5;
	const char word[20];
	line_t * lineSample = line_new(size);

	line_fill(lineSample);
	line_print(lineSample);
	printf("Size is %i\n\n", line_getSize(lineSample));

	line_deleteSent(lineSample, 2);
	line_print(lineSample);
	printf("Size is %i\n\n", line_getSize(lineSample));

	line_addSent(lineSample, 2, "Not every shade is your own.");
	line_print(lineSample);
	printf("Size is %i\n\n", line_getSize(lineSample));

	line_addSent(lineSample, 1, "I understand more, than you can possibly know.");
	line_print(lineSample);
	printf("Size is %i\n\n", line_getSize(lineSample));

	printf("The longest sentence is:\n%s\n\n", line_LongestSent(lineSample));

	char * res = line_LongestWord(word, lineSample);
	printf("The longest word in the text is:\n%s\n", res);

	line_free(lineSample);

	getch();

	return 0;
}