#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "investorStruct.h"
#include "investor.h"

//ALLOCATING MEMORY EQUAL TO THE SIZE OF ONE STRUCT (INVESTOR)
investor_t * investor_new(void) {
	investor_t * invSmp = malloc(sizeof(struct investor_s));
	return invSmp;
}

void investor_free(investor_t * self) {
	free(self);
}

//investor_fillSmp - AFTER CREATING INVESTOR WITH investor_new, PASS POINTER OF HIM TO THIS FUNC AND FILL HIM WITH DATA
void investor_fillSmp(investor_t * self, char * name, char * surname, float rating, int moneyInv, int projInv, int year, int day, int mon) {
	strcpy(self->name, name);
	strcpy(self->surname, surname);
	self->rating = rating;
	self->moneyInvested = moneyInv;
	self->projectsInvested = projInv;
	self->firstInvestment.tm_year = year;
	self->firstInvestment.tm_mday = day;
	self->firstInvestment.tm_mon = mon;
}

investorList_t * investorList_new(void) {
	investorList_t * invListSmp = malloc(sizeof(struct investorList_s));
	invListSmp->invList = list_new();
	return invListSmp;
}

void investorList_free(investorList_t * self) {
	int size = list_getSize(self->invList);
	for (int i = 0; i < size; i++) {
		investor_free((investor_t *)list_pop_back(self->invList));
	}
	list_free(self->invList);
	free(self);
}