#ifndef NLP_H_INCLUDED
#define NLP_H_INCLUDED

#include "list/list.h"

#define NO_FILE -1
#define SUCCESS 1

typedef struct text_s text_t;
typedef struct sent_s sent_t;

text_t * text_new(void);
void text_free(text_t * self);

sent_t * sent_new(void);
void sent_free(sent_t * self);

int text_addText(text_t * self, const char * frName);
void text_formListOfSent(text_t * self);
void text_deleteWords(text_t * self);
// Free sent with sent_free() after usage!
// Note: Function DOES NOT create the copy of the list!
sent_t * text_sortWords(text_t * self);
int file_writeWordsToFile(sent_t * self, const char * fwName);

#endif // NLP_H_INCLUDED