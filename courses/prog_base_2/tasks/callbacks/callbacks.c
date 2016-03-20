/*Im really sorry, Ruslan Anatolievich, I was not able to complete my task properly until deadline. But I'm very close
as far as you may see from this code. I will end with this as soon as possible, just, if you can, give me like 2 hours
(at maximum)
Thanks :P*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef void (* intCB)(int);
typedef void (* doubleCB)(float);

void isNumber(const char * textLine[], int size, intCB intNum, doubleCB floatNum);
void intFunc(int intNum);
void floatFunc(float floatNum);

int main(void) {
	char * words [] = { "hello", "5.323", "5", "5.000", "0.00", "0.323"};
	int length = sizeof(words) / sizeof(words[0]);
	intCB intNum = intFunc;
	doubleCB floatNum = floatFunc;
	isNumber(words, length, intNum, floatNum);
	getch();
	return 0;
}

void isNumber(const char * textLine[], int size, intCB intNum, doubleCB floatNum) {
	int intNumberNew;
	float floatNumberNew;
	float floatSum=0;
	for (int i = 0; i < size; i++) {
		intNumberNew = atoi(textLine[i]);
		floatNumberNew = atof(textLine[i]);
		if (intNumberNew == floatNumberNew && intNumberNew != 0) {
			intNum(intNumberNew);
		}
		else if (floatNumberNew != 0) {
			floatNum(floatNumberNew);
		}
		else {
			puts("");
			printf("It's not a number at all (or it's '0' number)!\n");
			puts("");
		}
	}
	return 0;
}

void intFunc(int intNum) {
	printf("int num: %i\n", intNum);
}

void floatFunc(float floatNum) {
	printf("float num: %f\n", floatNum);
}