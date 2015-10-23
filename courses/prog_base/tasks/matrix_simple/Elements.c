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
			MatrixMain[i][j] = rand(5) % 1000 * pow(-1, rand(25));
			printf("%d ", MatrixMain[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d ", MatrixMain[3-j][i]);
		}
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d ", MatrixMain[3-i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (i=0; i<4; i++) {
		for (j=0; j < 4; j++) {
			printf("%d ", MatrixMain[3-j][3-i]);
		}
		printf("\n");
	}
	return 0;
}
