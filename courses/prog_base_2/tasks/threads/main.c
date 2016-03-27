/*There is another version, commented out in the end of every file (writer.h, writer.c and main.c)
If something disappoints you in this version (but everything is working fine, I guess), check another version.
Thank you for the attention.*/

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
	//reader_t * readerTwo = reader_new(stringSmp); // -- second reader module
	//reader_t * readerThree = reader_new(stringSmp); // -- third reader module

	writer_free(writer);
	reader_free(readerOne);
	//reader_free(readerTwo); // -- free of second reader module
	//reader_free(readerThree); // -- free of third reader module
	string_free(stringSmp);

	puts("\nPress ANY KEY again to exit the program...");
	getch();
	getch();
	return 0;
}

/*#include <stdio.h>
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

	writer_new(stringSmp);
	reader_new(stringSmp);
	//reader_new(stringSmp); // -- second reader module
	//reader_new(stringSmp); // -- third reader module

	writer_free(stringSmp);
	reader_free(stringSmp);
	string_free(stringSmp);

	puts("\nPress ANY KEY again to exit the program...");
	getch();
	getch();
	return 0;
}*/