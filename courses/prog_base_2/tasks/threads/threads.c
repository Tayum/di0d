#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#include "thread.h"
#include "mutex.h"

/* Instead of creating a string, a pointer to it and passing them to function, I would rather
create a structure with all of these variables and pass it directly. I hope that does matter much.*/

struct string_s {
	char * string;
	mutex_t * myMutex;
	int index;
};

typedef struct string_s string_t;

void * writerFunc(void *args);
void * readerFunc(void *args);

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
	//thread_t * readerTwo = thread_create_args(readerFunc, &stringSmp); //-- the second reader function. It's clearer without it, but may be uncommented regarding to the condition of the task
	//thread_t * readerThree = thread_create_args(readerFunc, &stringSmp); //-- the third reader function. It's clearer without it, but may be uncommented regarding to the condition of the task
	thread_join(readerOne); //ANY thread may be passed as parameter (writer/readerTwo/etc.); -- needed for correct checking on kbhit() and closing both threads properly

	//freeing threads and mutex
	thread_free(writer);
	thread_free(readerOne);
	//thread_free(readerTwo); //-- uncomment if creating of threads is uncommented
	//thread_free(readerThree); //-- uncomment if creating of threads is uncommented
	mutex_free(stringSmp.myMutex);

	//end of program
	puts("\nPress ANY KEY to exit the program...");
	getch();
	getch();
	return 0;
}

void * writerFunc(void *args) {
	string_t * stringStrc = (string_t *)args;
	int length = strlen(stringStrc->string);
	while (1) {
		mutex_lock(stringStrc->myMutex);
		(stringStrc->index)++;
		if ((stringStrc->index) == length) {
			(stringStrc->index) = (stringStrc->index) % length;
			puts("\nThe end of the string is reached. Start checking again in 3 seconds...");
			Sleep(3000);
		}
		//when you press ANY KEY - the threads are closed
		if (kbhit()) {
			break;
		}
		//END OF closing threads
		Sleep(30);	// -- correct behaviour of the program (if goes before mutex_unlock)
		mutex_unlock(stringStrc->myMutex);
		//Sleep(100); // -- incorrect behaviour of the program (if goes after mutex_unlock)
	}
	return (NULL);
}

void * readerFunc(void *args) {
	string_t * stringStrc = (string_t *)args;
	while (1) {
		mutex_lock(stringStrc->myMutex);
		if (stringStrc->string[stringStrc->index] == 'a' || stringStrc->string[stringStrc->index] == 'A' || stringStrc->string[stringStrc->index] == 'e' || stringStrc->string[stringStrc->index] == 'E' || stringStrc->string[stringStrc->index] == 'i' || stringStrc->string[stringStrc->index] == 'I' || stringStrc->string[stringStrc->index] == 'o' || stringStrc->string[stringStrc->index] == 'O' || stringStrc->string[stringStrc->index] == 'u' || stringStrc->string[stringStrc->index] == 'U') {
			printf("%c", stringStrc->string[stringStrc->index]);
		}
		//when you press ANY KEY - the threads are closed
		if (kbhit()) {
			break;
		}
		//END OF closing threads
		Sleep(30); //correct behaviour of the program (if goes before mutex_unlock)
		mutex_unlock(stringStrc->myMutex);
		//Sleep(100); // -- incorrect behaviour of the program (if goes after mutex_unlock)
	}
	return (NULL);
}