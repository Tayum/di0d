#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "module.h"

struct line_s {
	char ** line;
	int size;
};

line_t * line_new(int size) {
	line_t * lineSample = malloc(sizeof(struct line_s));
	lineSample->line = calloc(size, sizeof(char *));
	lineSample->size = size;
	return lineSample;
}

void line_free(line_t * self) {
	free(self->line);
	free(self);
}

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

int line_addSent(line_t * self, int index, const char * textLine) {
	if (index<0 || index > self->size) {
		return ERROR;
	}
	self->line = realloc(self->line, (self->size + 1)*(sizeof(char *)));
	int i, j;
	if (self->size > index) {
		for (i = self->size; i > index; i--) {
			self->line[i] = self->line[i - 1];

		}
	}
	self->line[index] = textLine;
	self->size++;
	return OK;
}

int line_deleteSent(line_t * self, int index) {
	if (index<0 || index >= self->size) {
		return ERROR;
	}
	int i, j;
	if (self->size - 1 > index) {
		for (i = index; i < self->size - 1; i++) {
			self->line[i] = self->line[i + 1];
		}
	}
	self->line = realloc(self->line, (self->size - 1)*(sizeof(char *)));
	self->size--;
	return OK;
}

char * line_getLine(char * resultStr, const line_t * self, int index) {
	if (index<0 || index >= self->size) {
		printf("Invalid index: %d!", index);
		strcpy(resultStr, "-1");
		return resultStr;
	}
	strcpy(resultStr, self->line[index]);
	return resultStr;
}

char * line_LongestSent(const line_t * self) {
	int i;
	int length = 0;
	int maxLength = 0;
	int index = 0;
	for (i = 0; i < self->size; i++) {
		length = strlen(self->line[i]);
		if (maxLength <= length) {
			maxLength = length;
			index = i;
		}
	}
	return self->line[index];
}

char * line_LongestWord(char * resultStr, const line_t * self) {
	int i, j;
	int length = 0;
	int maxLength = 0;
	char buffer[100];
	char * token;
	for (i = 0; i < self->size; i++) {
		strcpy(buffer, self->line[i]);
		token = strtok(buffer, " .");
		while (token != NULL) {
			length = strlen(token);
			if (maxLength <= length) {
				strcpy(resultStr, token);
				maxLength = length;
			}
			token = strtok(NULL, " .");
		}
	}
	return resultStr;
}