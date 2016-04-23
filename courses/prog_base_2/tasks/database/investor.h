#ifndef INVESTOR_H_INCLUDED
#define INVESTOR_H_INCLUDED

#include <time.h>

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

typedef struct investor_s investor_t;

//LIST OF INVESTORS (POINTER TO POINTERS OF INVESTOR STRUCTS)
struct investorList_s {
	investor_t ** list;
	int size;
};

typedef struct investorList_s investorList_t;

investor_t * investor_new();
investorList_t * investorList_new(int size);
void investor_free(investor_t * self);
void investorList_free(investorList_t * self);
void investor_fillSmp(investor_t * self, char * name, char * surname, float rating, int moneyInv, int projInv, int year, int day, int mon);
void investor_print(investor_t * self);
void investorList_print(investorList_t * self);

#endif //INVESTOR_H_INCLUDED