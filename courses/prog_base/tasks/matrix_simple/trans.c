#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

void assignment(int FirstMatrix[4][4], int SecondMatrix[4][4]) {
	int n, i, j = 4;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			SecondMatrix[i][j] = FirstMatrix[i][j];
		}
	}
}

void fillRand(int mat[4][4]) {
	int n, i, j = 4;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			mat[i][j] = rand() % 1000 * pow(-1, rand());
		}
	}
}

void rotateCCW270(int mat[4][4]) {
	int n, i, j = 4;
	int MatrixRotate[4][4];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; i++) {
			MatrixRotate[i][j] = mat[3 - j][i];
		}
	}
	assignment(MatrixRotate, mat);
}

void flipV(int mat[4][4]) {
	int n, i, j = 4;
	int MatrixFlip[4][4];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			MatrixFlip[i][j] = mat[3 - i][j];
		}
	}
	assignment(MatrixFlip, mat);
}

void transposSide(int mat[4][4]) {
	int n, i, j = 4;
	int MatrixTranspos[4][4];
	for (i = 0; i < n; j++) {
		for (j = 0; j < n; j++) {
			MatrixTranspos[i][j] = mat[3 - j][3 - i];
		}
	}
	assignment(MatrixTranspos, mat);
}