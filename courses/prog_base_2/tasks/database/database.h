#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "SQLite/sqlite3.h"

#include "investor.h"

typedef struct database_s database_t;

database_t * database_new(const char * databaseFilename);
void database_free(database_t * self);

int database_getSize(const database_t * self);

void database_createInv(database_t * self, investor_t * invPtr);
investor_t * database_readInv(const database_t * self, int index);
void database_readInvList(const database_t * self, investorList_t * invPtr);
int database_readInvListWHERE(const database_t * self, int moneyInv, int projInv, investorList_t * invPtr);
void database_updateInv(database_t * self, investor_t * invPtr, int index);
void database_deleteInv(database_t * self, int index);

#endif //DATABASE_H_INCLUDED