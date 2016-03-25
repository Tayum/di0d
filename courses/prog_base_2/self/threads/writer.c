#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

#include "logic.h"


//printf("This char: %c", (ptr)[ind]);  -- TRASH
void * writerFunc(void *args) {
	string_t * stringStrc = (string_t *)args;
	stringStrc->index = -1;
	int length = strlen(stringStrc->string);
	while (1) {
		mutex_lock(stringStrc->myMutex);
		(stringStrc->index)++;
		if ((stringStrc->index) == length) {
			(stringStrc->index) = (stringStrc->index) % length;
			puts("\nThe end of the string is reached. Start checking again...");
			//Sleep(3000);
		}
		//fflush(stdout);
		mutex_unlock(stringStrc->myMutex);
		Sleep(100);
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
		mutex_unlock(stringStrc->myMutex);
		Sleep(100);
	}
	return (NULL);
}


/*#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include "logic.h"

// private:
bool _checkAscending(unsigned *arr)
{
	for (int i = 0; i < SHARED_ARR_SIZE - 1; i++)
	{
		if (arr[i] >= arr[i + 1])
			return (false);
	}
	return (true);
}

// public:
void *producerFunc(void *args)
{
	sharedObj_t *shObj = (sharedObj_t *)args;
	time_t t;
	srand((unsigned)time(&t));
	int index = 0;
	while (TRUE)
	{
		mutex_lock(shObj->mu);
		shObj->arr[index] = rand() % 10;
		index++;
		index %= 4;
		system("cls");
		printf("Array: %4i%4i%4i%4i\n", shObj->arr[0], shObj->arr[1], shObj->arr[2], shObj->arr[3]);
		printf("A process can take a while...\n\n");
		fflush(stdout);
		mutex_unlock(shObj->mu);
		Sleep(SLEEP_TIME);
	}
	return (NULL);
}

void *consumerFunc(void *args)
{
	sharedObj_t *shObj = (sharedObj_t *)args;
	while (TRUE)
	{
		mutex_lock(shObj->mu);
		if (_checkAscending(shObj->arr))
		{
			puts("Array in ascending order!\n"
				"See you later!\n"
				"Wait +-2 seconds.");
			Sleep(2000);
		}
		mutex_unlock(shObj->mu);
		Sleep(SLEEP_TIME);
	}
	return (NULL);
}*/