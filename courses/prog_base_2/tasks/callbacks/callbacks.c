/*22:01:Im really sorry, Ruslan Anatolievich, I was not able to complete my task properly until deadline. But I'm very close
as far as you may see from this code. I will end with this as soon as possible, just, if you can, give me like 2 hours
(at maximum)
Thanks :P
UPD 23:21: Everything is working fine I guess, updating code on GitHub.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef void(*intCB)(int);
typedef void(*doubleCB)(float, float *);

void procSequence(const char * textLine[], int size, float * floatSum, intCB intNum, doubleCB floatNum);
void intFunc(int intNum);
void floatFunc(float floatNum, float * floatSum);

int main(void) {
	float floatSum = 0;
	char * words[] = { "hello", "5.323", "5", "5.000", "0.00", "0.323", "0.323" };
	int length = sizeof(words) / sizeof(words[0]);
	intCB intNum = intFunc;
	doubleCB floatNum = floatFunc;
	procSequence(words, length, &floatSum, intNum, floatNum);
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