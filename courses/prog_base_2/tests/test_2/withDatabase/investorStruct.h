#ifndef INVESTORSTRUCT_H_INCLUDED
#define INVESTORSTRUCT_H_INCLUDED

#include <time.h>
#include "list/list.h"

//SINGLE INVESTOR STRUCT
struct investor_s {
	int id;
	char name[25];
	char surname[25];
	float rating;
	int moneyInvested;
	int projectsInvested;
	struct tm firstInvestment;
};

struct investorList_s {
	list_t * invList;
};

#endif // INVESTORSTRUCT_H_INCLUDED
