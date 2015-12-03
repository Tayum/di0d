#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#ifdef WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

COORD CurrPos;
HANDLE consHndlr;
void fillMatrix(int arr[], int Row, int Col, int LB, int UB);
void printMatrix(int arr[], int arr2[], int Row, int Col);
void copyMatrix(int arr[], int arr2[], int Row, int Col);
void resetMatrix(int arr[], int Row, int Col);
void chngElement(int arr[], int Row, int Col, int n, int m, int k);
void flipV(int arr[], int Row, int Col);
double avgMean(int arr[], int Row, int Col);
int sumRow(int arr[], int Col, int n);
void ChngMinMax(int arr[], int Row, int Col, int n);
void ChngCol(int arr[], int Row, int Col);
void drawRectangle(int length, int height, int xStart, int yStart, int start);
void FillUpRect(int length, int height, int xStart, int yStart, int start);
void ReDraw(int arr[], int arr2, int Row, int Col);
void clearInput(void);

int main(void) {
	int sizeRow = 0;
	int sizeCol = 0;
	int LB = -35;
	int UB = 100;
	int status = 0;
	char nums[4][20];
	int index1 = 0, index2 = 0, toIndex = 0, sum = 0;
	srand(time(NULL));
	consHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	//START SCREEN
	drawRectangle(40, 8, 20, 10, 0);
	FillUpRect(40, 8, 20, 10, 0);
	SetConsoleTextAttribute(consHndlr, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	CurrPos.X = 21;
	CurrPos.Y = 11;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	printf("Enter matrix size: Rows:[1..13];");
	CurrPos.X = 21;
	CurrPos.Y = 12;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	printf("Columns:[1..8], separated by space,");
	CurrPos.X = 21;
	CurrPos.Y = 13;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	printf("for example '5 8':");
	CurrPos.X = 21;
	CurrPos.Y = 14;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	printf(">>");
	//SCANF ROWS COLUMNS
	do {
		status = scanf("%s %s", &nums[0], &nums[1]);
		sizeRow = atoi(nums[0]);
		sizeCol = atoi(nums[1]);
		if (sizeRow > 13 || sizeRow <= 0 || sizeCol > 8 || sizeCol <= 0) {
			CurrPos.X = 21;
			CurrPos.Y = 16;
			SetConsoleCursorPosition(consHndlr, CurrPos);
			SetConsoleTextAttribute(consHndlr, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
			printf("Invalid input, pls, try again\n");
			CurrPos.X = 23;
			CurrPos.Y = 14;
			SetConsoleCursorPosition(consHndlr, CurrPos);
			printf("                                     ");
			CurrPos.X = 23;
			CurrPos.Y = 14;
			SetConsoleCursorPosition(consHndlr, CurrPos);
			SetConsoleTextAttribute(consHndlr, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			status = 0;
		}
	} while (status < 2);
	//END OF SCANF
	int *Matrix = malloc(sizeof(int)*sizeRow*sizeCol);
	int *MatrixCopy = malloc(sizeof(int)*sizeRow*sizeCol);
	resetMatrix(MatrixCopy, sizeRow, sizeCol);
	//SECOND SCREEN
	SetConsoleTextAttribute(consHndlr, BACKGROUND_GREEN || BACKGROUND_BLUE || BACKGROUND_RED);
	system(CLEAR_SCREEN);
	drawRectangle(79, 15, 0, 0, 1);
	FillUpRect(79, 15, 0, 0, 1);
	fillMatrix(Matrix, sizeRow, sizeCol, LB, UB);
	CurrPos.X = 10;
	CurrPos.Y = 1;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	printMatrix(Matrix, MatrixCopy, sizeRow, sizeCol);
	//FIELD TO ENTER COMMANDS
	CurrPos.X = 0;
	CurrPos.Y = 17;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	SetConsoleTextAttribute(consHndlr, BACKGROUND_GREEN || BACKGROUND_BLUE || BACKGROUND_RED);
	SetConsoleTextAttribute(consHndlr, FOREGROUND_RED | FOREGROUND_GREEN);
	printf("Pls, enter your command (type help for more info)\n>>");
	//ELSEIF LADDER OF COMMANDS
	while (1) {
		SetConsoleTextAttribute(consHndlr, FOREGROUND_BLUE | FOREGROUND_GREEN);
		CurrPos.X = 2;
		CurrPos.Y = 18;
		SetConsoleCursorPosition(consHndlr, CurrPos);
		scanf("%s", &nums[0]);
		puts("");
		//help case
		if (strcmp(nums[0], "help") == 0) {
			printf("reset\t\tresets all matrix elements to zeros\n");
			printf("rand $a $b\tfills matrix in the range [$a..$b]\n");
			printf("change $a $b $c\tchanges el. with index [$a][$b] to $c {first index is [0][0]!}\n");
			printf("flipV\t\tflips matrix vertically\n");
			printf("avg\t\tshows average mean of matrix\n");
			printf("sum $a\t\tshows sum of $a row\n");
			printf("swap\t\tswaps first min and last max elements\n");
			printf("swapInv\t\tswaps last min and first max elements\n");
			printf("swapCol\t\tswaps columns with biggest and lowest sums\n");
			printf("exit\t\texits the program\n");
			printf("Press any key to continue...");
			getch();
			clearInput();
		}
		//reset case
		else if (strcmp(nums[0], "reset") == 0) {
			resetMatrix(Matrix, sizeRow, sizeCol);
			ReDraw(Matrix, MatrixCopy, sizeRow, sizeCol);
		}
		//flipV case
		else if (strcmp(nums[0], "flipV") == 0) {
			flipV(Matrix, sizeRow, sizeCol);
			ReDraw(Matrix, MatrixCopy, sizeRow, sizeCol);
		}
		//mean value case
		else if (strcmp(nums[0], "avg") == 0) {
			CurrPos.X = 2;
			CurrPos.Y = 20;
			SetConsoleCursorPosition(consHndlr, CurrPos);
			printf("Average value of matrix is: ");
			SetConsoleTextAttribute(consHndlr, FOREGROUND_GREEN);
			printf("%.8f  ", avgMean(Matrix, sizeRow, sizeCol));
			SetConsoleTextAttribute(consHndlr, FOREGROUND_BLUE | FOREGROUND_GREEN);
			printf("Press any key to continue...");
			getch();
			clearInput();
		}
		//swap case
		else if (strcmp(nums[0], "swap") == 0) {
			ChngMinMax(Matrix, sizeRow, sizeCol, 0);
			ReDraw(Matrix, MatrixCopy, sizeRow, sizeCol);
		}
		//swap inverted case
		else if (strcmp(nums[0], "swapInv") == 0) {
			ChngMinMax(Matrix, sizeRow, sizeCol, 1);
			ReDraw(Matrix, MatrixCopy, sizeRow, sizeCol);
		}
		//swap columns case
		else if (strcmp(nums[0], "swapCol") == 0) {
			ChngCol(Matrix, sizeRow, sizeCol);
			ReDraw(Matrix, MatrixCopy, sizeRow, sizeCol);
		}
		//fillrand case
		else if (strcmp(nums[0], "rand") == 0) {
			scanf("%s %s", &nums[1], &nums[2]);
			LB = atoi(nums[1]);
			UB = atoi(nums[2]);
			if (UB < LB) {
				printf("Invalid borders, pls, try again\n");
				printf("Press any key to continue...\n");
				getch();
				clearInput();
				continue;
			}
			printf("You will fill matrix with elements bordered by:[%i..%i]\n", LB, UB);
			printf("Press any key to continue...\n");
			getch();
			if ((LB == 0 && LB == UB) || (UB == 0 && LB == UB)) {
				resetMatrix(Matrix, sizeRow, sizeCol);
			}
			else {
				fillMatrix(Matrix, sizeRow, sizeCol, LB, UB);
			}
			ReDraw(Matrix, MatrixCopy, sizeRow, sizeCol);
			clearInput();
		}
		//change by index case
		else if (strcmp(nums[0], "change") == 0) {
				scanf("%s %s %s", &nums[1], &nums[2], &nums[3]);
				index1 = atoi(nums[1]);
				index2 = atoi(nums[2]);
				toIndex = atoi(nums[3]);
				if ((index1 > (sizeRow - 1) || index1 <= 0) || (index2 > (sizeCol - 1) || index2 <= 0)) {
				printf("Invalid index, pls, try again\n");
				printf("Press any key to continue...\n");
				getch();
				clearInput();
				continue;
			}
			else {
				printf("You are going to change element with index [%i][%i] to [%i]\n", index1, index2, toIndex);
				printf("Press any key to continue...\n");
				getch();
				chngElement(Matrix, sizeRow, sizeCol, index1, index2, toIndex);
				ReDraw(Matrix, MatrixCopy, sizeRow, sizeCol);
				clearInput();
			}
		}
		//sum row case
		else if (strcmp(nums[0], "sum") == 0) {
			scanf("%s", &nums[1]);
			sum = atoi(nums[1]);
			if (sum > sizeRow || sum <= 0) {
				printf("Invalid row, pls, try again\n");
				printf("Press any key to continue...\n");
				getch();
				clearInput();
			}
			else {
				CurrPos.X = 2;
				CurrPos.Y = 20;
				SetConsoleTextAttribute(consHndlr, FOREGROUND_GREEN);
				printf("Sum of the %i row is: %i\n", sum, sumRow(Matrix, sizeCol, sum));
				SetConsoleTextAttribute(consHndlr, FOREGROUND_BLUE | FOREGROUND_GREEN);
				printf("Press any key to continue...");
				getch();
				clearInput();
			}
		}
		//exit case
		else if (strcmp(nums[0], "exit") == 0) {
			break;
		}
		//invalid input case
		else {
			CurrPos.X = 0;
			CurrPos.Y = 20;
			SetConsoleCursorPosition(consHndlr, CurrPos);
			printf("Invalid input. Pls, try again\n");
			printf("Press any key to continue...");
			getch();
			clearInput();
		}
	}
	free(Matrix);
	free(MatrixCopy);
	return 0;
}

void fillMatrix(int arr[], int Row, int Col, int LB, int UB) {
	int i, j;
	for (i = 0; i < Row; i++) {
		for (j = 0; j < Col; j++) {
			do {
				arr[i*Col + j] = rand()*pow(-1, rand());
			} while (arr[i*Col + j] < LB || arr[i*Col + j] > UB);
		}
	}
}

void printMatrix(int arr[], int arr2[], int Row, int Col) {
	int i, j;
	for (i = 0; i < Row; i++) {
		CurrPos.X = 1;
		CurrPos.Y = 1 + i;
		SetConsoleCursorPosition(consHndlr, CurrPos);
		printf("\t");
		for (j = 0; j < Col; j++) {
			if (arr[i*Col + j] != arr2[i*Col + j]) {
				SetConsoleTextAttribute(consHndlr, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN);
			}
				printf("%i\t", arr[i*Col + j]);
				SetConsoleTextAttribute(consHndlr, FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
			}
	}
	copyMatrix(arr, arr2, Row, Col);
}

void copyMatrix(int arr[], int arr2[], int Row, int Col) {
	int i, j;
	for (i = 0; i < Row; i++) {
		for (j = 0; j < Col; j++) {
			arr2[i*Col + j] = arr[i*Col + j];
		}
	}
}

void resetMatrix(int arr[], int Row, int Col) {
	int i, j;
	for (i = 0; i < Row; i++) {
		for (j = 0; j < Col; j++) {
			arr[i*Col + j] = 0;
		}
	}
}

void chngElement(int arr[], int Row, int Col, int n, int m, int k) {
	arr[n*Col + m] = k;
}

void flipV(int arr[], int Row, int Col) {
	int i, j;
	int tmp = 0;
	for (i = 0; i < Row/2; i++) {
		for (j = 0; j < Col; j++) {
			 tmp = arr[i*Col + j];
			arr[i*Col + j] = arr[Col*(Row - 1 - i) + j];
			arr[Col*(Row - 1 - i) + j] = tmp;
		}
	}
}

double avgMean(int arr[], int Row, int Col) {
	int i, j;
	int sum = 0;
	for (i = 0; i < Row; i++) {
		for (j = 0; j < Col; j++) {
			sum=sum+arr[i*Col + j];
		}
	}
	sum = (sum + 0.0) / (Col*Row);
	return sum;
}

int sumRow(int arr[], int Col, int n) {
	int j;
	int sum = 0;
	for (j = 0; j < Col; j++) {
		sum = sum + arr[(n - 1)*Col + j];
	}
	return sum;
}

void ChngMinMax(int arr[], int Row, int Col, int n) {
	int i, j;
	int indMin = 0;
	int indMax = 0;
	int min = arr[0];
	int max = arr[0];
	int tmp = 0;
	switch (n) {
	case 0:
		for (i = 0; i < Row; i++) {
			for (j = 0; j < Col; j++) {
				if (arr[i*Col + j] < min) {
					min = arr[i*Col + j];
					indMin = i*Col + j;
				}
				if (arr[i*Col + j] >= max) {
					max = arr[i*Col + j];
					indMax = i*Col + j;
				}
			}
		}
		break;
	case 1:
		for (i = 0; i < Row; i++) {
			for (j = 0; j < Col; j++) {
				if (arr[i*Col + j] <= min) {
					min = arr[i*Col + j];
					indMin = i*Col + j;
				}
				if (arr[i*Col + j] > max) {
					max = arr[i*Col + j];
					indMax = i*Col + j;
				}
			}
		}
		break;
	}
	tmp = arr[indMin];
	arr[indMin] = arr[indMax];
	arr[indMax] = tmp;
}

void ChngCol(int arr[], int Row, int Col) {
	int i, j;
	int sum = 0;
	int sumMin = 0;
	int sumMax = 0;
	for (i = 0; i < Row; i++) {
		sumMin = sumMin + arr[i*Col];
	}
	sumMax = sumMin;
	int indMin = 0, indMax = 0;
	int tmp = 0;
	for (j = 1; j < Col; j++) {
		for (i = 0; i < Row; i++) {
			sum = sum + arr[j + i*Col];
		}
			if (sum < sumMin) {
				sumMin = sum;
				indMin = j;
			}
			if (sum >= sumMax) {
				sumMax = sum;
				indMax = j;
			}
			sum = 0;
	}
	for (i = 0; i < Row; i++) {
		tmp = arr[i*Col + indMin];
		arr[i*Col + indMin] = arr[i*Col + indMax];
		arr[i*Col + indMax] = tmp;
	}
}

void drawRectangle(int length, int height, int xStart, int yStart, int start) {
	switch (start) {
	case 0:
		SetConsoleTextAttribute(consHndlr, BACKGROUND_GREEN | BACKGROUND_BLUE); break;
	case 1:
		SetConsoleTextAttribute(consHndlr, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE); break;
	}
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

void FillUpRect(int length, int height, int xStart, int yStart, int start) {
	switch (start) {
	case 0:
		SetConsoleTextAttribute(consHndlr, BACKGROUND_GREEN | BACKGROUND_BLUE); break;
	case 1:
		SetConsoleTextAttribute(consHndlr, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE); break;
	}
	int i,j;
	CurrPos.X = xStart + 1;
	CurrPos.Y = yStart + 1;
	for (i = 0; i < length; i++) {
		for (j = 0; j < height-1; j++) {
			CurrPos.Y = yStart + 1 + j;
			SetConsoleCursorPosition(consHndlr, CurrPos);
			printf(" ");
		}
		CurrPos.X = xStart + 1 + i;
		CurrPos.Y = yStart + 1;
	}
}

void ReDraw(int arr[], int arr2, int Row, int Col) {
	CurrPos.X = 1;
	CurrPos.Y = 1;
	FillUpRect(70, 13, 5, 1, 1);
	CurrPos.X = 10;
	CurrPos.Y = 1;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	printMatrix(arr, arr2, Row, Col);
	CurrPos.X = 2;
	CurrPos.Y = 18;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	SetConsoleTextAttribute(consHndlr, BACKGROUND_GREEN || BACKGROUND_BLUE || BACKGROUND_RED);
	printf("                                                                              ");
}

void clearInput(void) {
	int z;
	CurrPos.X = 2;
	CurrPos.Y = 18;
	SetConsoleCursorPosition(consHndlr, CurrPos);
	for (z = 0; z < 12; z++) {
		printf("                                                                              \n");
	}
}