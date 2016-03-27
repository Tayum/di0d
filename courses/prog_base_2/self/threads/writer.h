#include "thread.h"

#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED

typedef struct string_s string_t;
typedef thread_t writer_t;
typedef thread_t reader_t;

string_t * string_new(char * smpString);
void string_free(string_t * self);
char * string_getString(char * resultStr, const string_t * self);

writer_t * writer_new(string_t * self);
void writer_free(writer_t * self);
void writer_wait(const writer_t * self);
void * writerFunc(void *args);

reader_t * reader_new(string_t * self);
void reader_free(reader_t * self);
void reader_wait(const reader_t * self);
void * readerFunc(void *args);

#endif //WRITER_H_INCLUDED

/*#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED

#include "mutex.h"

struct string_s {
	char * string;
	mutex_t * myMutex;
	int index;
};

typedef struct string_s string_t;

void * writerFunc(void *args);
void * readerFunc(void *args);

#endif //WRITER_H_INCLUDED*/