/* Investor struct with opened body.
This file is needed for proper incapsulation of data. */

#ifndef INVESTORSTRUCT_H_INCLUDED
#define INVESTORSTRUCT_H_INCLUDED

#include <time.h> //struct tm

struct investor_s {
	int id;
	char * name;
	char * nickname;
	char * surname;
	float rating;
	//firstInv date struct
	struct tm firstInv;
	int exp;
	int moneyInv;
	char * curInv;
};

#endif // INVESTORSTRUCT_H_INCLUDED