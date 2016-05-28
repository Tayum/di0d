#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "server.h"
#include "studentStruct.h"
#include "FSHelper/FSHelper.h"
#include "cJSON/cJSON.h"
#include "database.h"

// ====================cJSON====================

// Constructing a CJSON form from the single student-struct
// The function is static as far as it is not used in other files.
static cJSON * student_serializeJSON(const student_t * self) {
	cJSON * studSmpJSON = cJSON_CreateObject();
	cJSON_AddItemToObject(studSmpJSON, "student", cJSON_CreateString(self->student));
	cJSON_AddItemToObject(studSmpJSON, "group", cJSON_CreateString(self->group));
	cJSON_AddItemToObject(studSmpJSON, "variant", cJSON_CreateNumber(self->variant));

	return studSmpJSON;
}

// Function that forms the line from the single student
// @Returns: line (constructed from one student) that is presented in cJSON form.
// Free a line after usage with built-in free() function!
char * student_parseToJSON(const student_t * self) {
	cJSON * studentJSON = student_serializeJSON(self);
	char * buffJSON = cJSON_Print(studentJSON);
	cJSON_Delete(studentJSON);
	return buffJSON;
}

// ====================SERVER====================

static void server_TASK1_info(socket_t * client, http_request_t * req, student_t * self);
static void server_TASK3_database(socket_t * client, http_request_t * req, database_t * db, investorList_t * invList);
static void server_TASK4_newFile(socket_t * client, http_request_t * req);
static void server_TASK4_data(socket_t * client, http_request_t * req);
static void server_invalidResponce(socket_t * client, char * message);

// ====================MAIN FUNCTION, USED IN MAIN====================

// ANY TASK:
// Analyze the path of request
void server_analyzeRequest(http_request_t * request, socket_t * client, student_t * student, database_t * db, investorList_t * invList) {

	// TASK 1: myInfo
	if (strcmp(request->uri, "/info") == 0 || strcmp(request->uri, "/info/") == 0) {
		server_TASK1_info(client, request, student); // socket_close() function inside
	}
	// TASK 4: POST request
	else if (strcmp(request->uri, "/file-new") == 0 || strcmp(request->uri, "/file-new/") == 0) {
		server_TASK4_newFile(client, request); // socket_close() function inside
	}
	// TASK 4: data
	else if (strcmp(request->uri, "/data") == 0 || strcmp(request->uri, "/data/") == 0) {
		server_TASK4_data(client, request); // socket_close() function inside
	}
	// TASK 3: database
	else if (strcmp(request->uri, "/database") == 0 || strcmp(request->uri, "/database/") == 0) {
		server_TASK3_database(client, request, db, invList); // socket_close() function inside
	}
	// DEFAULT
	// default invalid path
	else {
		server_invalidResponce(client, "Invalid path."); // socket_close() function inside
	}
}

// ====================OTHER CONNECTED WITH SERVER FUNCTIONS====================

// TASK 1:
// INFO ABOUT STUDENT TO CLIENT
static void server_TASK1_info(socket_t * client, http_request_t * req, student_t * self) {
	char strBuf[10240];
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		char * studentJSON = student_parseToJSON(self);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(studentJSON), studentJSON);
		free(studentJSON);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}
	socket_write_string(client, strBuf);
	socket_close(client);
}

// TASK 3:
// INIT FROM DATABASE AND GIVE INFO TO CLIENT
static void server_TASK3_database(socket_t * client, http_request_t * req, database_t * db, investorList_t * invList) {
	char strBuf[10240];
	database_readInvList(db, invList);
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		char * infoMsg = "Hello, user. You should've received the list of cJSON investors, but that task is not done."
			" But half of task is done: the investors are initialized! Check the investor.c/.h, database.c/.h files, please...";
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(infoMsg), infoMsg);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}
	socket_write_string(client, strBuf);
	socket_close(client);
}

// TASK 4:
// GET FOR THE PAGE WITH POST REQUEST
static void server_TASK4_newFile(socket_t * client, http_request_t * req) {
	char strBuf[10240];
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		char line[1000];
		strcpy(line, "<html><head><h1>PLEASE READ CAREFULLY!</h1>Note, that whitespaces and other symbols <h4>WILL BE INTERPRETTED IMPROPERLY!</h4></head><body><form action=\"http://127.0.0.1:5000/data\" method=\"POST\">"
			"Input your text here:<br><textarea rows=\"10\" cols=\"100\" name=\"thyText\">SampleText</textarea><br>"
			"<br><input type=\"submit\" value='Send DATA' /></form></body></html>");
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(line), line);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}
	socket_write_string(client, strBuf);
	socket_close(client);
}

// TASK 4:
// POST REQUEST FOR THE RESULT OF THE GET REQUEST IN PREVIOUS FUNCTION:
// Returns the same info to user that he used to write in textarea and writes this info to file
static void server_TASK4_data(socket_t * client, http_request_t * req) {
	char strBuf[10240];
	// =====POST=====
	if (strcmp(req->method, "POST") == 0) {
		// The info:
		char * str = http_request_getArg(req, "thyText");
		// Checks if dir exists
		const char * directory = "C:\\Users\\Student\\Documents\\Different\\ProgBase\\Term_2\\zCW_2\\CW_2\\CW_2\\testFile"; // CHANGE DIR HERE!
		int check = dir_exists(directory);
		if (check == 0) {
			server_invalidResponce(client, "No such directory");
			return;
		}
		// Write to file
		FILE * fwPtr = fopen("testFile\\data.txt", "w"); // CHANGE DIR HERE! (it opens the testFile dir, situated in the root dir of project)
		if (fwPtr == NULL) {
			server_invalidResponce(client, "Error while opening file");
			return;
		}
		fprintf(fwPtr, "%s\n", str);
		fclose(fwPtr);
		// Write the info back to client
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(str), str);
	}
	// =====Invalid command=====
	else {
		server_invalidResponce(client, "Invalid command.");
		return;
	}
	socket_write_string(client, strBuf);
	socket_close(client);
}

// ANY TASK:
// Invalid responce message
static void server_invalidResponce(socket_t * client, char * message) {
	char strBuf[1024];
	char * errText = message;

	sprintf(strBuf,
		"HTTP/1.1 404 \n"
		"Content-Type: application/json\n"
		"Content-Length: %zu\n"
		"\n%s", strlen(errText), errText);

	socket_write_string(client, strBuf);
	socket_close(client);
}