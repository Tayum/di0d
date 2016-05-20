#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "investorStruct.h"
#include "server.h"

//				Main function that analyses the path of the request.
//	It calls the described below functions basing on the path that request is sent to.

// @Returns (prints):		Proper answer to the client
void server_analyzeRequest(http_request_t * request, socket_t * client, invArr_t * investorArray) {

	// HTML: homepage
	if (strcmp(request->uri, "/") == 0) {
		server_HTML_homepage(client, "Hello. Pls, proceed further to list of investors (/investors)"); // socket_close() function inside
	}

	// HTML: new-investor
	else if (strcmp(request->uri, "/new-investor") == 0 || strcmp(request->uri, "/new-investor/") == 0) {
		server_HTML_newInvestor(investorArray, client); // socket_close() function inside
	}

	// HTML: all investors
	else if (strcmp(request->uri, "/investors") == 0 || strcmp(request->uri, "/investors/") == 0) {
		server_HTML_allInvestors(investorArray, client, request); // socket_close() function inside
	}

	// HTML: single investor (by ID)
	// condition that is working with the index of the investor
	else if (strstr(request->uri, "/investors/") != NULL && strstr(request->uri, "/api/investors/") == NULL) {
		// checking if index is proper (i.e. is a number)
		char * string = strstr(request->uri, "/investors/");
		char * token = strtok(request->uri, "/");
		token = strtok(NULL, "/");
		if (token != NULL && isdigit(token[0]) != 0) {
			// checking if index presents among our investors
			int ID = atoi(token);
			if (invArr_isThereID(investorArray, ID) == INDEX_COR) {
				server_HTML_investorByID(investorArray, client, request, ID); // socket_close() function inside
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
		server_API_allInvestors(investorArray, client, request); // socket_close() function inside
	}

	// API: single investor (by ID)
	// condition that is working with the index of the investor
	else if (strstr(request->uri, "/api/investors/") != NULL) {
		// checking if index is proper (i.e. is a number)
		char * string = strstr(request->uri, "/api/investors/");
		char * token = strtok(request->uri, "/");
		token = strtok(NULL, "/");
		token = strtok(NULL, "/");
		if (token != NULL && isdigit(token[0]) != 0) {
			// checking if index presents among our investors
			int ID = atoi(token);
			if (invArr_isThereID(investorArray, ID) == INDEX_COR) {
				server_API_investorByID(investorArray, client, request, ID); // socket_close() function inside
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
void server_API_allInvestors(invArr_t * self, socket_t * client, http_request_t * req) {
	char strBuf[10240];
	
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		char * invArrJSON = investor_parseAllToJSON(self);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invArrJSON), invArrJSON);
		free(invArrJSON);
	}
	// =====POST=====
	else if (strcmp(req->method, "POST") == 0) {
		// ID field is assigned automatically.
		// Every new info is briefly checked on validity.
		// If some field is not valid - the investor is not added.
		investor_t * newInvestor = investor_new();
		// Name field:
		char * str = http_request_getArg(req, "name");
		if (str != NULL && strlen(str) < 25) {
			newInvestor->name = str;
		}
		else {
			server_invalidResponce(client, "Invalid name.");
			return;
		}
		// Nickname field:
		str = http_request_getArg(req, "nickname");
		if (str != NULL && strlen(str) < 25) {
			newInvestor->nickname = str;
		}
		else {
			server_invalidResponce(client, "Invalid nickname.");
			return;
		}
		// Surname field:
		str = http_request_getArg(req, "surname");
		if (str != NULL && strlen(str) < 25) {
			newInvestor->surname = str;
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
			newInvestor->curInv = str;
		}
		else {
			server_invalidResponce(client, "Invalid project.");
			return;
		}
		
		// adding investor to our array (list)
		// (finding the proper ID for the investor)
		int newID = invArr_seekForFreeID(self);
		newInvestor->id = newID;
		invArr_addInvByIndex(self, newInvestor, newID);

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

// Command:				GET						DELETE					For a single investor (by index)

// @Returns (prints): investor		message about successful deleting =====OR===== error message
void server_API_investorByID(invArr_t * self, socket_t * client, http_request_t * req, int ID) {
	char strBuf[10240];
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		investor_t * investor = invArr_getInvByID(self, ID);
		char * invJSON = investor_parseToJSON(investor);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(invJSON), invJSON);
		free(invJSON);
	}
	// =====DELETE=====
	else if (strcmp(req->method, "DELETE") == 0) {
		investor_t * delInvestor = invArr_removeInvByID(self, ID);
		// if something went wrong
		if (delInvestor == NULL) {
			server_invalidResponce(client, "The investor was not deleted.");
			return;
		}

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
void server_HTML_allInvestors(invArr_t * self, socket_t * client, http_request_t * req) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		char * line = investor_parseAllToHTML(self);

		char link[1024];
		strcpy(link, "<br/><a href=\"/new-investor\">New-investor</a>");

		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s%s", (strlen(line) + strlen(link)), line, link);

		free(line);
	}

	// =====POST=====
	else if (strcmp(req->method, "POST") == 0) {
		// ID field is assigned automatically.
		// Every new info is briefly checked on validity.
		// If some field is not valid - the investor is not added.
		investor_t * newInvestor = investor_new();
		// Name field:
		char * str = http_request_getArg(req, "name");
		if (str != NULL && strlen(str) < 25) {
			newInvestor->name = str;
		}
		else {
			server_invalidResponce(client, "Invalid name.");
			return;
		}
		// Nickname field:
		str = http_request_getArg(req, "nickname");
		if (str != NULL && strlen(str) < 25) {
			newInvestor->nickname = str;
		}
		else {
			server_invalidResponce(client, "Invalid nickname.");
			return;
		}
		// Surname field:
		str = http_request_getArg(req, "surname");
		if (str != NULL && strlen(str) < 25) {
			newInvestor->surname = str;
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
			newInvestor->curInv = str;
		}
		else {
			server_invalidResponce(client, "Invalid project.");
			return;
		}

		// Adding investor to our array (list)
		int newID = invArr_seekForFreeID(self);
		newInvestor->id = newID;
		invArr_addInvByIndex(self, newInvestor, newID);

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
void server_HTML_newInvestor(invArr_t * self, socket_t * client) {
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
void server_HTML_investorByID(invArr_t * self, socket_t * client, http_request_t * req, int ID) {
	char strBuf[10240];

	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		investor_t * investor = invArr_getInvByID(self, ID);
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

		free(line);
	}

	// =====DELETE=====
	else if (strcmp(req->method, "DELETE") == 0) {
		investor_t * delInvestor = invArr_removeInvByID(self, ID);
		// if something went wrong
		if (delInvestor == NULL) {
			server_invalidResponce(client, "The investor was not deleted.");
			return;
		}

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