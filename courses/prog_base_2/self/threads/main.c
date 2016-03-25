#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#include "thread.h"
#include "mutex.h"

#include "logic.h"

int main(void) {
	//Structure with string and mutex
	string_t stringSmp;
	stringSmp.string = "This is the string that program will work with.";
	stringSmp.myMutex = mutex_new();

	// Create and run primary threads/
	printf("Input string: '%s'\n", stringSmp.string);
	thread_t * writer = thread_create_args(writerFunc, &stringSmp);
	thread_t * reader = thread_create_args(readerFunc, &stringSmp);

	// Wait here.
	getch();

	// Delete threads and free allocated memory.
	thread_free(writer);
	thread_free(reader);
	mutex_free(stringSmp.myMutex);
	puts("\nPress ANY KEY to exit the program...");
	getch();
	return 0;
}


/*#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "mutex.h"
#include "thread.h"
#include "logic.h"

int main()
{
	SetConsoleTitleA("Gonchar Maxim KP-51 Threads");
	// Shared data structure.
	sharedObj_t sharedObject = { { 0,0,0,0 } };
	sharedObject.mu = mutex_new();
	// Create and run primary threads/
	thread_t *producer = thread_create_args(producerFunc, &sharedObject);
	thread_t *consumer = thread_create_args(consumerFunc, &sharedObject);
	// Wait here.
	_getch();
	_getch();
	// Delete threads and free allocated memory.
	thread_free(producer);
	thread_free(consumer);
	// Delete mutex.
	mutex_free(sharedObject.mu);
	// End of the program
	puts("End of the program.");
	return (0);
}*/