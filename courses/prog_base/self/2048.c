#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

COORD CurrPos;
HANDLE consHndlr;

int swipeDown(int matrix[4][4], int matrixCopy[4][4], int score);
int swipeUp(int matrix[4][4], int matrixCopy[4][4], int score);
int swipeRight(int matrix[4][4], int matrixCopy[4][4], int score);
int swipeLeft(int matrix[4][4], int matrixCopy[4][4], int score);
void summonRand(int matrix[4][4]);
int checkLoss(int matrix[4][4]);
void mirrorMatrix(int matrix[4][4], int matrixCopy[4][4]);
int whetherSwipe(int matrix[4][4], int matrixCopy[4][4]);
void printMatrix(int matrix[4][4], int matrixCopy[4][4], int xStart, int yStart);
void drawRectangle(int length, int height, int xStart, int yStart);
void FillUpRect(int matrix[4][4], int matrixCopy[4][4], int length, int height, int xStart, int yStart, int choice);
void clearScore(void);

int main(void) {
	system("cls");
	int matrix[4][4] = { 0 };
	int matrixCopy[4][4];
	int row, col;
	int choice;
	int checkSwipe;
	int lose;
	int score = 0;
	srand(time(NULL));
	consHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	// first init
	row = rand() % 4;
	col = rand() % 4;
	matrix[row][col] = 2;
	do {
		row = rand() % 4;
		col = rand() % 4;
		if (matrix[row][col] == 2) {
			continue;
		}
		else {
			matrix[row][col] = 2;
			break;
		}
	} while (1);
	//
	//constant interface
	CurrPos.X = 0;
	CurrPos.Y = 0;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	SetConsoleTextAttribute(consHndlr, 0 | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	printf("W - swipe UP\n");
	printf("S - swipe DOWN\n");
	printf("A - swipe LEFT\n");
	printf("D - swipe RIGHT");
	mirrorMatrix(matrix, matrixCopy);
	drawRectangle(28, 10, 25, 10);
	FillUpRect(matrix, matrixCopy, 28, 10, 25, 10, 0);
	//
	//* actually game
	do {
		// printf'ing interface
		FillUpRect(matrix, matrixCopy, 28, 10, 25, 10, 1);
		clearScore();
		CurrPos.X = 25;
		CurrPos.Y = 22;
		SetConsoleCursorPosition(consHndlr, CurrPos);
		SetConsoleTextAttribute(consHndlr, 0 | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		printf("Score: ");
		SetConsoleTextAttribute(consHndlr, 0 | FOREGROUND_GREEN);
		printf("%i", score);
		//
		// checking if lost
		lose = checkLoss(matrix);
		if (lose == 1) {		// lose == 1 - person has lost
			clearScore();
			CurrPos.X = 25;
			CurrPos.Y = 22;
			SetConsoleCursorPosition(consHndlr, CurrPos);
			SetConsoleTextAttribute(consHndlr, 0 | FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("Game over!");
			CurrPos.X = 25;
			CurrPos.Y = 23;
			SetConsoleCursorPosition(consHndlr, CurrPos);
			SetConsoleTextAttribute(consHndlr, 0 | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			printf("Your final score: ");
			SetConsoleTextAttribute(consHndlr, 0 | FOREGROUND_GREEN);
			printf("%i", score);
			break;
		}
		else {					// lose == 0 - person did not lose
			// key
			CurrPos.X = 25;
			CurrPos.Y = 24;
			SetConsoleCursorPosition(consHndlr, CurrPos);
			SetConsoleTextAttribute(consHndlr, 0 | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			do {
				choice = getch();
			} while (choice != 'w' && choice != 's' && choice != 'a' && choice != 'd');
			//
			// actual swipe
			switch (choice) {
			case 'w':
				score = swipeUp(matrix, matrixCopy, score);
				break;
			case 's':
				score = swipeDown(matrix, matrixCopy, score);
				break;
			case 'a':
				score = swipeLeft(matrix, matrixCopy, score);
				break;
			case 'd':
				score = swipeRight(matrix, matrixCopy, score);
				break;
			}
			//
			// check if swiped
			checkSwipe = whetherSwipe(matrix, matrixCopy);
			if (checkSwipe == 0) { // swipe == 0 - person didn't swipe
				continue;
			}
			else {					// swipe == 1 - person has swiped
				mirrorMatrix(matrix, matrixCopy);
				summonRand(matrix);
				continue;
			}
			//
		}
	} while (1);
	//* end of "actually game"
	CurrPos.X = 25;
	CurrPos.Y = 25;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	SetConsoleTextAttribute(consHndlr, 0 | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	printf("Press SPACE to exit...");
	do {
		choice = getch();
	} while (choice != ' ');
	system("cls");
	return 0;
}

int swipeDown(int matrix[4][4], int matrixCopy[4][4], int score) {
	mirrorMatrix(matrix, matrixCopy);
	int i;
	for (i = 0; i <= 3; i++) {
		if (matrix[3][i] == matrix[2][i]) {
			matrix[3][i] = matrix[3][i] * 2;
			score = score + matrix[3][i] * 2;
			matrix[2][i] = 0;
		}
		else if (matrix[3][i] == matrix[1][i] && matrix[2][i] == 0) {
			matrix[3][i] = matrix[3][i] * 2;
			score = score + matrix[3][i] * 2;
			matrix[1][i] = 0;
		}
		else if (matrix[3][i] == matrix[0][i] && matrix[2][i] == 0 && matrix[1][i] == 0) {
			matrix[3][i] = matrix[3][i] * 2;
			score = score + matrix[3][i] * 2;
			matrix[0][i] = 0;
		}
		if (matrix[2][i] == matrix[1][i]) {
			matrix[2][i] = matrix[2][i] * 2;
			score = score + matrix[2][i] * 2;
			matrix[1][i] = 0;
		}
		else if (matrix[2][i] == matrix[0][i] && matrix[1][i] == 0) {
			matrix[2][i] = matrix[2][i] * 2;
			score = score + matrix[2][i] * 2;
			matrix[0][i] = 0;
		}
		if (matrix[1][i] == matrix[0][i]) {
			matrix[1][i] = matrix[1][i] * 2;
			score = score + matrix[1][i] * 2;
			matrix[0][i] = 0;
		}
		if (matrix[3][i] == 0 && matrix[2][i] != 0) {
			matrix[3][i] = matrix[2][i];
			matrix[2][i] = 0;
		}
		else if (matrix[3][i] == 0 && matrix[1][i] != 0) {
			matrix[3][i] = matrix[1][i];
			matrix[1][i] = 0;
		}
		else if (matrix[3][i] == 0 && matrix[0][i] != 0) {
			matrix[3][i] = matrix[0][i];
			matrix[0][i] = 0;
		}
		if (matrix[2][i] == 0 && matrix[1][i] != 0) {
			matrix[2][i] = matrix[1][i];
			matrix[1][i] = 0;
		}
		else if (matrix[2][i] == 0 && matrix[0][i] != 0) {
			matrix[2][i] = matrix[0][i];
			matrix[0][i] = 0;
		}
		if (matrix[1][i] == 0 && matrix[0][i] != 0) {
			matrix[1][i] = matrix[0][i];
			matrix[0][i] = 0;
		}
	}
	return score;
}

int swipeUp(int matrix[4][4], int matrixCopy[4][4], int score) {
	mirrorMatrix(matrix, matrixCopy);
	int i;
	for (i = 0; i <= 3; i++) {
		if (matrix[0][i] == matrix[1][i]) {
			matrix[0][i] = matrix[0][i] * 2;
			score = score + matrix[0][i] * 2;
			matrix[1][i] = 0;
		}
		else if (matrix[0][i] == matrix[2][i] && matrix[1][i] == 0) {
			matrix[0][i] = matrix[0][i] * 2;
			score = score + matrix[0][i] * 2;
			matrix[2][i] = 0;
		}
		else if (matrix[0][i] == matrix[3][i] && matrix[1][i] == 0 && matrix[2][i] == 0) {
			matrix[0][i] = matrix[0][i] * 2;
			score = score + matrix[0][i] * 2;
			matrix[3][i] = 0;
		}
		if (matrix[1][i] == matrix[2][i]) {
			matrix[1][i] = matrix[1][i] * 2;
			score = score + matrix[1][i] * 2;
			matrix[2][i] = 0;
		}
		else if (matrix[1][i] == matrix[3][i] && matrix[2][i] == 0) {
			matrix[1][i] = matrix[1][i] * 2;
			score = score + matrix[1][i] * 2;
			matrix[3][i] = 0;
		}
		if (matrix[2][i] == matrix[3][i]) {
			matrix[2][i] = matrix[2][i] * 2;
			score = score + matrix[2][i] * 2;
			matrix[3][i] = 0;
		}
		if (matrix[0][i] == 0 && matrix[1][i] != 0) {
			matrix[0][i] = matrix[1][i];
			matrix[1][i] = 0;
		}
		else if (matrix[0][i] == 0 && matrix[2][i] != 0) {
			matrix[0][i] = matrix[2][i];
			matrix[2][i] = 0;
		}
		else if (matrix[0][i] == 0 && matrix[3][i] != 0) {
			matrix[0][i] = matrix[3][i];
			matrix[3][i] = 0;
		}
		if (matrix[1][i] == 0 && matrix[2][i] != 0) {
			matrix[1][i] = matrix[2][i];
			matrix[2][i] = 0;
		}
		else if (matrix[1][i] == 0 && matrix[3][i] != 0) {
			matrix[1][i] = matrix[3][i];
			matrix[3][i] = 0;
		}
		if (matrix[2][i] == 0 && matrix[3][i] != 0) {
			matrix[2][i] = matrix[3][i];
			matrix[3][i] = 0;
		}
	}
	return score;
}

int swipeRight(int matrix[4][4], int matrixCopy[4][4], int score) {
	mirrorMatrix(matrix, matrixCopy);
	int i;
	for (i = 0; i <= 3; i++) {
		if (matrix[i][3] == matrix[i][2]) {
			matrix[i][3] = matrix[i][3] * 2;
			score = score + matrix[i][3] * 2;
			matrix[i][2] = 0;
		}
		else if (matrix[i][3] == matrix[i][1] && matrix[i][2] == 0) {
			matrix[i][3] = matrix[i][3] * 2;
			score = score + matrix[i][3] * 2;
			matrix[i][1] = 0;
		}
		else if (matrix[i][3] == matrix[i][0] && matrix[i][2] == 0 && matrix[i][1] == 0) {
			matrix[i][3] = matrix[i][3] * 2;
			score = score + matrix[i][3] * 2;
			matrix[i][0] = 0;
		}
		if (matrix[i][2] == matrix[i][1]) {
			matrix[i][2] = matrix[i][2] * 2;
			score = score + matrix[i][2] * 2;
			matrix[i][1] = 0;
		}
		else if (matrix[i][2] == matrix[i][0] && matrix[i][1] == 0) {
			matrix[i][2] = matrix[i][2] * 2;
			score = score + matrix[i][2] * 2;
			matrix[i][0] = 0;
		}
		if (matrix[i][1] == matrix[i][0]) {
			matrix[i][1] = matrix[i][1] * 2;
			score = score + matrix[i][1] * 2;
			matrix[i][0] = 0;
		}
		if (matrix[i][3] == 0 && matrix[i][2] != 0) {
			matrix[i][3] = matrix[i][2];
			matrix[i][2] = 0;
		}
		else if (matrix[i][3] == 0 && matrix[i][1] != 0) {
			matrix[i][3] = matrix[i][1];
			matrix[i][1] = 0;
		}
		else if (matrix[i][3] == 0 && matrix[i][0] != 0) {
			matrix[i][3] = matrix[i][0];
			matrix[i][0] = 0;
		}
		if (matrix[i][2] == 0 && matrix[i][1] != 0) {
			matrix[i][2] = matrix[i][1];
			matrix[i][1] = 0;
		}
		else if (matrix[i][2] == 0 && matrix[i][0] != 0) {
			matrix[i][2] = matrix[i][0];
			matrix[i][0] = 0;
		}
		if (matrix[i][1] == 0 && matrix[i][0] != 0) {
			matrix[i][1] = matrix[i][0];
			matrix[i][0] = 0;
		}
	}
	return score;
}

int swipeLeft(int matrix[4][4], int matrixCopy[4][4], int score) {
	mirrorMatrix(matrix, matrixCopy);
	int i;
	for (i = 0; i <= 3; i++) {
		if (matrix[i][0] == matrix[i][1]) {
			matrix[i][0] = matrix[i][0] * 2;
			score = score + matrix[i][0] * 2;
			matrix[i][1] = 0;
		}
		else if (matrix[i][0] == matrix[i][2] && matrix[i][1] == 0) {
			matrix[i][0] = matrix[i][0] * 2;
			score = score + matrix[i][0] * 2;
			matrix[i][2] = 0;
		}
		else if (matrix[i][0] == matrix[i][3] && matrix[i][1] == 0 && matrix[i][2] == 0) {
			matrix[i][0] = matrix[i][0] * 2;
			score = score + matrix[i][0] * 2;
			matrix[i][3] = 0;
		}
		if (matrix[i][1] == matrix[i][2]) {
			matrix[i][1] = matrix[i][1] * 2;
			score = score + matrix[i][1] * 2;
			matrix[i][2] = 0;
		}
		else if (matrix[i][1] == matrix[i][3] && matrix[i][2] == 0) {
			matrix[i][1] = matrix[i][1] * 2;
			score = score + matrix[i][1] * 2;
			matrix[i][3] = 0;
		}
		if (matrix[i][2] == matrix[i][3]) {
			matrix[i][2] = matrix[i][2] * 2;
			score = score + matrix[i][2] * 2;
			matrix[i][3] = 0;
		}
		if (matrix[i][0] == 0 && matrix[i][1] != 0) {
			matrix[i][0] = matrix[i][1];
			matrix[i][1] = 0;
		}
		else if (matrix[i][0] == 0 && matrix[i][2] != 0) {
			matrix[i][0] = matrix[i][2];
			matrix[i][2] = 0;
		}
		else if (matrix[i][0] == 0 && matrix[i][3] != 0) {
			matrix[i][0] = matrix[i][3];
			matrix[i][3] = 0;
		}
		if (matrix[i][1] == 0 && matrix[i][2] != 0) {
			matrix[i][1] = matrix[i][2];
			matrix[i][2] = 0;
		}
		else if (matrix[i][1] == 0 && matrix[i][3] != 0) {
			matrix[i][1] = matrix[i][3];
			matrix[i][3] = 0;
		}
		if (matrix[i][2] == 0 && matrix[i][3] != 0) {
			matrix[i][2] = matrix[i][3];
			matrix[i][3] = 0;
		}
	}
	return score;
}

void summonRand(int matrix[4][4]) {
	int row, col;
	do {
		row = rand() % 4;
		col = rand() % 4;
		if (matrix[row][col] != 0) {
			continue;
		}
		else {
			matrix[row][col] = 2;
			break;
		}
	} while (1);
}

// Don't look here... :D
int checkLoss(int matrix[4][4]) {
	if (matrix[0][0] == 0 || matrix[0][0] == matrix[0][1] || matrix[0][0] == matrix[1][0]) {
		return 0;
	}
	else if (matrix[0][3] == 0 || matrix[0][3] == matrix[0][2] || matrix[0][3] == matrix[1][3]) {
		return 0;
	}
	else if (matrix[3][0] == 0 || matrix[3][0] == matrix[2][0] || matrix[3][0] == matrix[3][1]) {
		return 0;
	}
	else if (matrix[3][3] == 0 || matrix[3][3] == matrix[3][2] || matrix[3][3] == matrix[2][3]) {
		return 0;
	}
	else if (matrix[0][1] == 0 || matrix[0][1] == matrix[0][2] || matrix[0][1] == matrix[1][1]) {
		return 0;
	}
	else if (matrix[0][2] == 0 || matrix[0][2] == matrix[1][2]) {
		return 0;
	}
	else if (matrix[3][1] == 0 || matrix[3][1] == matrix[3][2] || matrix[3][1] == matrix[2][1]) {
		return 0;
	}
	else if (matrix[3][2] == 0 || matrix[3][2] == matrix[2][2]) {
		return 0;
	}
	else if (matrix[1][0] == 0 || matrix[1][0] == matrix[2][0] || matrix[1][0] == matrix[1][1]) {
		return 0;
	}
	else if (matrix[2][0] == 0 || matrix[2][0] == matrix[2][1]) {
		return 0;
	}
	else if (matrix[1][3] == 0 || matrix[1][3] == matrix[2][3] || matrix[1][3] == matrix[1][2]) {
		return 0;
	}
	else if (matrix[2][3] == 0 || matrix[2][3] == matrix[2][2]) {
		return 0;
	}
	else if (matrix[1][1] == 0 || matrix[1][1] == matrix[1][2] || matrix[1][1] == matrix[2][1]) {
		return 0;
	}
	else if (matrix[1][2] == 0 || matrix[1][2] == matrix[2][2]) {
		return 0;
	}
	else if (matrix[2][2] == 0 || matrix[2][2] == matrix[2][1]) {
		return 0;
	}
	else if (matrix[2][1] == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

void mirrorMatrix(int matrix[4][4], int matrixCopy[4][4]) {
	int i, j;
	for (i = 0; i <= 3; i++) {
		for (j = 0; j <= 3; j++) {
			matrixCopy[i][j] = matrix[i][j];
		}
	}
}

int whetherSwipe(int matrix[4][4], int matrixCopy[4][4]) {
	int i, j;
	for (i = 0; i <= 3; i++) {
		for (j = 0; j <= 3; j++) {
			if (matrix[i][j] != matrixCopy[i][j]) {
				return 1;
			}
		}
	}
	return 0;
}

// interface functions go here:

void printMatrix(int matrix[4][4], int matrixCopy[4][4], int xStart, int yStart) {
	int i, j;
	for (i = 0; i <= 3; i++) {
		CurrPos.X = xStart + 2;
		CurrPos.Y = yStart + 2 + 2 * i;
		SetConsoleCursorPosition(consHndlr, CurrPos);
		for (j = 0; j < 3; j++) {
			if (matrix[i][j] == matrixCopy[i][j]) {
				SetConsoleTextAttribute(consHndlr, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED);
				printf("%i\t", matrix[i][j]);
			}
			else {
				SetConsoleTextAttribute(consHndlr, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				printf("%i\t", matrix[i][j]);
			}
		}
		if (matrix[i][j] == matrixCopy[i][j]) {
			SetConsoleTextAttribute(consHndlr, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED);
			printf("%i", matrix[i][j]);
		}
		else {
			SetConsoleTextAttribute(consHndlr, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			printf("%i", matrix[i][j]);
		}
	}
}

void drawRectangle(int length, int height, int xStart, int yStart) {
	SetConsoleTextAttribute(consHndlr, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_RED);
	int i;
	for (i = 0; i < length; i++) {
		CurrPos.X = xStart + i;
		CurrPos.Y = yStart;
		SetConsoleCursorPosition(consHndlr, CurrPos);
		printf("*");
		CurrPos.Y = yStart + height;
		SetConsoleCursorPosition(consHndlr, CurrPos);
		printf("*");
	}
	for (i = 0; i <= height; i++) {
		CurrPos.X = xStart;
		CurrPos.Y = yStart + i;
		SetConsoleCursorPosition(consHndlr, CurrPos);
		printf("*");
		CurrPos.X = xStart + length;
		SetConsoleCursorPosition(consHndlr, CurrPos);
		printf("*");
	}
}

void FillUpRect(int matrix[4][4], int matrixCopy[4][4], int length, int height, int xStart, int yStart, int choice) {
	SetConsoleTextAttribute(consHndlr, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	int i, j;
	switch (choice) {
	case 0:
		CurrPos.X = xStart + 1;
		CurrPos.Y = yStart + 1;
		for (i = 0; i < length; i++) {
			for (j = 0; j < height - 1; j++) {
				CurrPos.Y = yStart + 1 + j;
				SetConsoleCursorPosition(consHndlr, CurrPos);
				printf(" ");
			}
			CurrPos.X = xStart + 1 + i;
			CurrPos.Y = yStart + 1;
		}
		printMatrix(matrix, matrixCopy, xStart, yStart);
	case 1:
		CurrPos.X = xStart + 2;
		CurrPos.Y = yStart + 2;
		for (i = 0; i < length-1; i++) {
			for (j = 0; j < height - 2; j=j+2) {
				CurrPos.Y = yStart + 2 + j;
				SetConsoleCursorPosition(consHndlr, CurrPos);
				printf(" ");
			}
			CurrPos.X = xStart + 2 + i;
			CurrPos.Y = yStart + 2;
		}
		printMatrix(matrix, matrixCopy, xStart, yStart);
	}
}

void clearScore(void) {
	int i;
	CurrPos.X = 25;
	CurrPos.Y = 22;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	SetConsoleTextAttribute(consHndlr, 0);
	for (i = 0; i < 8; i++) {
		printf("                                                                              \n");
	}
}