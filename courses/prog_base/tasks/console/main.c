#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

COORD CurrPos;
HANDLE consHndlr;
void drawDown(int CoordY, int maxY, int colorCheck);
void drawUp(int CoordY, int maxY, int colorCheck);

int main(void) {
	int CoordX = 0, CoordY = 0;
	int checkX = 0;
	consHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	while (checkX < 40) {
		CurrPos.X = CoordX;
		drawDown(CoordY, 24, checkX);
		CoordX++;
		CoordY = 24;
		CurrPos.X = CoordX;
		drawUp(CoordY, 0, checkX);
		CoordX++;
		CoordY = 0;
		checkX++;
	}
	getchar();
	return 0;
}

void drawDown(int CoordY, int maxY, int colorCheck) {
	while (CoordY <= maxY) {
		CurrPos.Y = CoordY;
		if (((int)(colorCheck / 5) * 5 <= CoordY && CoordY < (int)(colorCheck / 5) * 5 + 5) || ((int)((colorCheck - 10) / 5) * 5 - 5 <= CoordY && CoordY < (int)((colorCheck - 10) / 5) * 5)) {
			SetConsoleTextAttribute(consHndlr, BACKGROUND_RED);
			SetConsoleCursorPosition(consHndlr, CurrPos);
		}
		else if ((int)(colorCheck/5)*5-10<=CoordY && CoordY<(int)(colorCheck/5)*5+5) {
			SetConsoleTextAttribute(consHndlr, BACKGROUND_GREEN || BACKGROUND_RED || BACKGROUND_BLUE);
			SetConsoleCursorPosition(consHndlr, CurrPos);
		}
		else {
			SetConsoleTextAttribute(consHndlr, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE);
			SetConsoleCursorPosition(consHndlr, CurrPos);
		}
		printf("*");
		CoordY++;
		Sleep(10);
	}
}

void drawUp(int CoordY, int maxY, int colorCheck) {
	while (CoordY >= maxY) {
		CurrPos.Y = CoordY;
		if (((int)(colorCheck / 5) * 5 <= CoordY && CoordY < (int)(colorCheck / 5) * 5 + 5) || ((int)((colorCheck - 10) / 5) * 5 - 5 <= CoordY && CoordY < (int)((colorCheck - 10) / 5) * 5)) {
			SetConsoleTextAttribute(consHndlr, BACKGROUND_RED);
			SetConsoleCursorPosition(consHndlr, CurrPos);
		}
		else if ((int)(colorCheck / 5) * 5 - 10 <= CoordY && CoordY<(int)(colorCheck / 5) * 5 + 5) {
			SetConsoleTextAttribute(consHndlr, BACKGROUND_GREEN || BACKGROUND_RED || BACKGROUND_BLUE);
			SetConsoleCursorPosition(consHndlr, CurrPos);
		}
		else {
			SetConsoleTextAttribute(consHndlr, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE);
			SetConsoleCursorPosition(consHndlr, CurrPos);
		}
		printf("*");
		CoordY--;
		Sleep(10);
	}
}