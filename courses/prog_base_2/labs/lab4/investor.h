/* investor.c/investor.h represent single investor structure (as object)
and the array of such objects - invArr structure
(contains list of investors inside, represented with list.c/list.h).
These are the data we use to work with during the program.

Files also represent two functions that returns the line (of single investor OR their array (list):
in cJSON form (for API requests) or in HTML form (for HTML requests)

For more information check out investor.c file. */

#ifndef INVESTOR_H_INCLUDED
#define INVESTOR_H_INCLUDED

#include "list/list.h"

typedef struct investor_s investor_t;
typedef struct invArr_s invArr_t;

typedef enum {
	INDEX_COR = 1,
	INDEX_INCOR
} ERR_HNDL;

investor_t * investor_new(void);
void investor_free(investor_t * self);
void investor_fill(investor_t * self, int id, char * name, char * nickname, char * surname, float rating, int year, int day, int month, int exp, int moneyInv, char * curInv);

invArr_t * invArr_new(void);
void invArr_free(invArr_t * self);

int invArr_seekForFreeID(const invArr_t * self);
void invArr_addInv(invArr_t * self, const investor_t * inv);
void invArr_addInvByIndex(invArr_t * self, const investor_t * inv, int index);

ERR_HNDL invArr_isThereID(const invArr_t * self, int ID);
investor_t * invArr_removeInvByID(invArr_t * self, int ID);
investor_t * invArr_getInvByID(const invArr_t * self, int ID);

int invArr_getSize(invArr_t * self);

// cJSON form
// Free a line after usage with built-in free() function!
char * investor_parseAllToJSON(const invArr_t * self);
// Free a line after usage with built-in free() function!
char * investor_parseToJSON(const investor_t * self);

// HTML form
// Free a line after usage with built-in free() function!
char * investor_parseAllToHTML(const invArr_t * self);
// Free a line after usage with built-in free() function!
char * investor_parseToHTML(const investor_t * self);

#endif //INVESTOR_H_INCLUDED