#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "database.h"

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
void investor_fill(sqlite3_stmt * stmt, investor_t * self) {
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

//not included in main:
//FORMS A STRING FROM INVESTOR struct tm date IN ORDER TO PASS IT TO stmt AND TO DATABASE IN FUTURE
char * investor_createStringFromDate(char * resultStr, investor_t * self) {
	sprintf(resultStr, "%d-%d-%d\n", self->firstInvestment.tm_year, self->firstInvestment.tm_mday, self->firstInvestment.tm_mon);
	return resultStr;
}

//CREATES A NEW STUDENT IN DATABASE USING DATA FROM invPtr INVESTOR
void database_createInv(database_t * self, investor_t * invPtr) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "INSERT INTO Investor ('name', 'surname', 'rating', 'moneyInvested', 'projectsInvested', 'firstInvestment') VALUES (?, ?, ?, ?, ?, ?);";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	//SQLITE_STATIC MEANS THAT INFO (invPtr->name) DOES NOT NEED TO BE FREED
	//-1 IN sqlite3_bind_text MEANS AUTO-ESTIMATION OF STRING LENGTH
	sqlite3_bind_text(stmt, 1, invPtr->name, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, invPtr->surname, -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 3, (double)invPtr->rating);
	sqlite3_bind_int(stmt, 4, invPtr->moneyInvested);
	sqlite3_bind_int(stmt, 5, invPtr->projectsInvested);
	//date
	char date[20];
	char * res = investor_createStringFromDate(date, invPtr);
	sqlite3_bind_text(stmt, 6, res, -1, SQLITE_STATIC);
	//

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot create new investor.\n");
	}
	else {
		//also provides investor with the proper ID from database
		invPtr->id = sqlite3_last_insert_rowid(self->database);
		sqlite3_finalize(stmt);
	}
}

//RETURNS A SINGLE INVESTOR FROM THE DATABASE BY CERTAIN INDEX OR NULL IF NO SUCH INDEX EXISTS
investor_t * database_readInv(const database_t * self, int index) {
	sqlite3_stmt * stmt = NULL;
	//CREATINF A SAMPLE OF INVESTOR TO BE PASSED IN RETURN IN FUTURE
	investor_t * invSmp = investor_new();

	char * sqlRequest = "SELECT * FROM Investor WHERE ID = ?;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, index);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get Student with this ID.\n");
		return NULL; //return NULL (INDEX IS INVALID) ====> MUST BE CHECKED ON NULL IN MAIN!
	}
	//FILLS OUR SAMPLE WITH DATA
	investor_fill(stmt, invSmp);
	sqlite3_finalize(stmt);
	return invSmp;
}

//FORMS A STRUCT BY invPtr POINTER, USING DATA FROM DATABASE!
//THIS FUNCTION SHOULD BE USED EVERY TIME AFTER YOU CHANGE SOMETHING IN DATABASE TO KEEP STRUCT IN THE PROGRAM REFRESHED!
void database_readInvList(const database_t * self, investorList_t * invPtr) {
	sqlite3_stmt * stmt = NULL;
	int size = database_getSize(self);

	//ALLOCATES NEW AMOUNT OF MEMORY (POINTERS) FOR THE STRUCT
	invPtr->list = realloc(invPtr->list, size * sizeof(investor_t *));
	//ALLOCATES A SIZE OF STRUCT FOR EACH POINTER THAT WAS ALLOCATED ABOVE
	for (int i = 0; i < size; i++) {
		invPtr->list[i] = investor_new();
	}
	invPtr->size = size;
	//

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
			investor_fill(stmt, invPtr->list[i]);
		}
	}
	sqlite3_finalize(stmt);
}

//FORMS A STRUCT BY invPtr POINTER, USING DATA (WITH FILTERS) FROM DATABASE!
//THIS FUNCTION ALSO CHANGES THE STRUCT IN THE PROGRAM!
int database_readInvListWHERE(const database_t * self, int moneyInv, int projInv, investorList_t * invPtr) {
	sqlite3_stmt * stmt = NULL;
	//FIRST STEP: COUNTS THE AMOUNT OF INVESTORS THAT FITS THE CONDITIONS
	char * sqlRequest = "SELECT COUNT(*) FROM Investor WHERE moneyInvested < ? OR projectsInvested < ?;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, moneyInv);
	sqlite3_bind_int(stmt, 2, projInv);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get size of Investor table.\n");
		exit(1); //	exit instead of return to instantly abort the running program
	}
	int sizeFilter = sqlite3_column_int(stmt, 0);

	//SECOND STEP: RESETS stmt IN ORDER TO WORK WITH THE SAME stmt AGAIN (IN THIRD STEP),
	//(not sure about reset though, it works without it)
	sqlite3_reset(stmt);
	//ALLOCATES NEW AMOUNT OF MEMORY (POINTERS) FOR THE STRUCT
	invPtr->list = realloc(invPtr->list, sizeFilter * sizeof(investor_t *));
	for (int i = 0; i < sizeFilter; i++) {
		//ALLOCATES A SIZE OF STRUCT FOR EACH POINTER THAT WAS ALLOCATED ABOVE
		invPtr->list[i] = investor_new();
	}
	invPtr->size = sizeFilter;

	//THIRD STEP: SELECTS THE NEEDED STUDENTS FROM DATABASE AND ADDS THEM TO OUR STRUCT
	sqlRequest = "SELECT * FROM Investor WHERE moneyInvested < ? OR projectsInvested < ?;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, moneyInv);
	sqlite3_bind_int(stmt, 2, projInv);

	for (int i = 0; i < sizeFilter;i++) { //CHECK ON SQLITE_DONE IS NOT NEEDED AS FAR AS for() CYCLE WORKS EXACTLY AS MUCH AS NEEDED TIMES
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR) {
			printf("Cannot get Student table.\n");
			exit(1); //exit instead of return to instantly abort the running program
		}
		else {
			//FILLS EACH OF OUR POINTERS' STRUCTS' WITH DATA
			investor_fill(stmt, invPtr->list[i]);
		}
	}
	sqlite3_finalize(stmt);
	return sizeFilter;
}

//UPDATES INVESTOR IN DATABASE BY CERTAIN INDEX USING THE DATA FROM invPtr INVESTOR!
void database_updateInv(database_t * self, investor_t * invPtr, int index) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "UPDATE Investor SET name = ?, surname = ?, rating = ?, moneyInvested = ?, projectsInvested = ?, firstInvestment = ? WHERE ID = ?;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, invPtr->name, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, invPtr->surname, -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 3, (double)invPtr->rating);
	sqlite3_bind_int(stmt, 4, invPtr->moneyInvested);
	sqlite3_bind_int(stmt, 5, invPtr->projectsInvested);
	//date
	char date[20];
	char * res = investor_createStringFromDate(date, invPtr);
	sqlite3_bind_text(stmt, 6, res, -1, SQLITE_STATIC);
	//

	//ID TO CHECK WHICH STUDENT TO UPDATE ('WHERE ID = ?')
	sqlite3_bind_int(stmt, 7, index);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot update this investor.\n");
	}
	else {
		sqlite3_finalize(stmt);
	}
}

//FUNCTION THAT DELETES INVESTOR BY CERTAIN ID (IDs ARE NOT SHIFTED AFTER THE OPERATION IS DONE!)
void database_deleteInv(database_t * self, int index) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "DELETE FROM Investor WHERE ID = ?;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	//ID TO CHECK WHICH STUDENT TO DELETE ('WHERE ID = ?')
	sqlite3_bind_int(stmt, 1, index);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot delete this investor.\n");
	}
	else {
		sqlite3_finalize(stmt);
	}
}