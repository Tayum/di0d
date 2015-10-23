#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

int main() {
	int i, j;
	int MatrixMain[4][4];
	srand(time(0));
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			MatrixMain[i][j] = rand(5)%1000*pow(-1,rand(25));
			printf("%d ", MatrixMain[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (j = 0; j < 4; j++) {
		for (i = 3; i >= 0; i--) {
			printf("%d ", MatrixMain[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (i = 3; i >= 0 ; i--) {
		for (j = 0; j < 4; j++) {
			printf("%d ", MatrixMain[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (j = 3; j >= 0; j--) {
		for (i = 3; i >= 0; i--) {
			printf("%d ", MatrixMain[i][j]);
		}
		printf("\n");
	}
	return 0;
}