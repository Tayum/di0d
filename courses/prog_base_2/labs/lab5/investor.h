/* investor.c/investor.h represent single investor structure (as object)
and the array of such objects - invArr structure
(contains list of investors inside, represented with list.c/list.h).
These are the way we transport the data from database to user.

Files also represent two functions that returns the line (of single investor OR their array (list) ):
in cJSON form (for API requests) or in HTML form (for HTML requests)

For more information check out investor.c file. */

#ifndef INVESTOR_H_INCLUDED
#define INVESTOR_H_INCLUDED

#include "list/list.h"

typedef struct investor_s investor_t;
typedef struct invArr_s invArr_t;

investor_t * investor_new(void);
void investor_free(investor_t * self);

invArr_t * invArr_new(void);
void invArr_free(invArr_t * self);

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