#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nlp.h"

struct word_s {
	char word[25];
	int length;
};

typedef struct word_s word_t;

struct sent_s {
	list_t * wordList;
};

struct text_s {
	char text[10000];
	list_t * sentList;
};

// Counts the amount of lines in the file.
// As far as it is not used in other files, it's static.
// @Returns: SUCCESS if everything is OK and NO_FILE if the file is not found.
static int file_length(const char * frName) {
	int newLine;
	int linesAmount = 0;
	FILE * frPtr = fopen(frName, "r");
	if (frPtr == NULL) {
		return NO_FILE;
	}
	do {
		newLine = fgetc(frPtr);
		if (newLine == '\n') {
			linesAmount++;
		}
	} while (newLine != EOF);
	fclose(frPtr);
	return linesAmount;
}

// ====================WORD STRUCT CREATION====================
// As far as it is not used in other files, it's static.
static word_t * word_new(void) {
	word_t * wordSmp = malloc(sizeof(struct word_s));
	return wordSmp;
}

static void word_free(word_t * self) {
	free(self);
}

// ====================SENT STRUCT CREATION====================
sent_t * sent_new(void) {
	sent_t * sentSmp = malloc(sizeof(struct sent_s));
	sentSmp->wordList = list_new();
	return sentSmp;
}

void sent_free(sent_t * self) {
	int wordAmount = list_getSize(self->wordList);
	for (int i = 0; i < wordAmount; i++) {
		word_free((word_t *)list_pop_back(self->wordList));
	}
	list_free(self->wordList);
	free(self);
}

// ====================TEXT STRUCT CREATION====================
text_t * text_new(void) {
	text_t * textSmp = malloc(sizeof(struct text_s));
	textSmp->sentList = list_new();
	return textSmp;
}

void text_free(text_t * self) {
	int sentAmount = list_getSize(self->sentList);
	for (int i = 0; i < sentAmount; i++) {
		sent_free((sent_t *)list_pop_back(self->sentList));
	}
	list_free(self->sentList);
	free(self);
}

// Adds the text from file to the certain structure.
// @Returns: SUCCESS if everything is OK and NO_FILE if the file is not found.
int text_addText(text_t * self, const char * frName) {
	FILE * frPtr = fopen(frName, "r");
	if (frPtr == NULL) {
		return NO_FILE;
	}
	char buff[10000];
	int fileLength = file_length(frName);
	if (fileLength == NO_FILE) {
		return NO_FILE;
	}
	strcpy(self->text, "");
	for (int i = 0; i < fileLength; i++) {
		fgets(buff, 10000, frPtr);
		strcat(self->text, buff);
	}
	fclose(frPtr);
	return SUCCESS;
}

// Forms the list of word in self->wordList from the given sentence ($sent).
// As far as it is not used in other files, it's static.
static void sent_formListOfWords(sent_t * self, char * sent) {
	char buff[1000];
	strcpy(buff, sent);
	char * token = strtok(buff, ",-!?/();: \"\\");
	while (token != NULL) {
		word_t * newWord = word_new();
		strcpy(newWord->word, token);
		newWord->length = strlen(newWord->word);
		list_push_back(self->wordList, newWord);
		token = strtok(NULL, ",-!?/();: \"\\");
	}
}

// Forms the list of sentences from the text inside the text struct.
//
// Initialises sentences ** array of pointers (every of which
// points to sentence, and then dividing this sentences into words and forming
// the struct list of "sents" in text_t * self.
// It is made in order to avoid using strtok()-cycle for words in strtok()-cycle
// for sentences, as it is forbidden and causes the inappropriate behaviour of the pointer,
// used in strtok.
void text_formListOfSent(text_t * self) {
	char buff[10000];
	strcpy(buff, self->text);
	char * token = strtok(buff, ".\n");
	// Initializing the array of sentences
	char ** sentences = NULL;
	int sentNumber = 0;
	// Dividing the text into sentences and put them down into our array
	// of sentences
	while (token != NULL) {
		sentences = realloc(sentences, (sentNumber + 1)*sizeof(char *));
		sentences[sentNumber] = calloc(1000, sizeof(char));
		strcpy(sentences[sentNumber], token);

		sentNumber++;
		token = strtok(NULL, ".\n");
	}
	// Converting this sentences into "sents" (list of words)
	for (int i = 0; i < sentNumber; i++) {
		sent_t * newSent = sent_new();
		sent_formListOfWords(newSent, sentences[i]);
		list_push_back(self->sentList, newSent);
		free(sentences[i]);
	}
	free(sentences);
}

// Deletes each word from whole text (from each sentence (sentence is a list of words) ),
// which length is (accordingly to task) less than five (5).
void text_deleteWords(text_t * self) {
	int sentAmount = list_getSize(self->sentList);
	for (int i = 0; i < sentAmount; i++) {
		sent_t * sent = (sent_t *)list_get(self->sentList, i);
		int wordsAmount = list_getSize(sent->wordList);
		int index = 0;
		for (int j = 0; j < wordsAmount; j++) {
			word_t * word = (word_t *)list_get(sent->wordList, index);
			if (word->length <= 5) {
				word = (word_t *)list_remove(sent->wordList, index);
				word_free(word);
				index--;
			}
			index++;
		}
	}
}

// Free sent with sent_free() after usage!
// Note: Function DOES NOT create the copy of the list!
// 
// Function that creates another list, deleting pointers from old sentences in text
// and putting them into the new list at proper position (not to lost the sort property). 
// @Returns List with pointers to words filtered in the right order
sent_t * text_sortWords(text_t * self) {
	sent_t * allWords = sent_new();
	int sentAmount = list_getSize(self->sentList);
	for (int i = 0; i < sentAmount; i++) {
		sent_t * sent = (sent_t *)list_get(self->sentList, i);
		int wordsAmount = list_getSize(sent->wordList);
		for (int j = 0; j < wordsAmount; j++) {
			word_t * newWord = (word_t *)list_pop_back(sent->wordList);
			for (int k = 0; k <= list_getSize(allWords->wordList); k++) {
				if (k == list_getSize(allWords->wordList)) {
					list_push_back(allWords->wordList, newWord);
					break;
				}
				word_t * curWord = (word_t *)list_get(allWords->wordList, k);
				if (newWord->length <= curWord->length) {
					list_insert(allWords->wordList, k, newWord);
					break;
				}
			}
		}
	}
	return allWords;
}

// Function that writes the list of words to the given file with ($fwName) name,
// each word on the new line.
// @Returns: SUCCESS if everything is OK and NO_FILE if the file is not found.
int file_writeWordsToFile(sent_t * self, const char * fwName) {
	FILE * fwPtr = fopen(fwName, "w");
	if (fwPtr == NULL) {
		return NO_FILE;
	}
	word_t * curWord;
	int wordsAmount = list_getSize(self->wordList);
	for (int i = 0; i < wordsAmount; i++) {
		curWord = (word_t *)list_pop_back(self->wordList);
		fprintf(fwPtr, "%s\n", curWord->word);
	}
	word_free(curWord);
	fclose(fwPtr);
	return SUCCESS;
}