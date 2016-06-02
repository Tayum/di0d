#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "database.h"
#include "investorStruct.h"
#include "invArrStruct.h"

struct database_s {
	sqlite3 * database;
};

database_t * database_new(const char * databaseFilename) {
	database_t * databaseSmp = malloc(sizeof(struct database_s));
	int rc = sqlite3_open(databaseFilename, &databaseSmp->database); // rc stands for 'errorCode'
	if (rc == SQLITE_ERROR) {
		printf("No such database exists.\n");
		exit(1); //	Exit instead of return to instantly abort the running program
	}
	return databaseSmp;
}

void database_free(database_t * self) {
	sqlite3_close(self->database);
	free(self);
}

// Amount of investors in database.
// The function is not used in other files, so it's static.
static int database_getSize(const database_t * self) {
	sqlite3_stmt * stmt = NULL; // stmt stands for 'Prepared statement'
	char * sqlRequest = "SELECT COUNT(*) FROM Investor,InvestorIden WHERE Investor.ID = InvestorIden.IDinv;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get size of Investor table.\n");
		exit(1); //	Exit instead of return to instantly abort the running program
	}
	int size = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	return size;
}

// Fills single investor with the info from stmt.
// The function is not used in other files, so it's static.
static void investor_fillByStmt(sqlite3_stmt * stmt, investor_t * self) {
	// Main table
	int id = sqlite3_column_int(stmt, 0);
	double rate = sqlite3_column_double(stmt, 1);
	char * date = sqlite3_column_text(stmt, 2);
	int exp = sqlite3_column_int(stmt, 3);
	int moneyInv = sqlite3_column_int(stmt, 4);
	char * curInv = sqlite3_column_text(stmt, 5);
	// Sub-table
	char * nm = sqlite3_column_text(stmt, 6);
	char * nknm = sqlite3_column_text(stmt, 7);
	char * srnm = sqlite3_column_text(stmt, 8);

	self->id = id;
	self->rating = (float)rate;
	// Date struct
	self->firstInv.tm_year = atoi(date);
	date = strtok(date, "-");
	date = strtok(NULL, "-");
	self->firstInv.tm_mday = atoi(date);
	date = strtok(NULL, "-");
	self->firstInv.tm_mon = atoi(date);
	//
	self->exp = exp;
	self->moneyInv = moneyInv;
	strcpy(self->curInv, curInv);
	strcpy(self->name, nm);
	strcpy(self->nickname, nknm);
	strcpy(self->surname, srnm);
}

// Function that check whether there is an investor with such ($ID) in the database.
// @Returns: INDEX_COR from ERR_HNDL enum if the index presents, INDEX_INCOR otherwise.
ERR_HNDL database_isThereID(const database_t * self, int ID) {
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "SELECT COUNT(*) FROM Investor,InvestorIden WHERE Investor.ID = ? AND Investor.ID = InvestorIden.IDinv;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	sqlite3_bind_int(stmt, 1, ID);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get info from Investor table.\n");
		exit(1); //	Exit instead of return to instantly abort the running program
	}
	int size = sqlite3_column_int(stmt, 0);

	sqlite3_finalize(stmt);
	// Investor presents in database
	if (size == 1) {
		return INDEX_COR;
	}
	// Investor does not present in database
	else if (size == 0) {
		return INDEX_INCOR;
	}
}

// Forms a single string from investor 'struct tm date'
// The function is not used in other files, so it's static.
static char * investor_createStringFromDate(char * resultStr, investor_t * self) {
	sprintf(resultStr, "%d-%d-%d\n", self->firstInv.tm_year, self->firstInv.tm_mday, self->firstInv.tm_mon);
	return resultStr;
}

// Creates a new investor in database with the info provided by invPtr.
void database_createInv(database_t * self, investor_t * invPtr) {
	// Main table
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "INSERT INTO Investor ('rating', 'firstInv', 'exp', 'moneyInv', 'curInv') VALUES (?, ?, ?, ?, ?);";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	// |SQLITE_STATIC| in (sqlite3_bind_text) means that the given string does not need to be free()'d
	// |-1| in (sqlite3_bind_text) means auto-estimation of the length of the given string
	sqlite3_bind_double(stmt, 1, (double)invPtr->rating);
	// Date struct
	char date[20];
	char * res = investor_createStringFromDate(date, invPtr);
	sqlite3_bind_text(stmt, 2, res, -1, SQLITE_STATIC);
	//
	sqlite3_bind_int(stmt, 3, invPtr->exp);
	sqlite3_bind_int(stmt, 4, invPtr->moneyInv);
	sqlite3_bind_text(stmt, 5, invPtr->curInv, -1, SQLITE_STATIC);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot create new investor.\n");
	}
	else {
		// Sub-table
		sqlite3_stmt * stmtIden = NULL;
		sqlRequest = "INSERT INTO InvestorIden ('name', 'nickname', 'surname') VALUES (?, ?, ?);";
		sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmtIden, NULL);

		sqlite3_bind_text(stmtIden, 1, invPtr->name, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmtIden, 2, invPtr->nickname, -1, SQLITE_STATIC);
		sqlite3_bind_text(stmtIden, 3, invPtr->surname, -1, SQLITE_STATIC);

		int rc = sqlite3_step(stmtIden);
		if (rc == SQLITE_ERROR) {
			printf("Cannot create new investor sub-info.\n");
		}
		else {
			sqlite3_finalize(stmt);
			sqlite3_finalize(stmtIden);
		}
	}
}

// Returns a single investor from the database by certain index or NULL if such index does not exist.
// Free an investor with (investor_free() ) after you're finished with him!
investor_t * database_getInvFromDB(const database_t * self, int index) {
	sqlite3_stmt * stmt = NULL;
	investor_t * invSmp = investor_new();
	
	char * sqlRequest = "SELECT * FROM Investor,InvestorIden WHERE ID = ? AND Investor.ID = InvestorIden.IDinv;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, index);

	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot get Investor with this ID.\n");
		return NULL;
	}

	investor_fillByStmt(stmt, invSmp);
	sqlite3_finalize(stmt);
	return invSmp;
}

// Returns (new) invArr of investors from database.
// Free returned invArr with invArr_free() after you're finished with it!
invArr_t * database_getInvListFromDB(const database_t * self) {
	sqlite3_stmt * stmt = NULL;
	int size = database_getSize(self);

	char * sqlRequest = "SELECT * FROM Investor,InvestorIden WHERE Investor.ID = InvestorIden.IDinv;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	invArr_t * invArrToReturn = invArr_new();
	for (int i = 0; i < size; i++) { // Check on 'sqlite_done' is not needed as far as for() cycle works EXACTLY as much times, as needed
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR) {
			printf("Cannot get Investor table.\n");
			exit(1); // Exit instead of return to instantly abort the running program
		}
		else {
			list_push_back(invArrToReturn->investors, investor_new());
			investor_fillByStmt(stmt, (investor_t *)list_get(invArrToReturn->investors, i));
		}
	}
	sqlite3_finalize(stmt);
	return invArrToReturn;
}

// Returns (new) invArr of investors in database according to the given conditions.
// Free returned invArr with invArr_free() you're finished with it!
invArr_t * database_getInvArrFromDB_WHERE(const database_t * self, int moneyInv, condition moneyInvSign, int exp, condition expSign) {
	// Condition, given by user
	char mnySign;
	char xpSign;
	if (moneyInvSign == GREATER) {
		mnySign = '>';
	}
	else if (moneyInvSign == LESS) {
		mnySign = '<';
	}
	if (expSign == GREATER) {
		xpSign = '>';
	}
	else if (expSign == LESS) {
		xpSign = '<';
	}
	//

	// The amount of investors that fit the condition
	sqlite3_stmt * stmt = NULL;
	char * sqlRequestSize = calloc(500, sizeof(char));
	sprintf(sqlRequestSize,
		"SELECT COUNT(*) FROM Investor,InvestorIden "
		"WHERE (moneyInv %c ? OR exp %c ?) "
		"AND Investor.ID = InvestorIden.IDinv;",
		mnySign, xpSign);

	sqlite3_prepare_v2(self->database, sqlRequestSize, strlen(sqlRequestSize) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, moneyInv);
	sqlite3_bind_int(stmt, 2, exp);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		free(sqlRequestSize);
		printf("Cannot get size of Investor table.\n");
		exit(1); //	Exit instead of return to instantly abort the running program
	}
	int sizeFilter = sqlite3_column_int(stmt, 0);
	//

	sqlite3_reset(stmt);

	// Working with every single investor and his info
	char * sqlRequestInvestors = calloc(500, sizeof(char));
	sprintf(sqlRequestInvestors,
		"SELECT * FROM Investor,InvestorIden "
		"WHERE (moneyInv %c ? OR exp %c ?) "
		"AND Investor.ID = InvestorIden.IDinv;",
		mnySign, xpSign);

	sqlite3_prepare_v2(self->database, sqlRequestInvestors, strlen(sqlRequestInvestors) + 1, &stmt, NULL);
	sqlite3_bind_int(stmt, 1, moneyInv);
	sqlite3_bind_int(stmt, 2, exp);
	invArr_t * invToReturn = invArr_new();
	for (int i = 0; i < sizeFilter;i++) { // Check on 'sqlite_done' is not needed as far as for() cycle works EXACTLY as much times, as needed
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ERROR) {
			free(sqlRequestSize);
			free(sqlRequestInvestors);
			printf("Cannot get Investor table.\n");
			exit(1); // Exit instead of return to instantly abort the running program
		}
		else {
			list_push_back(invToReturn->investors, investor_new());
			investor_fillByStmt(stmt, (investor_t *)list_get(invToReturn->investors, i));
		}
	}
	free(sqlRequestSize);
	free(sqlRequestInvestors);
	sqlite3_finalize(stmt);
	//

	return invToReturn;
}

// Function that deletes the investor by certain ID. IDs are not shifted (read description below).
// Description:
// For example, if you have 3 investors with 1,2,3 indeces and then delete the 2nd one, the 1st and 3rd will remain.
// Then, when you add new another investor, it will be added with 4th index.
void database_deleteInv(database_t * self, int index) {
	// Main table
	sqlite3_stmt * stmt = NULL;
	char * sqlRequest = "DELETE FROM Investor WHERE ID = ?;";
	sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmt, NULL);

	// Taking the ID to check which investor to delete ('WHERE ID = ?')
	sqlite3_bind_int(stmt, 1, index);
	int rc = sqlite3_step(stmt);
	if (rc == SQLITE_ERROR) {
		printf("Cannot delete this investor.\n");
	}
	else {
		// Sub-table
		sqlite3_stmt * stmtIden = NULL;
		sqlRequest = "DELETE FROM InvestorIden WHERE IDinv = ?;";
		sqlite3_prepare_v2(self->database, sqlRequest, strlen(sqlRequest) + 1, &stmtIden, NULL);

		// Taking the ID to check which investor to delete ('WHERE ID = ?')
		sqlite3_bind_int(stmtIden, 1, index);
		int rc = sqlite3_step(stmtIden);
		if (rc == SQLITE_ERROR) {
			printf("Cannot delete this investor sub-info.\n");
		}
		else {
			sqlite3_finalize(stmt);
			sqlite3_finalize(stmtIden);
		}
	}
}