#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "database.h"

int main(void) {
	//PRIMARY SIZE OF THE DATABASE
	const int size = 4;
	investorList_t * investorList = investorList_new(size);
	database_t * database = database_new("investors.db");
	//SIZE OF PRIMARY DATABASE
	int countSize = database_getSize(database);
	printf("TOTAL INVESTORS: %i\n\n", countSize);
	//FILTERS FOR THE NEXT STEP
	int moneyFilter = 4000000;
	int projFilter = 10;
	//AMOUNT OF INVESTORS FITTING FILTERS
	int countFilter = database_readInvListWHERE(database, moneyFilter, projFilter, investorList);
	printf("=====CONDITIONAL READ=====\nInvestors with money invested < %i OR projects invested < %i: %i\n\n", moneyFilter, projFilter, countFilter);
	investorList_print(investorList);

	puts("=====READ INVESTOR (BY INDEX 3)=====");
	investor_t * investor = database_readInv(database, 3);
	if (investor != NULL) { //CHECKING IF SUCH AN INDEX EXISTS
		investor_print(investor);
	}

	puts("=====CREATE NEW INVESTOR=====");
	investor_fillSmp(investor, "Sample", "Samploff", 5.7, 10000, 4, 2000, 3, 11);
	database_createInv(database, investor);
	database_readInvList(database, investorList);
	investorList_print(investorList);

	puts("=====UPDATE INVESTOR (BY INDEX 2)=====");
	database_updateInv(database, investor, 2);
	database_readInvList(database, investorList);
	investorList_print(investorList);
	
	puts("=====DELETE INVESTOR (BY INDEX 3)=====");
	database_deleteInv(database, 3);
	database_readInvList(database, investorList);
	investorList_print(investorList);

	//end of program
	investor_free(investor);
	investorList_free(investorList);
	database_free(database);
	getch();
	return 0;
}