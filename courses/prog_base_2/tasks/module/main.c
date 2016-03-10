#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "source.h"


int main(void) {
	const int size = 5;
	const char word[20];	//this is needed because without this does not work... (read the comment below)
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

	printf("LongestSent is:\n%s\n", line_LongestSent(lineSample));

	strcpy(word, line_LongestWord(lineSample));	//...this. If you try to printf directly "array_LongestWord(arr)"
	printf("\nLongestWord is:\n%s\n", word);	//(calling a function in a same time (line) you call "printf" function)
												//, it returns correct word ("understand" in original code),
												// but will print some "cracozyabras" instead. Idk why it happens.	

	line_free(lineSample);

	getch();

	return 0;
}