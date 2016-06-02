/* database.h/.c represent the functions that is needed to work with database:
read, create or delete the investors from the database.
Some of functions form a struct (or array (list) of the structs) from the investors
from database in order to transform this struct to cJSON or HTML form and pass
the retrieved info to client.
There is no permanent list of investors like it was in Lab4, only
the temporary ones that are used for 'transporting' the data between database and client.
After they are used, they are immideatily free()'d with their 'free()' functions.

For more information check out database.c file. */

#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "SQLite/sqlite3.h"

#include "investor.h"

typedef enum {
	INDEX_COR = 1,
	INDEX_INCOR
} ERR_HNDL;

typedef enum {
	LESS,
	GREATER
} condition;

typedef struct database_s database_t;

database_t * database_new(const char * databaseFilename);
void database_free(database_t * self);

ERR_HNDL database_isThereID(const database_t * self, int ID);
void database_createInv(database_t * self, investor_t * invPtr);
// Free an investor with (investor_free() ) after you're finished with him!
investor_t * database_getInvFromDB(const database_t * self, int index);
// Free returned invArr with invArr_free() after you're finished with it!
invArr_t * database_getInvListFromDB(const database_t * self);
// Free returned invArr with invArr_free() after you're finished with it!
invArr_t * database_getInvArrFromDB_WHERE(const database_t * self, int moneyInv, condition moneyInvSign, int exp, condition expSign);
void database_deleteInv(database_t * self, int index);

#endif //DATABASE_H_INCLUDED