#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "investorStruct.h"
#include "server.h"


//				Main function that analyses the path of the request.
//	It calls the described below functions basing on the path that request is sent to.

// @Returns (prints):		Proper answer to the client
void server_analyzeRequest(http_request_t * request, socket_t * client, database_t * db) {

	// HTML: homepage
	if (strcmp(request->uri, "/") == 0) {
		server_HTML_homepage(client, "Hello. Pls, proceed further to list of investors (/investors)"); // socket_close() function inside
	}

	// HTML: new-investor
	else if (strcmp(request->uri, "/new-investor") == 0 || strcmp(request->uri, "/new-investor/") == 0) {
		server_HTML_newInvestor(db, client); // socket_close() function inside
	}

	// HTML: all investors
	else if (strcmp(request->uri, "/investors") == 0 || strcmp(request->uri, "/investors/") == 0) {
		server_HTML_allInvestors(db, client, request); // socket_close() function inside
	}

	// HTML: single investor (by ID)
	// condition that is working with the index of the investor
	else if (strstr(request->uri, "/investors/") != NULL && strstr(request->uri, "/api/investors/") == NULL) {
		// checking if index is proper (i.e. is a number)
		char * token = strtok(request->uri, "/");
		token = strtok(NULL, "/");
		if (token != NULL && isdigit(token[0]) != 0) {
			// checking if index presents among our investors
			int ID = atoi(token);
			if (database_isThereID(db, ID) == INDEX_COR) {
				server_HTML_investorByID(db, client, request, ID); // socket_close() function inside
			}
			// index does not present among our investors
			else {
				server_invalidResponce(client, "Invalid path."); // socket_close() function inside
			}
		}
		// index is not proper (i.e. is not a number)
		else {
			server_invalidResponce(client, "Invalid path."); // socket_close() function inside
		}
	}


	// API: homepage
	else if (strcmp(request->uri, "/api") == 0 || strcmp(request->uri, "/api/") == 0) {
		server_API_homepage(client, "Hello. Pls, proceed further to list of investors (/api/investors)"); // socket_close() function inside
	}

	// API: all investors
	else if (strcmp(request->uri, "/api/investors") == 0 || strcmp(request->uri, "/api/investors/") == 0) {
		server_API_allInvestors(db, client, request); // socket_close() function inside
	}
	// API: investors with condition WHERE
	else if (strstr(request->uri, "/api/investors/") == NULL && strstr(request->uri, "/api/investors") != NULL) {
		int moneyInv;
		condition moneyInvCond;
		int exp;
		condition expCond;
		char * token = strtok(request->uri, "/=?&");
		token = strtok(NULL, "/=?&");
		if (token != NULL && strcmp(token, "investors") == 0) {
			token = strtok(NULL, "/=?&");
			// Is 'key' correct?:
			if (token != NULL && (strcmp(token, "moneyInv_gt") == 0 || strcmp(token, "moneyInv_lt") == 0 || strcmp(token, "exp_gt") == 0 || strcmp(token, "exp_lt") == 0)) {
				// If first condition is about moneyInv...
				if (strcmp(token, "moneyInv_gt") == 0 || strcmp(token, "moneyInv_lt") == 0) {
					if (strcmp(token, "moneyInv_gt") == 0) {
						moneyInvCond = GREATER;
					}
					else if (strcmp(token, "moneyInv_lt") == 0) {
						moneyInvCond = LESS;
					}
					token = strtok(NULL, "/=?&");
					// Is 'value' correct?:
					if (token != NULL && isdigit(token[0]) != 0) {
						moneyInv = atoi(token);
						// ...Then second condition must be about exp
						token = strtok(NULL, "/=?&");
						// Is 'key' correct?:
						if (token != NULL && (strcmp(token, "exp_gt") == 0 || strcmp(token, "exp_lt") == 0)) {
							if (strcmp(token, "exp_gt") == 0) {
								expCond = GREATER;
							}
							else if (strcmp(token, "exp_lt") == 0) {
								expCond = LESS;
							}
							token = strtok(NULL, "/=?&");
							// Is 'value' correct?:
							if (token != NULL && isdigit(token[0]) != 0) {
								exp = atoi(token);
								server_API_allInvestors_WHERE(db, client, request, moneyInv, moneyInvCond, exp, expCond); // socket_close() function inside
							}
							else {
								server_invalidResponce(client, "Invalid path."); // socket_close() function inside
							}
						}
						else {
							server_invalidResponce(client, "Invalid path."); // socket_close() function inside
						}
					}
					else {
						server_invalidResponce(client, "Invalid path."); // socket_close() function inside
					}
				}
				// If first condition is about exp...
				else if (strcmp(token, "exp_gt") == 0 || strcmp(token, "exp_lt") == 0) {
					if (strcmp(token, "exp_gt") == 0) {
						expCond = GREATER;
					}
					else if (strcmp(token, "exp_lt") == 0) {
						expCond = LESS;
					}
					token = strtok(NULL, "/=?&");
					// Is 'value' correct?:
					if (token != NULL && isdigit(token[0]) != 0) {
						exp = atoi(token);
						// ...Then second condition must be about moneyInv
						token = strtok(NULL, "/=?&");
						// Is 'key' correct?:
						if (token != NULL && (strcmp(token, "moneyInv_gt") == 0 || strcmp(token, "moneyInv_lt") == 0)) {
							if (strcmp(token, "moneyInv_gt") == 0) {
								moneyInvCond = GREATER;
							}
							else if (strcmp(token, "moneyInv_lt") == 0) {
								moneyInvCond = LESS;
							}
							token = strtok(NULL, "/=?&");
							// Is 'value' correct?:
							if (token != NULL && isdigit(token[0]) != 0) {
								moneyInv = atoi(token);
								server_API_allInvestors_WHERE(db, client, request, moneyInv, moneyInvCond, exp, expCond); // socket_close() function inside
							}
							else {
								server_invalidResponce(client, "Invalid path."); // socket_close() function inside
							}
						}
						else {
							server_invalidResponce(client, "Invalid path."); // socket_close() function inside
						}
					}
					else {
						server_invalidResponce(client, "Invalid path."); // socket_close() function inside
					}
				}
			}
		}
		else {
			server_invalidResponce(client, "Invalid path."); // socket_close() function inside
		}
	}

	// API: single investor (by ID)
	// condition that is working with the index of the investor
	else if (strstr(request->uri, "/api/investors/") != NULL) {
		// checking if index is proper (i.e. is a number)
		char * token = strtok(request->uri, "/");
		token = strtok(NULL, "/");
		token = strtok(NULL, "/");
		if (token != NULL && isdigit(token[0]) != 0) {
			// checking if index presents among our investors
			int ID = atoi(token);
			if (database_isThereID(db, ID) == INDEX_COR) {
				server_API_investorByID(db, client, request, ID); // socket_close() function inside
			}
			// index does not present among our investors
			else {
				server_invalidResponce(client, "Invalid path."); // socket_close() function inside
			}
		}
		// index is not proper (i.e. is not a number)
		else {
			server_invalidResponce(client, "Invalid path."); // socket_close() function inside
		}
	}


	// HTML/API: default
	// default invalid path
	else {
		server_invalidResponce(client, "Invalid path."); // socket_close() function inside
	}

}


// ========================================FUNCTIONS THAT ARE USED IF YOU USE THE API FORM========================================

//						Root page of the server

// @Returns (prints):		Welcome message
void server_API_homepage(socket_t * client, char * message) {
	char strBuf[10240];

	sprintf(strBuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s", strlen(message), message);

	socket_write_string(client, strBuf);
	socket_close(client);
}

// Command:					GET (for all investors)			POST (for single investor)

// @Returns (prints):			all investors						new investor			=====OR===== error message
void server_API_allInvestors(database_t * db, socket_t * client, http_request_t * req) {
	char strBuf[10240];
	
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		invArr_t * invArr = database_getInvListFromDB(db);
		char * invArrJSON = investor_parseAllToJSON(invArr);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invArrJSON), invArrJSON);
		free(invArr);
		free(invArrJSON);
	}
	// =====POST=====
	else if (strcmp(req->method, "POST") == 0) {
		// ID field is assigned automatically in database.
		// Every new info is briefly checked on validity.
		// If some field is not valid - the investor is not added.
		investor_t * newInvestor = investor_new();
		// Name field:
		char * str = http_request_getArg(req, "name");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newInvestor->name, str);
		}
		else {
			server_invalidResponce(client, "Invalid name.");
			return;
		}
		// Nickname field:
		str = http_request_getArg(req, "nickname");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newInvestor->nickname, str);
		}
		else {
			server_invalidResponce(client, "Invalid nickname.");
			return;
		}
		// Surname field:
		str = http_request_getArg(req, "surname");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newInvestor->surname, str);
		}
		else {
			server_invalidResponce(client, "Invalid surname.");
			return;
		}
		// Rating field:
		str = http_request_getArg(req, "rating");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			newInvestor->rating = atof(str);
		}
		else {
			server_invalidResponce(client, "Invalid rating.");
			return;
		}
		// First investment (date struct) field:
		str = http_request_getArg(req, "firstInvestmentDate");
		// Buffer for (str) string. First (str) will be checked on validity
		// and if everything is fine - the data will be copied again
		// and assigned to the fields.
		char buffForStr[30];
		strcpy(buffForStr, str);
		if (str != NULL) {
			// Checks if data of every field in date struct is valid:
			if (str[4] != NULL && str[4] == '-' && atoi(str) > 1900 && atoi(str) < 2016) {
				str = strtok(str, "-");
				str = strtok(NULL, "-");
				if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 12)) {
					str = strtok(NULL, "-");
					if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 31)) {
						// All data is valid:
						str = buffForStr;
						// Year:
						newInvestor->firstInv.tm_year = atoi(str);
						// Month:
						str = strtok(str, "-");
						str = strtok(NULL, "-");
						newInvestor->firstInv.tm_mon = atoi(str);
						// Day:
						str = strtok(NULL, "-");
						newInvestor->firstInv.tm_mday = atoi(str);
					}
					else {
						server_invalidResponce(client, "Invalid day.");
						return;
					}
				}
				else {
					server_invalidResponce(client, "Invalid month.");
					return;
				}
			}
			else {
				server_invalidResponce(client, "Invalid year.");
				return;
			}
		}
		// Experience field:
		str = http_request_getArg(req, "experienceYears");
		if (str != NULL && isdigit(str[0]) != 0 && atoi(str) >= 0) {
			newInvestor->exp = atoi(str);
		}
		else {
			server_invalidResponce(client, "Invalid experience.");
			return;
		}
		// Total money invested field:
		str = http_request_getArg(req, "totalMoneyInvested");
		if (str != NULL && isdigit(str[0]) != 0 && atoi(str) >= 0) {
			newInvestor->moneyInv = atoi(str);
		}
		else {
			server_invalidResponce(client, "Invalid money invested.");
			return;
		}
		// Current investment project field:
		str = http_request_getArg(req, "curInvest");
		if (str != NULL && strlen(str) < 100) {
			strcpy(newInvestor->curInv, str);
		}
		else {
			server_invalidResponce(client, "Invalid project.");
			return;
		}
		
		// Adding investor to database
		database_createInv(db, newInvestor);

		char * newInvestorJSON = investor_parseToJSON(newInvestor);
		// Printing info to console.
		printf("New investor created:\n%s\n", newInvestorJSON);
		// Giving info to the client.
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(newInvestorJSON), newInvestorJSON);
		free(newInvestor);
		free(newInvestorJSON);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}

// Command:								GET (for all investors)

// @Returns (prints):			all investors (according to WHERE condition)			=====OR===== error message
void server_API_allInvestors_WHERE(database_t * db, socket_t * client, http_request_t * req, int moneyInv, condition moneyInvSign, int exp, condition expSign) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		invArr_t * invWhereArr = database_getInvArrFromDB_WHERE(db, moneyInv, moneyInvSign, exp, expSign);
		char * invArrJSON = investor_parseAllToJSON(invWhereArr);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invArrJSON), invArrJSON);
		free(invArrJSON);
		invArr_free(invWhereArr);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}

// Command:				GET						DELETE					For a single investor (by index)

// @Returns (prints): investor		message about successful deleting =====OR===== error message
void server_API_investorByID(database_t * db, socket_t * client, http_request_t * req, int ID) {
	char strBuf[10240];
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		investor_t * investor = database_getInvFromDB(db, ID);
		char * invJSON = investor_parseToJSON(investor);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invJSON), invJSON);
		investor_free(investor);
		free(invJSON);
	}
	// =====DELETE=====
	else if (strcmp(req->method, "DELETE") == 0) {
		// Getting the investor (and his info) before it was deleted
		investor_t * delInvestor = database_getInvFromDB(db, ID);
		// If something went wrong
		if (delInvestor == NULL) {
			server_invalidResponce(client, "The investor was not deleted.");
			return;
		}
		// Deleting investor from database
		database_deleteInv(db, ID);

		char * delInvestorJSON = investor_parseToJSON(delInvestor);
		// Printing info to console.
		printf("Deleted investor (%i-th one):\n%s\n", ID, delInvestorJSON);
		// Giving info to the client.
		char * delText = "Investor deleted successfully!";

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(delText), delText);

		free(delInvestor);
		free(delInvestorJSON);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}
	socket_write_string(client, strBuf);
	socket_close(client);
}

// ========================================FUNCTIONS THAT ARE USED IF YOU USE THE HTML FORM========================================

//						Root page of the server

// @Returns (prints):		Welcome message
// (links):					allInvestors						
void server_HTML_homepage(socket_t * client, char * message) {
	char strBuf[10240];

	char link[1024];
	strcpy(link, "<br/><a href=\"/investors\">All investors</a>");

	sprintf(strBuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s%s", (strlen(message) + strlen(link)), message, link);
	socket_write_string(client, strBuf);
	socket_close(client);
}

// Command:								GET (for all investors)						POST (for single investor)

// @Returns (prints):			all investors (URLs, brief description)						new investor			=====OR===== error message
// (links):						each investor with full description (by ID)			HTML form to add new investor	
void server_HTML_allInvestors(database_t * db, socket_t * client, http_request_t * req) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		invArr_t * invArr = database_getInvListFromDB(db);
		char * line = investor_parseAllToHTML(invArr);

		char link[1024];
		strcpy(link, "<br/><a href=\"/new-investor\">New-investor</a>");

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s%s", (strlen(line) + strlen(link)), line, link);
		free(invArr);
		free(line);
	}

	// =====POST=====
	else if (strcmp(req->method, "POST") == 0) {
		// ID field is assigned automatically in database.
		// Every new info is briefly checked on validity.
		// If some field is not valid - the investor is not added.
		investor_t * newInvestor = investor_new();
		// Name field:
		char * str = http_request_getArg(req, "name");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newInvestor->name, str);
		}
		else {
			server_invalidResponce(client, "Invalid name.");
			return;
		}
		// Nickname field:
		str = http_request_getArg(req, "nickname");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newInvestor->nickname, str);
		}
		else {
			server_invalidResponce(client, "Invalid nickname.");
			return;
		}
		// Surname field:
		str = http_request_getArg(req, "surname");
		if (str != NULL && strlen(str) < 25) {
			strcpy(newInvestor->surname, str);
		}
		else {
			server_invalidResponce(client, "Invalid surname.");
			return;
		}
		// Rating field:
		str = http_request_getArg(req, "rating");
		if (str != NULL && isdigit(str[0]) != 0 && strlen(str) < 7) {
			newInvestor->rating = atof(str);
		}
		else {
			server_invalidResponce(client, "Invalid rating.");
			return;
		}
		// First investment (date struct) field:
		str = http_request_getArg(req, "firstInvestmentDate");
		// Buffer for (str) string. First (str) will be checked on validity
		// and if everything is fine - the data will be copied again
		// and assigned to the fields.
		char buffForStr[30];
		strcpy(buffForStr, str);
		if (str != NULL) {
			// Checks if data of every field in date struct is valid:
			if (str[4] != NULL && str[4] == '-' && atoi(str) > 1900 && atoi(str) < 2016) {
				str = strtok(str, "-");
				str = strtok(NULL, "-");
				if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 12)) {
					str = strtok(NULL, "-");
					if (str != NULL && (atoi(str) >= 1 && atoi(str) <= 31)) {
						// All data is valid:
						str = buffForStr;
						// Year:
						newInvestor->firstInv.tm_year = atoi(str);
						// Month:
						str = strtok(str, "-");
						str = strtok(NULL, "-");
						newInvestor->firstInv.tm_mon = atoi(str);
						// Day:
						str = strtok(NULL, "-");
						newInvestor->firstInv.tm_mday = atoi(str);
					}
					else {
						server_invalidResponce(client, "Invalid day.");
						return;
					}
				}
				else {
					server_invalidResponce(client, "Invalid month.");
					return;
				}
			}
			else {
				server_invalidResponce(client, "Invalid year.");
				return;
			}
		}
		// Experience field:
		str = http_request_getArg(req, "experienceYears");
		if (str != NULL && isdigit(str[0]) != 0 && atoi(str) >= 0) {
			newInvestor->exp = atoi(str);
		}
		else {
			server_invalidResponce(client, "Invalid experience.");
			return;
		}
		// Total money invested field:
		str = http_request_getArg(req, "totalMoneyInvested");
		if (str != NULL && isdigit(str[0]) != 0 && atoi(str) >= 0) {
			newInvestor->moneyInv = atoi(str);
		}
		else {
			server_invalidResponce(client, "Invalid money invested.");
			return;
		}
		// Current investment project field:
		str = http_request_getArg(req, "curInvest");
		if (str != NULL && strlen(str) < 100) {
			strcpy(newInvestor->curInv, str);
		}
		else {
			server_invalidResponce(client, "Invalid project.");
			return;
		}

		// Adding investor to our database
		database_createInv(db, newInvestor);

		char * newInvestorHTML = investor_parseToHTML(newInvestor);
		// Printing info to console.
		printf("New investor created:\n%s\n", newInvestorHTML);
		// Giving info to the client.
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(newInvestorHTML), newInvestorHTML);
		free(newInvestorHTML);
		free(newInvestor);
	}

	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}

// Command:								POST

// @Returns (prints):				new investor			=====OR===== error message
// (links):								--
void server_HTML_newInvestor(database_t * db, socket_t * client) {
	char strbuf[10240];
	char line[1000];
	// the HTML form to send post request
	strcpy(line, "<html><head></head><body><form action=\"http://127.0.0.1:5000/investors\" method=\"POST\">"
		"First Name:<br><input type=\"text\" name=\"name\" value='Ivan'><br>Nickname:<br>"
		"<input type=\"text\" name=\"nickname\" value='Vano'><br>"
		"Surname:<br><input type=\"text\" name=\"surname\" value=\"Ivanov\"><br>"
		"Rating:<br><input type=\"text\" name=\"rating\" value=\"5.5\"><br>"
		"First investment date:<br><input type=\"text\" name=\"firstInvestmentDate\" value=\"1995-01-01\"><br>"
		"Experience in years:<br><input type=\"text\" name=\"experienceYears\" value=\"10\"><br>"
		"Total money invested (in $):<br><input type=\"text\" name=\"totalMoneyInvested\" value=\"25000\"><br>"
		"Current investment project:<br><input type=\"text\" name=\"curInvest\" value=\"Memasiki\"><br>"
		"<input type=\"submit\" value='Send POST request' /></form></body></html>");

	sprintf(strbuf,
		"HTTP/1.1 200 OK\n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"Connection: keep-alive\n"
		"\n%s", strlen(line), line);

	socket_write_string(client, strbuf);
	socket_close(client);
}

// Command:						GET									DELETE					For a single investor (by index)

// @Returns (prints): investor (full description)		message about successful deleting =====OR===== error message
// (links):												link to delete the user with this ID
void server_HTML_investorByID(database_t * db, socket_t * client, http_request_t * req, int ID) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		investor_t * investor = database_getInvFromDB(db, ID);
		char * line = investor_parseToHTML(investor);

		char link[1024];
		char linkURL[100];
		// the DELETE link with proper index
		sprintf(linkURL,
			"\"http://127.0.0.1:5000/investors/%d\"",
			ID);

		// the main logic that the DELETE link consists of
		sprintf(link,
			"<br/><a href=\"#\" onclick=\"doDelete()\">Delete</a>"
			"<body><script>"
			"function doDelete() {"
			"var xhttp = new XMLHttpRequest();"
			"xhttp.open(\"DELETE\", %s, true);" // <-- %s (link) here -->
			"xhttp.send();}"
			"</script></body>",
			linkURL);// <-- link -->

		// info about the investor + delete link
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s%s", (strlen(line) + strlen(link)), line, link);
		free(investor);
		free(line);
	}

	// =====DELETE=====
	else if (strcmp(req->method, "DELETE") == 0) {
		// Getting the investor (and his info) before it was deleted
		investor_t * delInvestor = database_getInvFromDB(db, ID);
		// If something went wrong
		if (delInvestor == NULL) {
			server_invalidResponce(client, "The investor was not deleted.");
			return;
		}
		// Deleting the investor from database
		database_deleteInv(db, ID);

		char * delInvestorHTML = investor_parseToHTML(delInvestor);
		// Printing info to console.
		printf("Deleted investor (%i-th one):\n%s\n", ID, delInvestorHTML);
		// Giving info to the client.
		char * delText = "Investor deleted successfully!";

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(delText), delText);

		free(delInvestorHTML);
		free(delInvestor);
	}

	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}

	socket_write_string(client, strBuf);
	socket_close(client);
}


// The function is used both in API and HTML requests.
//		Function that prints the given error message

// @Returns (prints):	error message
void server_invalidResponce(socket_t * client, char * message) {
	char strBuf[1024];
	char * errText = message;

	sprintf(strBuf,
		"HTTP/1.1 404 \n"
		"Content-Type: text/html\n"
		"Content-Length: %zu\n"
		"\n%s", strlen(errText), errText);

	socket_write_string(client, strBuf);
	socket_close(client);
}