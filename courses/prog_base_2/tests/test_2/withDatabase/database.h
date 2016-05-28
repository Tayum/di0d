#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "SQLite/sqlite3.h"

#include "investor.h"

typedef struct database_s database_t;

database_t * database_new(const char * databaseFilename);
void database_free(database_t * self);

int database_getSize(const database_t * self);
void database_readInvList(const database_t * self, investorList_t * invPtr);

#endif // DATABASE_H_INCLUDED
