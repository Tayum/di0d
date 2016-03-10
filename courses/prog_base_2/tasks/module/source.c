/*Description/question to some comments below (read it after reading the questions below, please):
As far as I understand, when I use "lineSample->line = calloc(size, sizeof(char *));",
I create an array of pointers, in which it is exactly (size) pointers.
After the creating they are pointing to nothing(to NULL?)...
So how the hack can the program work/run properly, if I do not
allocate memory for every of pointer with the line "lineSample->line[i] = calloc(100, sizeof(char));"?
Does the memory is allocated immideately when it see the line it should be allocated for?
Like, when I write "self->line[0] = "0 sample of text here.";", it allocates
certain(definite) memory for that line?
Then it's a question, again: Shouldn't I free() EVERY pointer of this array of pointers?
Or does the free(self->line) "i tak" free()'s every of the pointer in this array?
*/




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "source.h"

struct line_s {
	char ** line;
	int size;
};

line_t * line_new(int size) {				//CHECK IT PLS
	line_t * lineSample = malloc(sizeof(struct line_s));
	lineSample->line = calloc(size, sizeof(char *));
	//WHY DOES IT WORK WITHOUT THIS CYCLE? WTF
	/*for (int i = 0; i < size; i++) {
		lineSample->line[i] = calloc(100, sizeof(char));
	}*/
	lineSample->size = size;
	return lineSample;
}

void line_free(line_t * self) {				//CHECK IT PLS
	free(self->line);						//Shouldn't I free() a couple of pointers that I created
	free(self);								//here by using cycle, like free(self->line[i]) for (i=0, i<size, i++)?
}											//it says "srabativanie tochki ostanova" if I do that

void line_fill(line_t * self) {

	self->line[0] = "0 sample of text here.";
	self->line[1] = "1 sample of text here.";
	self->line[2] = "2 sample of text here.";
	self->line[3] = "3 sample of text here.";
	self->line[4] = "4 sample of text here.";
}

void line_print(const line_t * self) {
	for (int i = 0; i < self->size; i++) {
		printf("%d)%s\n", i, self->line[i]);
	}
}

int line_getSize(const line_t * self) {
	return self->size;
}

void line_addSent(line_t * self, int index, const char * textLine) {
	self->line = realloc(self->line, (self->size + 1)*(sizeof(char *)));
	//self->line[self->size] = calloc(100, sizeof(char));	//same question here as it was with cycle in "line_t * line_new(int size)"
	int i, j;
	if (self->size > index) {
		for (i = self->size; i > index; i--) {
			self->line[i] = self->line[i - 1];

		}
	}
	self->line[index] = textLine;
	self->size++;
}

void line_deleteSent(line_t * self, int index) {
	int i, j;
	if (self->size-1 > index) {
		for (i = index; i < self->size-1; i++) {
				self->line[i] = self->line[i + 1];
		}
	}
	self->line = realloc(self->line, (self->size - 1)*(sizeof(char *)));
	self->size--;
}

char * line_LongestSent(const line_t * self) {
	int i;
	int length = 0;
	int maxLength = 0;
	int index = 0;
	for (i = 0; i < self->size; i++) {
		length=strlen(self->line[i]);
		if (maxLength <= length) {
			maxLength = length;
			index = i;
		}
	}
	return self->line[index];
}

char * line_LongestWord(const line_t * self) {
	int i, j;
	int length = 0;
	int maxLength = 0;
	char word[20];
	char buffer[100];
	char * token;
	for (i = 0; i < self->size; i++) {
		strcpy(buffer, self->line[i]);
		token = strtok(buffer, " .");		//It is said in my task that I should use every non-alphabetical symbol as the delimiter (separator),
		while (token != NULL) {				//how can I add EVERY non-alphabetical symbol for token as a delimiter? I tried to use !"abc...XYZ",
			length=strlen(token);			//but that results in the error. It can be done without a token, I guess, but it would be really hard
			if (maxLength <= length) {
				strcpy(word, token);
				maxLength = length;
			}
			token = strtok(NULL, " .");
		}
	}
	free(token);
	return word;
}