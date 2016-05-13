/* investor.h / investor.c: represents "investor" type, which info will be shown in program */

#ifndef INVESTOR_H_INCLUDED
#define INVESTOR_H_INCLUDED

typedef struct investor_s investor_t;

investor_t * investor_new(void);
void investor_free(investor_t * self);

void investor_fill(investor_t * self, char * name, char * surname, int exp, int moneyInv, char * curInvest);
char * investor_getName(investor_t * self);
char * investor_getSurname(investor_t * self);
int investor_getExp(investor_t * self);
int investor_getMoney(investor_t * self);
char * investor_getCurInv(investor_t * self);

#endif // INVESTOR_H_INCLUDED