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
	thread_join(self);
	thread_free(self);
}

void * writerFunc(void *args) {
	string_t * stringStrc = (string_t *)args;
	int length = strlen(stringStrc->string);
	while (1) {
		mutex_lock(stringStrc->myMutex);
		if (kbhit()) {
			break;
		}
		(stringStrc->index)++;
		if ((stringStrc->index) == length) {
			(stringStrc->index) = (stringStrc->index) % length;
			puts("\nThe end of the string is reached. Start checking again in 3 seconds...");
			Sleep(3000);
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
	thread_join(self);
	thread_free(self);
}

void * readerFunc(void *args) {
	string_t * stringStrc = (string_t *)args;
	while (1) {
		mutex_lock(stringStrc->myMutex);
		if (kbhit()) {
			break;
		}
		if (stringStrc->string[stringStrc->index] == 'a' || stringStrc->string[stringStrc->index] == 'A' || stringStrc->string[stringStrc->index] == 'e' || stringStrc->string[stringStrc->index] == 'E' || stringStrc->string[stringStrc->index] == 'i' || stringStrc->string[stringStrc->index] == 'I' || stringStrc->string[stringStrc->index] == 'o' || stringStrc->string[stringStrc->index] == 'O' || stringStrc->string[stringStrc->index] == 'u' || stringStrc->string[stringStrc->index] == 'U') {
			printf("%c", stringStrc->string[stringStrc->index]);
		}
		Sleep(30);
		mutex_unlock(stringStrc->myMutex);
	}
	return (NULL);
}

/*#include <stdlib.h>
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
	thread_t * writerThread;
	thread_t * readerThread;
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
void writer_new(string_t * self) {
	self->writerThread = thread_create_args(writerFunc, self);
}

void writer_free(string_t * self) {
	thread_join(self->writerThread);
	thread_free(self->writerThread);
}

void * writerFunc(void *args) {
	string_t * stringStrc = (string_t *)args;
	int length = strlen(stringStrc->string);
	while (1) {
		mutex_lock(stringStrc->myMutex);
		if (kbhit()) {
			break;
		}
		(stringStrc->index)++;
		if ((stringStrc->index) == length) {
			(stringStrc->index) = (stringStrc->index) % length;
			puts("\nThe end of the string is reached. Start checking again in 3 seconds...");
			Sleep(3000);
		}
		Sleep(30);
		mutex_unlock(stringStrc->myMutex);
	}
	return (NULL);
}

//reader module
void reader_new(string_t * self) {
	self->readerThread = thread_create_args(readerFunc, self);
}

void reader_free(string_t * self) {
	thread_join(self->readerThread);
	thread_free(self->readerThread);
}

void * readerFunc(void *args) {
	string_t * stringStrc = (string_t *)args;
	while (1) {
		mutex_lock(stringStrc->myMutex);
		if (kbhit()) {
			break;
		}
		if (stringStrc->string[stringStrc->index] == 'a' || stringStrc->string[stringStrc->index] == 'A' || stringStrc->string[stringStrc->index] == 'e' || stringStrc->string[stringStrc->index] == 'E' || stringStrc->string[stringStrc->index] == 'i' || stringStrc->string[stringStrc->index] == 'I' || stringStrc->string[stringStrc->index] == 'o' || stringStrc->string[stringStrc->index] == 'O' || stringStrc->string[stringStrc->index] == 'u' || stringStrc->string[stringStrc->index] == 'U') {
			printf("%c", stringStrc->string[stringStrc->index]);
		}
		Sleep(30);
		mutex_unlock(stringStrc->myMutex);
	}
	return (NULL);
}*/