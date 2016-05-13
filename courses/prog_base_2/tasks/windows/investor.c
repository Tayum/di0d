#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "investor.h"

struct investor_s {
	char name[20];
	char surname[25];
	int exp;
	int moneyInv;
	char curInvest[30];
};

// investor_new: allocating memory for investor
investor_t * investor_new(void) {
	investor_t * invSmp = malloc(sizeof(struct investor_s));
	strcpy(invSmp->name, "NoName");
	strcpy(invSmp->name, "NoSurame");
	invSmp->exp = 0;
	invSmp->moneyInv = 0;
	strcpy(invSmp->name, "NoCurInv");
	return invSmp;
}

void investor_free(investor_t * self) {
	free(self);
}

// investor_fill: setting the fields of investor with those passed as parameters
void investor_fill(investor_t * self, char * name, char * surname, int exp, int moneyInv, char * curInvest) {
	strcpy(self->name, name);
	strcpy(self->surname, surname);
	self->exp = exp;
	self->moneyInv = moneyInv;
	strcpy(self->curInvest, curInvest);
}

char * investor_getName(investor_t * self) {
	return self->name;
}

char * investor_getSurname(investor_t * self) {
	return self->surname;
}

int investor_getExp(investor_t * self) {
	return self->exp;
}

int investor_getMoney(investor_t * self) {
	return self->moneyInv;
}

char * investor_getCurInv(investor_t * self) {
	return self->curInvest;
}