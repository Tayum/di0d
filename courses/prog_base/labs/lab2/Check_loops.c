#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846

double calc(int n, int m);

int main(void) {
	int n = 6;
	int m = 9;
	double result;
	result = calc(n, m);
	printf("%lf", result);
	return 0;
}

double calc(int n, int m) {
	double i;
	int j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			x = x + cos(M_PI / i)*i / (j + 1);
		}
	}
	return x;
}