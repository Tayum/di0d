/* Investor struct with opened body.
This file is needed for proper incapsulation of data. */

#ifndef INVESTORSTRUCT_H_INCLUDED
#define INVESTORSTRUCT_H_INCLUDED

#include <time.h> //struct tm

struct investor_s {
	int id;
	char name[30];
	char nickname[30];
	char surname[30];
	float rating;
	// 'firstInv' Date struct
	struct tm firstInv;
	int exp;
	int moneyInv;
	char curInv[30];
};

#endif // INVESTORSTRUCT_H_INCLUDED