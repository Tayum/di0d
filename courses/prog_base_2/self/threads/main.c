#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "writer.h"

int main(void) {
	const char sent[100];
	string_t * stringSmp = string_new("This is the string that program will work with.");

	char * res = string_getString(sent, stringSmp);
	printf("Input string: '%s'\n", res);
	puts("Reminder: to stop the processing of the string, press ANY KEY!");

	writer_t * writer = writer_new(stringSmp);
	reader_t * readerOne = reader_new(stringSmp);
	//reader_t * readerTwo = reader_new(stringSmp); -- constuction of the second reader module
	//reader_t * readerThree = reader_new(stringSmp); -- constuction of the third reader module

	reader_wait(readerOne);

	writer_free(writer);
	reader_free(readerOne);
	//reader_free(readerTwo); -- destruction of the second reader module, uncomment if construction is uncommented
	//reader_free(readerThree); -- destruction of the third reader module, uncomment if construction is uncommented
	string_free(stringSmp);

	puts("\nPress ANY KEY again to exit the program...");
	getch();
	getch();
	return 0;
}