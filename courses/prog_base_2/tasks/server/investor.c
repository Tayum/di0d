#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cJSON/cJSON.h"
#include "investor.h"

//CREATING NEW SAMPLE OF INVESTOR
investor_t investor_new(void) {
	investor_t invSmp;
	invSmp.id = -1;
	invSmp.name = "NoName";
	invSmp.nickname = "NoNickname";
	invSmp.surname = "NoSurname";
	invSmp.rating = 0.0;
	//date
	memset(&invSmp.firstInv, 0, sizeof(invSmp.firstInv));
	invSmp.firstInv.tm_year = 1900;
	invSmp.firstInv.tm_mday = 1;
	invSmp.firstInv.tm_mon = 1;
	//
	invSmp.exp = 0;
	invSmp.moneyInv = 0;
	invSmp.curInv = "NoCurInv";
	return invSmp;
}

//CONSTRUCTING A CJSON FORM OF INVESTOR FROM THE INVESTOR-STRUCT
cJSON * investor_serializeJSON(const investor_t * self) {
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

//FORMING A LINE FROM THE CJSON ARRAY-FORM OF ALL INVESTORS
char * investor_parseAllToJSON(const investor_t * invArr, int size) {
	cJSON * invArrJSON = cJSON_CreateArray();
	for (int i = 0; i < size; i++) {
		cJSON * invJSON = investor_serializeJSON(invArr + i);
		cJSON_AddItemToArray(invArrJSON, invJSON);
	}
	char * buffJSON = cJSON_Print(invArrJSON);
	cJSON_Delete(invArrJSON);
	return buffJSON;
}

//FORMING A LINE FROM A SINGLE CJSON INVESTOR
char * investor_parseToJSON(const investor_t * self) {
    cJSON * invJSON = investor_serializeJSON(self);
	char * buffJSON = cJSON_Print(invJSON);
	cJSON_Delete(invJSON);
    return buffJSON;
}