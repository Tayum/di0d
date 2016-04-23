#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "investor.h"

//ALLOCATING MEMORY EQUAL TO THE SIZE OF ONE STRUCT (INVESTOR)
investor_t * investor_new() {
	investor_t * invSmp = malloc(sizeof(struct investor_s));
	return invSmp;
}

investorList_t * investorList_new(int size) {
	if (size <= 0) {
		printf("Such amount of memory cannot be allocated.\n");
		exit(1);  //exit instead of return to instantly abort the running program
	}
	//ALLOCATING MEMORY FOR POINTER TO POINTERS
	investorList_t * invSmp = malloc(sizeof(struct investorList_s));
	//ALLOCATING MEMORY FOR EACH POINTER THAT WILL POINT ON STRUCT
	invSmp->list = calloc(size, sizeof(struct investor_s *));
	for (int i = 0; i < size; i++) {
		//ALLOCATING MEMORY EQUAL TO THE SIZE OF ONE STRUCT (see above)
		invSmp->list[i] = investor_new();
	}
	invSmp->size = 0;
	return invSmp;
}

void investor_free(investor_t * self) {
	free(self);
}

void investorList_free(investorList_t * self) {
	//FREEING MEMORY EQUAL TO THE SIZE OF ONE STRUCT IN EACH POINTER (see above)
	for (int i = 0; i < self->size; i++) {
		free(self->list[i]);
	}
	//FREEING AN ARRAY OF POINTERS
	free(self->list);
	//FREEING POINTER TO POINTERS
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

void investor_print(investor_t * self) {
	printf("=====INVESTOR #%i=====\n\nName: %s\nSurname: %s\nRating: %f\nTotal Money Invested(in hryvnas): %i\nProjects invested: %i\nFirst investment made: %i-%i-%i\n\n",
		self->id,
		self->name,
		self->surname,
		self->rating,
		self->moneyInvested,
		self->projectsInvested,
		self->firstInvestment.tm_year,
		self->firstInvestment.tm_mday,
		self->firstInvestment.tm_mon);
}

void investorList_print(investorList_t * self) {
	for (int i = 0; i < self->size; i++) {
		investor_print(self->list[i]);
	}
}