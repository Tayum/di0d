#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef void(*intCB)(int);
typedef void(*doubleCB)(float, float *);

void procSequence(const char * textLine[], int size, float * floatSum, intCB intNum, doubleCB floatNum);
void intFunc(int intNum);
void floatFunc(float floatNum, float * floatSum);
//TWO NEW-ADDED FUNCTIONS
void intFuncTwo(int intNum);
void floatFuncTwo(float floatNum, float * floatSum);

int main(void) {
	float floatSum = 0;
	char * words[] = { "hello", "5.323", "5", "0.00", "0.666" };
	int length = sizeof(words) / sizeof(words[0]);
	intCB intNum = intFunc;
	doubleCB floatNum = floatFunc;
	procSequence(words, length, &floatSum, intNum, floatNum);
	//"alternative" case:
	puts("\n=============ANOTHER CASE=============\n");
	floatSum = 0;
	intNum = intFuncTwo;
	floatNum = floatFuncTwo;
	procSequence(words, length, &floatSum, intNum, floatNum);
	//END of "alternative" case
	getch();
	return 0;
}

void procSequence(const char * textLine[], int size, float * floatSum, intCB intNum, doubleCB floatNum) {
	int i;
	int intNumber;
	float floatNumber;
	for (i = 0; i < size; i++) {
		printf("=====String to work with=====\n'%s'\n=============================\n", textLine[i]);
		intNumber = atoi(textLine[i]);
		floatNumber = atof(textLine[i]);
		if (intNumber == floatNumber && intNumber != 0) {
			intNum(intNumber);
		}
		else if (floatNumber != 0) {
			floatNum(floatNumber, floatSum);
		}
		else {
			puts("");
			printf("It's not a number at all (or it's '0' number)!\n");
			puts("");
		}
	}
}

void intFunc(int intNum) {
	puts("");
	printf("New added int num: %i\n", intNum);
	puts("");
}

void floatFunc(float floatNum, float * floatSum) {
	(*floatSum) += floatNum;
	puts("");
	printf("New added float num: %f\n", floatNum);
	printf("Sum now: %f\n", *floatSum);
	puts("");
}

//TWO NEW-ADDED FUNCTIONS, SIMILAR (but not the same!) TO THOSE ABOVE: is that the "alternative" you meant?
void intFuncTwo(int intNum) {
	puts("");
	puts("Okay, there we go, I do similar things but I'm not the function that you used!");
	printf("I added new int num: %i\n", intNum);
	puts("");
}

void floatFuncTwo(float floatNum, float * floatSum) {
	(*floatSum) += floatNum;
	puts("");
	puts("Okay, there we go, I do similar things but I'm not the function that you used!");
	printf("I added new float num: %f\n", floatNum);
	printf("And the sum now is next: %f\n", *floatSum);
	puts("");
}