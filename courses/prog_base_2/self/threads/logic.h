#pragma once

#include "mutex.h"

struct string_s
{
	char * string;
	mutex_t * myMutex;
	int index;
};

typedef struct string_s string_t;

void * writerFunc(void *args);
void * readerFunc(void *args);


/*#pragma once

#include "mutex.h"

#define SHARED_ARR_SIZE 4
#define SLEEP_TIME 30
#ifndef TRUE
#define TRUE 1
#endif

typedef struct sharedObj_s
{
	unsigned arr[SHARED_ARR_SIZE];
	mutex_t *mu;
} sharedObj_t;

void *producerFunc(void *args);
void *consumerFunc(void *args);*/