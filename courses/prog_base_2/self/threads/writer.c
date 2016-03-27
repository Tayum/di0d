#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#include "thread.h"
#include "mutex.h"

#include "writer.h"

//shared_data module
struct string_s {
	char * string;
	mutex_t * myMutex;
	int index;
};

string_t * string_new(char * smpString) {
	string_t * stringSample = malloc(sizeof(struct string_s));
	stringSample->string = smpString;
	stringSample->myMutex = mutex_new();
	stringSample->index = -1;
	return stringSample;
}

void string_free(string_t * self) {
	mutex_free(self->myMutex);
	free(self);
}

char * string_getString(char * resultStr, const string_t * self) {
		strcpy(resultStr, self->string);
	return resultStr;
}

//writer module
writer_t * writer_new(string_t * self) {
	thread_t * writerSample = thread_create_args(writerFunc, self);
	return writerSample;
}

void writer_free(writer_t * self) {
	thread_free(self);
}

void writer_wait(const writer_t * self) {
	thread_join(self);
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
		if (kbhit()) {
			break;
		}
		Sleep(30);
		mutex_unlock(stringStrc->myMutex);
	}
	return (NULL);
}

//reader module
reader_t * reader_new(string_t * self) {
	thread_t * readerSample = thread_create_args(readerFunc, self);
	return readerSample;
}

void reader_free(reader_t * self) {
	thread_free(self);
}

void reader_wait(const reader_t * self) {
	thread_join(self);
}

void * readerFunc(void *args) {
	string_t * stringStrc = (string_t *)args;
	while (1) {
		mutex_lock(stringStrc->myMutex);
		if (stringStrc->string[stringStrc->index] == 'a' || stringStrc->string[stringStrc->index] == 'A' || stringStrc->string[stringStrc->index] == 'e' || stringStrc->string[stringStrc->index] == 'E' || stringStrc->string[stringStrc->index] == 'i' || stringStrc->string[stringStrc->index] == 'I' || stringStrc->string[stringStrc->index] == 'o' || stringStrc->string[stringStrc->index] == 'O' || stringStrc->string[stringStrc->index] == 'u' || stringStrc->string[stringStrc->index] == 'U') {
			printf("%c", stringStrc->string[stringStrc->index]);
		}
		if (kbhit()) {
			break;
		}
		Sleep(30);
		mutex_unlock(stringStrc->myMutex);
	}
	return (NULL);
}