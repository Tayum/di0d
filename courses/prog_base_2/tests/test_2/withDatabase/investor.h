#ifndef INVESTOR_H_INCLUDED
#define INVESTOR_H_INCLUDED

typedef struct investor_s investor_t;
typedef struct investorList_s investorList_t;

investor_t * investor_new(void);
void investor_free(investor_t * self);
void investor_fillSmp(investor_t * self, char * name, char * surname, float rating, int moneyInv, int projInv, int year, int day, int mon);

investorList_t * investorList_new(void);
void investorList_free(investorList_t * self);

#endif // INVESTOR_H_INCLUDED
