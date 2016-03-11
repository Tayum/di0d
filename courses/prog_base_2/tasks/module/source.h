#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED

typedef struct line_s line_t;

line_t * line_new(int size);
void line_free(line_t * self);

int line_getSize(const line_t * self);
void line_deleteSent(line_t * self, int index);
void line_addSent(line_t * self, int index, const char * textLine);
char * line_LongestSent(const line_t * self);
char * line_LongestWord(char * resultStr, const line_t * self);

void line_fill(line_t * self);
void line_print(const line_t * self);


#endif //SOURCE_H_INCLUDED