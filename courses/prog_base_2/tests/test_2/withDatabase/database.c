#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "database.h"
#include "investorStruct.h"

struct database_s {
	sqlite3 * database;
};

database_t * database_new(const char * databaseFilename) {
	database_t * databaseSmp = malloc(sizeof(struct database_s));
	int rc = sqlite3_open(databaseFilename, &databaseSmp->database); //rc = errorCode
	if (rc == SQLITE_ERROR) {
		printf("No such database exists.\n");
		exit(1); //	exit instead of return to instantly abort the running program
	}
	return databaseSmp;
}

void database_free(database_t * self) {
	sqlite3_close(self->database);
	free(self);
}

//COUNTS SIZE OF DATABASE AND RETURNS THIS VALUE
int database_getSize(const database_t * self) {
	sqlite3_stmt * stmt = NULL; // stmt == prepared statement
	char * sqlRequest = "SELECT COUNT(*) FROM Investor;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get size of Investor table.\n");
		exit(1); //	exit instead of return to instantly abort the running program
	}
	int size = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return size;
}

//not included in main:
//FILLS SINGLE INVESTOR WITH THE INFO PROVIDED BY STATEMENT stmt
static void investor_fill(sqlite3_stmt * stmt, investor_t * self) {
	int id = sqlite3_column_int(stmt, 0);
	char * nm = sqlite3_column_text(stmt, 1);
	char * srnm = sqlite3_column_text(stmt, 2);
	double rate = sqlite3_column_double(stmt, 3);
	int moneyInv = sqlite3_column_int(stmt, 4);
	int projInv = sqlite3_column_int(stmt, 5);
	char * date = sqlite3_column_text(stmt, 6);
	self->id = id;
	strcpy(self->name, nm);
	strcpy(self->surname, srnm);
	self->rating = (float)rate;
	self->moneyInvested = moneyInv;
	self->projectsInvested = projInv;
	//date
	self->firstInvestment.tm_year = atoi(date);
	date = strtok(date, "-");
	date = strtok(NULL, "-");
	self->firstInvestment.tm_mday = atoi(date);
	date = strtok(NULL, "-");
	self->firstInvestment.tm_mon = atoi(date);
	//
}

//FORMS A STRUCT BY invPtr POINTER, USING DATA FROM DATABASE!
//THIS FUNCTION SHOULD BE USED EVERY TIME AFTER YOU CHANGE SOMETHING IN DATABASE TO KEEP STRUCT IN THE PROGRAM REFRESHED!
void database_readInvList(const database_t * self, investorList_t * invPtr) {
	sqlite3_stmt * stmt = NULL;
	int size = database_getSize(self);

	char * sqlRequest = "SELECT * FROM Investor;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	for (int i = 0; i < size; i++) {
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR) {
			printf("Cannot get Student table.\n");
			exit(1); //exit instead of return to instantly abort the running program
		}
		else {
			//FILLS EACH OF OUR POINTERS' STRUCTS' WITH DATA
			investor_t * invSmp = investor_new();
			list_push_back(invPtr->invList, invSmp);
			investor_fill(stmt, (investor_t *)list_get(invPtr->invList, i));
		}
	}
	sqlite3_finalize(stmt);
}