#ifndef INVESTOR_H_INCLUDED
#define INVESTOR_H_INCLUDED

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

typedef struct investor_s investor_t;

investor_t investor_new(void);
char * investor_parseAllToJSON(const investor_t * invArr, int size);
char * investor_parseToJSON(const investor_t * self);

#endif //INVESTOR_H_INCLUDED
