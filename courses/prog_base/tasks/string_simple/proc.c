#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char * process(char * resultStr, const char * textLines[],
	int linesNum, const char * extraStr) {
	int i;
	int indexVar = -1;
	int consConst = -1;
	int vowelConst = -1;
	int index;
	char line[100];
	char * token;
	// finds the index of consonant string
	for (i = 0; i < linesNum; i++) {
		strcpy(line, textLines[i]);
		token = strtok(line, " ");
		while (token != NULL) {
			if (isalpha(token[0]) != 0) {
				if (token[0] == 'a' || token[0] == 'A' || token[0] == 'e' || token[0] == 'E' || token[0] == 'i' || token[0] == 'I' || token[0] == 'o' || token[0] == 'O' || token[0] == 'u' || token[0] == 'U') {
					indexVar = -1;
					break;
				}
				else {
					indexVar = i;
				}
			}
			token = strtok(NULL, " ");
		}
		// if it finds such a string - index is being assigned and the scan is continued
		if (indexVar != -1) {
			consConst = indexVar;
			indexVar = -1;
		}
		//
	}
	//
	// finds the index of vowel string
	for (i = 0; i < linesNum; i++) {
		strcpy(line, textLines[i]);
		token = strtok(line, " ");
		while (token != NULL) {
			if (isalpha(token[0]) != 0) {
				if (token[0] != 'a' && token[0] != 'A' && token[0] != 'e' && token[0] != 'E' && token[0] != 'i' && token[0] != 'I' && token[0] != 'o' && token[0] != 'O' && token[0] != 'u' && token[0] != 'U') {
					indexVar = -1;
					break;
				}
				else {
					indexVar = i;
				}
			}
			token = strtok(NULL, " ");
		}
		// if it finds such a string - index is being assigned and the scan is stopped
		if (indexVar != -1) {
			vowelConst = indexVar;
			break;
		}
		//
	}
	//
	// copies sum of indices and the longest of strings into result string
	sprintf(resultStr, "%d ", consConst + vowelConst);
	//if both indices are "-1", it writes "0 NULL" instead of their sum (-2)
	if (consConst == -1 && vowelConst == -1) {
		strcpy(resultStr, "0 NULL ");
		strcat(resultStr, extraStr);
	}
	//
	else if (consConst != -1 && vowelConst == -1) {
		strcat(resultStr, textLines[consConst]);
	}
	else if (consConst == -1 && vowelConst != -1) {
		strcat(resultStr, textLines[vowelConst]);
	}
	else {
		if (strlen(textLines[consConst]) >= strlen(textLines[vowelConst])) {
			strcat(resultStr, textLines[consConst]);
		}
		else {
			strcat(resultStr, textLines[vowelConst]);
		}
	}
	return resultStr;
	//
}