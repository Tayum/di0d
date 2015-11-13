#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846

double calc(int n, int m) {
	double x=0;
	double i;
	int j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			x = x + cos(M_PI / i)*i / (j + 1);
		}
	}
	return x;
}