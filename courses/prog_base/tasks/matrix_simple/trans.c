#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

void fillRand(int mat[4][4]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			mat[i][j] = rand() % 1000 * pow(-1, rand());
		}
	}
}

void rotateCCW270(int mat[4][4]) {
	int i, j, MatrixRotate[4][4];
	for (j = 0; j < 4; j++) {
		for (i = 3; i >= 0; i--) {
			MatrixRotate[i][j] = mat[i][j];
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			mat[i][j] = MatrixRotate[i][j];
		}
	}
}

void flipV(int mat[4][4]) {
	int i, j, MatrixFlip[4][4];
	for (i = 3; i >= 0; i--) {
		for (j = 0; j < 4; j++) {
			MatrixFlip[i][j] = mat[i][j];
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			mat[i][j] = MatrixFlip[i][j];
		}
	}
}

void transposSide(int mat[4][4]) {
	int i, j, MatrixTranspos[4][4];
	for (j = 3; j >= 0; j--) {
		for (i = 3; i >= 0; i--) {
			MatrixTranspos[i][j] = mat[i][j];
		}
	}
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			mat[i][j] = MatrixTranspos[i][j];
		}
	}
}