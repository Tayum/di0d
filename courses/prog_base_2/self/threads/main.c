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

/*#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#include "thread.h"

#include "writer.h"

int main(void) {
	//creating struct
	string_t stringSmp;

	//filling struct with basic values
	stringSmp.string = "This is the string that program will work with."; //iieiaoaioi
	stringSmp.index = -1;
	stringSmp.myMutex = mutex_new();

	//two main functions (checking on kbhit() is inside)
	printf("Input string: '%s'\n", stringSmp.string);
	thread_t * writer = thread_create_args(writerFunc, &stringSmp);
	Sleep(15);	//needed for "writer"-thread to start first. But that's not important, may be commented out
	thread_t * readerOne = thread_create_args(readerFunc, &stringSmp);
	//thread_t * readerTwo = thread_create_args(readerFunc, &stringSmp); -- the second reader function. It's clearer without it, but may be uncommented regarding to the condition of the task
	//thread_t * readerThree = thread_create_args(readerFunc, &stringSmp); -- the third reader function. It's clearer without it, but may be uncommented regarding to the condition of the task
	thread_join(readerOne); //ANY thread may be passed as parameter (writer/readerTwo/etc.); -- needed for correct checking on kbhit() and closing both threads properly

	//freeing threads and mutex
	thread_free(writer);
	thread_free(readerOne);
	//thread_free(readerTwo); -- uncomment if creating of threads is uncommented
	//thread_free(readerThree); -- uncomment if creating of threads is uncommented
	mutex_free(stringSmp.myMutex);

	//end of program
	puts("\nPress ANY KEY to exit the program...");
	getch();
	getch();
	return 0;
}*/