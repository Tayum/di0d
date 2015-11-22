/*In order to work comfortably,
I recommend you to work in a full screen mode
Note, that scale changes on sqrt(2) each time*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

COORD CurrPos;
HANDLE consHndlr;

void axis(int xStart, int yStart, double k);
void cosWave(int xStart, int yStart, double k);
void hyperbole(int xStart, int yStart, double k);
void Funcs(void);

int main(void) {
	int xStart;
	int yStart;
	double k = 1;
	consHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	Funcs();
	xStart = 40;
	yStart = 24;
	axis(xStart, yStart, k);
	cosWave(xStart, yStart,k);
	hyperbole(xStart, yStart,k);
	while (1) {
		char z = getch();
		switch (z) {
		case 'w':
			system("cls");
			Funcs();
			yStart--;
			axis(xStart, yStart, k);
			cosWave(xStart, yStart, k);
			hyperbole(xStart, yStart, k);
			break;
		case 's':
			system("cls");
			Funcs();
			yStart++;
			axis(xStart, yStart, k);
			cosWave(xStart, yStart, k);
			hyperbole(xStart, yStart, k);
			break;
		case 'a':
			system("cls");
			Funcs();
			xStart = xStart - 2;
			axis(xStart, yStart, k);
			cosWave(xStart, yStart, k);
			hyperbole(xStart, yStart, k);
			break;
		case 'd':
			system("cls");
			Funcs();
			xStart = xStart + 2;
			axis(xStart, yStart, k);
			cosWave(xStart, yStart, k);
			hyperbole(xStart, yStart, k);
			break;
		case 'e':
			system("cls");
			Funcs();
			k = k * sqrt(2);
			axis(xStart, yStart, k);
			cosWave(xStart, yStart, k);
			hyperbole(xStart, yStart, k);
			break;
		case 'r':
			system("cls");
			Funcs();
			k = k / sqrt(2);
			axis(xStart, yStart, k);
			cosWave(xStart, yStart, k);
			hyperbole(xStart, yStart, k);
			break;
		default:
			continue;
		}
	}
	return 0;
}

void axis(int xStart, int yStart, double k) {
	double i;
	CurrPos.X = xStart;
	CurrPos.Y = 0;
	double coordX = 0;
	double coordY = 0;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	SetConsoleTextAttribute(consHndlr, FOREGROUND_RED | FOREGROUND_GREEN);
	while (CurrPos.Y <= 48) {
		printf("*");
		coordY = coordY + 2 / k;
		CurrPos.Y=coordY;
		SetConsoleCursorPosition(consHndlr, CurrPos);
	}
	CurrPos.X = 0;
	CurrPos.Y = yStart;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	while (coordX<80) {
		printf("*");
		coordX = coordX + 2/k;
		CurrPos.X = coordX;
		SetConsoleCursorPosition(consHndlr, CurrPos);
	}
}

void cosWave(int xStart, int yStart, double k) {
	int i;
	double x;
	double y=0;
	for (i = 0; i < 80; i++) {
		CurrPos.X = i;
		x = i*0.5 - xStart / 2;
		y = 1.5 * cos(0.2*x*k) * 25 / 3/k;
		CurrPos.Y = yStart - y;
		SetConsoleCursorPosition(consHndlr, CurrPos);
		SetConsoleTextAttribute(consHndlr, BACKGROUND_RED);
		printf(" ");
	}
	SetConsoleTextAttribute(consHndlr, BACKGROUND_RED || BACKGROUND_GREEN || BACKGROUND_BLUE);
}

void hyperbole(int xStart, int yStart, double k) {
	int i;
	double x;
	double y;
	for (i = 0; i < 80; i++) {
		CurrPos.X = i;
		x = i*0.5 - xStart / 2;
		y = (-2 / (4 * x*k - 1) - 1) * 25 / 3/k;
		CurrPos.Y = yStart - y;
		SetConsoleCursorPosition(consHndlr, CurrPos);
		SetConsoleTextAttribute(consHndlr, BACKGROUND_BLUE);
		printf(" ");
	}
	SetConsoleTextAttribute(consHndlr, BACKGROUND_RED || BACKGROUND_GREEN || BACKGROUND_BLUE);
}

void Funcs(void) {
	CurrPos.X = 0;
	CurrPos.Y = 0;
	SetConsoleTextAttribute(consHndlr, FOREGROUND_GREEN);
	puts("F(x) = - 2 / (4 * x - 1) - 1");
	puts("F(x) = 1.5 * cos(0.2 * x)");
	puts("WSAD - center control");
	printf("e r - scale control");
}