#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cJSON/cJSON.h"
#include "investorStruct.h"
#include "investor.h"

// ====================Single investor constructor (default values, ID == -1 )====================
investor_t * investor_new(void) {
	investor_t * invSmp = malloc(sizeof(struct investor_s));
	invSmp->id = -1;
	invSmp->name = "NoName";
	invSmp->nickname = "NoNickname";
	invSmp->surname = "NoSurname";
	invSmp->rating = 0.0;
	//date
	memset(&(invSmp->firstInv), 0, sizeof(invSmp->firstInv));
	invSmp->firstInv.tm_year = 1900;
	invSmp->firstInv.tm_mday = 1;
	invSmp->firstInv.tm_mon = 1;
	//
	invSmp->exp = 0;
	invSmp->moneyInv = 0;
	invSmp->curInv = "NoCurInv";
	return invSmp;
}

void investor_free(investor_t * self) {
	free(self);
}

void investor_fill(investor_t * self, int id, char * name, char * nickname, char * surname, float rating, int year, int day, int month, int exp, int moneyInv, char * curInv) {
	self->id = id;
	self->name = name;
	self->nickname = nickname;
	self->surname = surname;
	self->rating = rating;
	//date
	self->firstInv.tm_year = year;
	self->firstInv.tm_mday = day;
	self->firstInv.tm_mon = month;
	//
	self->exp = exp;
	self->moneyInv = moneyInv;
	self->curInv = curInv;
}

// ====================Array (list) with investors====================
struct invArr_s {
	list_t * investors;
};

invArr_t * invArr_new(void) {
	invArr_t * invArrSmp = malloc(sizeof(struct invArr_s));
	invArrSmp->investors = list_new();
	return invArrSmp;
}

void invArr_free(invArr_t * self) {
	list_free(self->investors);
	free(self);
}

// ==========Functions connected with adding the new investor to the list of investors==========
// Function that returns the first free ID
int invArr_seekForFreeID(const invArr_t * self) {
	if (list_getSize(self->investors) == 0) {
		return 0;
	}
	for (int i = 0; i <= list_getSize(self->investors); i++) {
		if (i == list_getSize(self->investors)) {
			return i;
		}
		else {
			investor_t * inv = (investor_t *)list_get(self->investors, i);
			if (inv->id != i) {
				return i;
			}
		}
	}
}

// Function that adds new investor to the end of the list
void invArr_addInv(invArr_t * self, const investor_t * inv) {
	list_push_back(self->investors, inv);
}

// Function that adds new investor to the some position ($index) to the list
void invArr_addInvByIndex(invArr_t * self, const investor_t * inv, int index) {
	list_insert(self->investors, index, inv);
}

// ==========Functions connected with deleting the existing investor from the list of investors==========
// Function that check whether there is an investor with such ($ID) in the list
// @Returns: INDEX_COR from ERR_HNDL enum if the index presents, INDEX_INCOR otherwise.
ERR_HNDL invArr_isThereID(const invArr_t * self, int ID) {
	for (int i = 0; i < list_getSize(self->investors); i++) {
		investor_t * inv = (investor_t *)list_get(self->investors, i);
		if (inv->id == ID) {
			return INDEX_COR;
		}
	}
	return INDEX_INCOR;
}

// Function that removes the investor by given ($ID)
investor_t * invArr_removeInvByID(invArr_t * self, int ID) {
	investor_t * inv = (investor_t *)list_remove(self->investors, ID);
	return inv;
}

// Function that gets the investor by given ($ID)
investor_t * invArr_getInvByID(const invArr_t * self, int ID) {
	for (int i = 0; i < list_getSize(self->investors); i++) {
		investor_t * inv = (investor_t *)list_get(self->investors, i);
		if (inv->id == ID) {
			return inv;
		}
	}
	return NULL;
}

// ==========Other functions==========
int invArr_getSize(invArr_t * self) {
	return list_getSize(self->investors);
}


// ====================Working with API (cJSON) requests====================

// Constructing a CJSON form from the single investor-struct
// The function is static as far as it is not used in other files.
static cJSON * investor_serializeJSON(const investor_t * self) {
    cJSON * invSmpJSON = cJSON_CreateObject();
	cJSON_AddItemToObject(invSmpJSON, "id", cJSON_CreateNumber(self->id));
	cJSON_AddItemToObject(invSmpJSON, "name", cJSON_CreateString(self->name));
	cJSON_AddItemToObject(invSmpJSON, "nickname", cJSON_CreateString(self->nickname));
	cJSON_AddItemToObject(invSmpJSON, "surname", cJSON_CreateString(self->surname));
	cJSON_AddItemToObject(invSmpJSON, "rating", cJSON_CreateNumber(self->rating));
	//date
	char data[20];
	sprintf(data, "%d-%d-%d", self->firstInv.tm_year, self->firstInv.tm_mon, self->firstInv.tm_mday);
	cJSON_AddItemToObject(invSmpJSON, "firstInvestmentDate", cJSON_CreateString(data));
	//
	cJSON_AddItemToObject(invSmpJSON, "experienceYears", cJSON_CreateNumber(self->exp));
	cJSON_AddItemToObject(invSmpJSON, "totalMoneyInvested", cJSON_CreateNumber(self->moneyInv));
	cJSON_AddItemToObject(invSmpJSON, "curInvest", cJSON_CreateString(self->curInv));
	return invSmpJSON;
}

// Function that forms the line from the whole list of investors that present in our program
// @Returns: line (constructed from all investors from list) that is presented in cJSON form.
// Free a line after usage with built-in free() function!
char * investor_parseAllToJSON(const invArr_t * self) {
	cJSON * invArrJSON = cJSON_CreateArray();
	for (int i = 0; i < list_getSize(self->investors); i++) {
		investor_t * invBuff = (investor_t *)list_get(self->investors, i);
		cJSON * invJSON = investor_serializeJSON(invBuff);
		cJSON_AddItemToArray(invArrJSON, invJSON);
	}
	char * buffJSON = cJSON_Print(invArrJSON);
	cJSON_Delete(invArrJSON);
	return buffJSON;
}

// Function that forms the line from the single investor
// @Returns: line (constructed from one investor) that is presented in cJSON form.
// Free a line after usage with built-in free() function!
char * investor_parseToJSON(const investor_t * self) {
    cJSON * invJSON = investor_serializeJSON(self);
	char * buffJSON = cJSON_Print(invJSON);
	cJSON_Delete(invJSON);
    return buffJSON;
}

// ====================Working with HTML (HTML) requests====================

// Function that forms the line from the whole list of investors that present in our program
// @Returns: line (constructed from all investors from list) that is presented in HTML form.
// Free a line after usage with built-in free() function!
char * investor_parseAllToHTML(const invArr_t * self) {
	char * buffHTML = calloc(10000, sizeof(char));
	char buffInvestor[1000];
	char buffURLInvestor[100];
	// constructing (opening) a "carcass" for the HTML table (labels)
	sprintf(buffHTML,
		"<html><head></head><body><table border=\"1\">"
		"<tr><td>URL</td>"
		"<td>Name</td>"
		"<td>Surname</td></tr>");

	// inserting all investors in this HTML table
	for (int i = 0; i < list_getSize(self->investors); i++) {
		investor_t * invBuff = list_get(self->investors, i);
		// link to the full description of investor
		sprintf(buffURLInvestor,
			"<a href=\"/investors/%d\">Investor #%d</a>",
			invBuff->id, invBuff->id);

		// actually inserting all the info about investor into created HTML table
		sprintf(buffInvestor,
			"<tr><td>%s</td>"
			"<td>%s</td>"
			"<td>%s</td></tr>",
			buffURLInvestor, invBuff->name, invBuff->surname);
		strcat(buffHTML, buffInvestor);
	}
	// closing a "carcass" for the HTML table
	strcat(buffHTML, "</table></body>");

	return buffHTML;
}


// Function that forms the line from the single investor
// @Returns: line (constructed from one investor) that is presented in HTML form.
// Free a line after usage with built-in free() function!
char * investor_parseToHTML(const investor_t * self) {
	char * buffHTML = calloc(10000, sizeof(char));
	// the simple HTML table with labels and one investor with full description inside
	sprintf(buffHTML,
		"<html><head></head><body><table border=\"1\">"
		"<tr><td>ID</td>"
		"<td>Name</td>"
		"<td>Nickname</td>"
		"<td>Surname</td>"
		"<td>Rating</td>"
		"<td>FirstInv</td>"
		"<td>Exp</td>"
		"<td>MoneyInv</td>"
		"<td>Project</td></tr>"
		"<tr><td>%d</td>"
		"<td>%s</td>"
		"<td>%s</td>"
		"<td>%s</td>"
		"<td>%.2f</td>"
		"<td>%d-%d-%d</td>"
		"<td>%d</td>"
		"<td>%d</td>"
		"<td>%s</td></tr>"
		"</table></body>",
		self->id, self->name, self->surname,
		self->nickname, self->rating, self->firstInv.tm_year,
		self->firstInv.tm_mday, self->firstInv.tm_mon, self->exp,
		self->moneyInv, self->curInv);

	return buffHTML;
}