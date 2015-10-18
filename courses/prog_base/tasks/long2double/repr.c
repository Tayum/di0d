#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double long2double(long long LongNumber) {
	int NumberInBinary[64];
	int i = 0;
	int ExponentArray[11];
	int FractionArray[52];
	int Sign = 0;
	double Exponent = 0;
	double Fraction = 0;
	for (i = 63; i >= 0; i--) {					//LongNumber in binary code
		NumberInBinary[i] = (LongNumber & (1LL << 63 - i)) ? 1 : 0;
	}
	for (i = 0; i < 11; i++) {			//array for exponent
		ExponentArray[i] = NumberInBinary[i + 1];
	}
	for (i = 0; i < 52; i++) {			//array for fraction
		FractionArray[i] = NumberInBinary[i + 12];
	}
	Sign = NumberInBinary[0];			//sign
	for (i = 10; i >= 0; i--) {			//exponent
		Exponent = Exponent + ExponentArray[i] * pow(2, 10 - i);
	}
	for (i = 0; i < 52; i++) {			//fraction
		Fraction = Fraction + FractionArray[i] * pow(2, -i - 1);
	}									//special cases						
	if (Exponent == 2047 && Fraction != 0) {
		return NAN;
	}
	if (Exponent == 2047 && Fraction == 0 && Sign == 1) {
		return -INFINITY;
	}
	if (Exponent == 2047 && Fraction == 0 && Sign == 0) {
		return INFINITY;
	}
	if (Exponent == 0 && Fraction == 0 && Sign == 1) {
		return -0;
	}
	if (Exponent == 0 && Fraction == 0 && Sign == 0) {
		return 0;
	}
	if (Exponent == 0 && Fraction != 0) {
		return pow(-1, Sign) * pow(2, -1022) * Fraction;
	}
	if (Exponent > 0 && Exponent < 2047) {
		return pow(-1, Sign) * pow(2, Exponent - 1023) * (1 + Fraction);
	}
}

