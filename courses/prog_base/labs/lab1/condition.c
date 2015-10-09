#include <math.h>

int satisfies(int a, int b, int c) {
	int result;
		int modmin = 0, sum2 = 0, max = 0, min = 0;		//New variables
	if (a < 0 && b < 0 && c < 0) {		//всі числа (a, b, c) від’ємні
		if (a < b && a < c) {
			modmin = abs(a);
			sum2 = b + c;
		}
		else if (b < a && b < c) {
			modmin = abs(b);
			sum2 = a + c;
		}
		else if (c < a && c < b) {
			modmin = abs(c);
			sum2 = b + c;
		}
		else {
			result = 0;
		}
		if (sum2 < 256 && log2(modmin) - (int)log2(modmin) == 0 && modmin < 256) {		//?log2(modmin)=int?
			result = 1;
		}
	    else if (fabs(sum2 - modmin) < 16 || fabs(sum2) < 16) {
		result = 1;
	}
		else {
		result = 0;
		}
	}
	else if (a < 0 || b < 0 || c < 0) {		//не всі числа додатні (0 вважати додатнім)
		if (a < 0 && b >= 0 && c >= 0) {		//тільки одне з них від’ємне
			if (a > -256) {
				result = 1;
			}
			else {
				result = 0;
			}
		}
		else if (a >= 0 && b < 0 && c >= 0) {
			if (b > -256) {
				result = 1;
			}
			else {
				result = 0;
			}
		}
		else if (a >= 0 && b >= 0 && c < 0) {
			if (c > -256) {
				result = 1;
			}
			else {
				result = 0;
			}
		}
		else if (a < 0 && b < 0 && c >= 0) {		//два від’ємних числа
			if (6 * (a + b) > -256) {
				result = 1;
			}
			else {
				result = 0;
			}
		}
		else if (a < 0 && b >= 0 && c < 0) {
			if (6 * (a + c) > -256) {
				result = 1;
			}
			else {
				result = 0;
			}
		}
		else if (a >= 0 && b < 0 && c < 0) {
			if (6 * (b + c) > -256) {
				result = 1;
			}
			else {
				result = 0;
			}
		}
	}
	else if (a >= 0 && b >= 0 && c >= 0) {		//всі числа додатні
		if (a > b && a > c) {
			max = a;
		}
		else if (b > a && b > c) {
			max = b;
		}
		else if (c > a && c > b) {
			max = c;
		}
		else {
			result = 0;
		}
		if (a < b && a < c) {
			min = a;
		}
		else if (b < a && b < c) {
			min = b;
		}
		else if (c < a && c < b) {
			min = c;
		}
		else {
			result = 0;
		}
		if (max - min > 32) {
			result = 1;
		}
		else {
			result = 0;
		}
	}
	return result;
}