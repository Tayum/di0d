#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

enum erCodes {
	ERROR = -1,
	OK = 0,
};

typedef struct line_s line_t;

line_t * line_new(int size);
void line_free(line_t * self);

int line_getSize(const line_t * self);
int line_deleteSent(line_t * self, int index);
int line_addSent(line_t * self, int index, const char * textLine);
char * line_LongestSent(const line_t * self);
char * line_LongestWord(char * resultStr, const line_t * self);

void line_fill(line_t * self);
void line_print(const line_t * self);

char * line_getLine(char * resultStr, const line_t * self, int index);


#endif //MODULE_H_INCLUDED