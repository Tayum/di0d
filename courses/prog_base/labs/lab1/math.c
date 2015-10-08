#include <math.h>

double calc(double x, double y, double z) {
	double a;
	if (x == y || x<=y || z == 0 || sin(x) == 0) {
		return NAN;
	}
	else {
		a = pow(x, y + 1) / (pow(x - y, 1 / z)) + y / (6 * fabs(x + y)) + sqrt(fabs(cos(y) / sin(x) + 1));
	}
	return a;
}