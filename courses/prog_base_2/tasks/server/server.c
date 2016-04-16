#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "server.h"

//MAIN ARRAY WITH STRUCTS THAT PROGRAM STARTS WITH
investor_t investorArray[] = {
	{
		.id = 0,
		.name = "Garrosh",
		.nickname = "Warrior",
		.surname = "Hellscream",
		.rating = 8.9,
		.firstInv.tm_year = 1970,
		.firstInv.tm_mday = 25,
		.firstInv.tm_mon = 9,
		.exp = 46,
		.moneyInv = 10000000,
		.curInv = "ArmorUp",
	},
	{
		.id = 1,
		.name = "Anduin",
		.nickname = "Priest",
		.surname = "Wrynn",
		.rating = 5.6,
		.firstInv.tm_year = 1995,
		.firstInv.tm_mday = 15,
		.firstInv.tm_mon = 3,
		.exp = 21,
		.moneyInv = 1000000,
		.curInv = "LesserHeal",
	},
	{
		.id = 2,
		.name = "Rexxar",
		.nickname = "Hunter",
		.surname = "Face",
		.rating = 8.1,
		.firstInv.tm_year = 1985,
		.firstInv.tm_mday = 20,
		.firstInv.tm_mon = 1,
		.exp = 31,
		.moneyInv = 5000000,
		.curInv = "SteadyShot",
	}
};

//FUNC THAT RETURNS SIZE OF OUR MAIN ARRAY WITH STRUCTS
int invArray_getSize(void) {
	return sizeof(investorArray) / sizeof(investorArray[0]);
}

//			ROOT PAGE OF THE SERVER
//RETURNS:		WELCOME MSG
void server_homepage(socket_t * client) {
	char homeBuf[10240];
	char * welcomeText = "Hello. Pls, proceed further to list of investors (/investors)";
	sprintf(homeBuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s", strlen(welcomeText), welcomeText);
	socket_write_string(client, homeBuf);
	socket_close(client);
}

//COMMAND:		GET						(FOR ALL INVESTORS)
//RETURNS:	ALL INVESTORS				=====OR===== ERROR MSG
void server_allInvestors(socket_t * client, http_request_t * req) {
	char strbuf[10240];
	if (strcmp(req->method, "GET") == 0) {
		int amount = sizeof(investorArray) / sizeof(investorArray[0]);
		char * invArrJSON = investor_parseAllToJSON(investorArray, amount);
		sprintf(strbuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invArrJSON), invArrJSON);
		free(invArrJSON);
	}
	else {
		char * errText = "Invalid command!";
		sprintf(strbuf,
			"HTTP/1.1 404 \n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"\n%s", strlen(errText), errText);
	}
	socket_write_string(client, strbuf);
	socket_close(client);
}

//COMMAND:	GET					POST					DELETE						FOR A SINGLE INVESTOR (BY INDEX)
//RETURNS: INVESTOR		MODIFIED INVESTOR		MSG ABOUT SUCCESSFUL DELETING =====OR===== ERROR MSG
void server_investorById(socket_t * client, http_request_t * req, int index) {
	char strbuf[10240];
	//=====GET COMMAND=====
	if (strcmp(req->method, "GET") == 0) {
		char * invJSON = investor_parseToJSON(&investorArray[index]);
		sprintf(strbuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invJSON), invJSON);
		free(invJSON);
	}
	//=====POST COMMAND=====
	else if (strcmp(req->method, "POST") == 0) {
		//ID FIELD NOT ALLOWED TO BE MODIFIED!
		//EVERY FIELD IS BRIEFLY CHECKED ON VALIDITY
		//NAME FIELD
		char * str = http_request_getArg(req, "name");
		if (str != NULL && strlen(str) < 25) {
			investorArray[index].name = str;
		}
		//NICKNAME FIELD
		str = http_request_getArg(req, "nickname");
		if (str != NULL && strlen(str) < 25) {
			investorArray[index].nickname = str;
		}
		//SURNAME FIELD
		str = http_request_getArg(req, "surname");
		if (str != NULL && strlen(str) < 25) {
			investorArray[index].surname = str;
		}
		//RATING FIELD
		str = http_request_getArg(req, "rating");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			investorArray[index].rating = atof(str);
		}
		//FIRST INVESTMENT (DATE STRUCT) FIELD
		str = http_request_getArg(req, "firstInvestmentDate");
		if (str != NULL) {
			//CHECKING IF DATA OF EVERY FIELD IS VALID
			if (str[5] != NULL && str[5] == '-' && atoi(str) > 1900 && atoi(str) < 2016) {
				str = strtok(str, "-");
				str = strtok(NULL, "-");
				if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 12)) {
					str = strtok(NULL, "-");
					if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 31)) {
						//ALL DATA IS VALID:
						str = http_request_getArg(req, "firstInvestmentDate");
						//YEAR
						investorArray[index].firstInv.tm_year = atoi(str);
						//MON
						str = strtok(str, "-");
						str = strtok(NULL, "-");
						investorArray[index].firstInv.tm_mon = atoi(str);
						//DAY
						str = strtok(NULL, "-");
						investorArray[index].firstInv.tm_mday = atoi(str);
					}
				}
			}
		}
		//EXPERIENCE FIELD
		str = http_request_getArg(req, "experienceYears");
		if (str != NULL && isdigit(str[0]) != 0 && atoi(str) >= 0) {
			investorArray[index].exp = atoi(str);
		}
		//TOTAL MONEY INVESTED FIELD
		str = http_request_getArg(req, "totalMoneyInvested");
		if (str != NULL && isdigit(str[0]) != 0 && atoi(str) >= 0) {
			investorArray[index].moneyInv = atoi(str);
		}
		//CURRENT INVESTMENT PROJECT FIELD
		str = http_request_getArg(req, "curInvest");
		if (str != NULL && strlen(str) < 100) {
			investorArray[index].curInv = str;
		}

		char * modInvJSON = investor_parseToJSON(&investorArray[index]);

		//PRINTF'ING TO CONSOLE
		printf("New student (instead of %i-th one):\n%s\n", index, modInvJSON);
		//GIVING INFO TO CLIENT
		sprintf(strbuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(modInvJSON), modInvJSON);
		free(modInvJSON);
	}
	//=====DELETE COMMAND=====
	else if (strcmp(req->method, "DELETE") == 0) {
		investorArray[index] = investor_new();

		//ID FIELD IS KEPT!
		investorArray[index].id = index;

		char * delInvJSON = investor_parseToJSON(&investorArray[index]);
		//PRINTF'ING TO CONSOLE
		printf("Deleted student (%i-th one):\n%s\n", index, delInvJSON);
		//GIVING INFO TO CLIENT
		char * delText = "Student deleted successfully!";
		sprintf(strbuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(delText), delText);
		free(delInvJSON);
	}
	//=====INVALID COMMAND=====
	else {
		char * errText = "Invalid command!";
		sprintf(strbuf,
			"HTTP/1.1 404 \n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"\n%s", strlen(errText), errText);
	}
	socket_write_string(client, strbuf);
	socket_close(client);
}

//FUNCTION THAT PRINTS ERROR MSG
//RETURNS:		 ERROR MSG
void server_invPath(socket_t * client) {
	char replyBuf[1024];
	char * errText = "Invalid path!";
	sprintf(replyBuf,
		"HTTP/1.1 404 \n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"\n%s", strlen(errText), errText);
	socket_write_string(client, replyBuf);
	socket_close(client);
}