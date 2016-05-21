#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "nlp.h"

int main(void) {
	text_t * myText = text_new();

	int fileCheck = text_addText(myText, "inputText.txt");
	if (fileCheck == NO_FILE) {
		printf("Cannot open file.\n");
		text_free(myText);
		getch();
		return 0;
	}

	text_formListOfSent(myText);
	text_deleteWords(myText);
	sent_t * mySent = text_sortWords(myText);

	fileCheck = file_writeWordsToFile(mySent, "outputText.txt");
	if (fileCheck == NO_FILE) {
		printf("Cannot open file.\n");
		sent_free(mySent);
		text_free(myText);
		getch();
		return 0;
	}

	// END of program
	sent_free(mySent);
	text_free(myText);
	printf("\n\nPress ANY KEY to exit the program...");
	getch();
	return 0;
}