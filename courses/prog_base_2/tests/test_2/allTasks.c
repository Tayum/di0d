#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "allTasks.h"
#include "cJSON/cJSON.h"
#include "FSHelper/FSHelper.h"

// ====================cJSON====================

// Constructing a CJSON form from the single investor-struct
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
	cJSON * invJSON = student_serializeJSON(self);
	char * buffJSON = cJSON_Print(invJSON);
	cJSON_Delete(invJSON);
	return buffJSON;
}


// ====================SERVER====================

// INVALID
void server_invalidResponce(socket_t * client, char * message) {
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

// INFO ABOUT STUDENT TO CLIENT (TASK 1)
void server_TASK1_info(socket_t * client, http_request_t * req, student_t * self) {
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

// GET FOR THE POST REQUEST (TASK 4)
void server_TASK4_newFile(socket_t * client, http_request_t * req) {
	char strBuf[10240];
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		char line[1000];
		strcpy(line, "<html><head>Input your text here</head><body><form action=\"http://127.0.0.1:5000/data\" method=\"POST\">"
			"Your text:<br><textarea rows=\"10\" cols=\"100\" name=\"thyText\">ok</textarea><br>"
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

// GET/POST FOR DATA
void server_TASK4_data(socket_t * client, http_request_t * req) {
	char strBuf[10240];
	// =====POST=====
	if (strcmp(req->method, "POST") == 0) {
		// All the info:
		char * str = http_request_getArg(req, "thyText");

		const char * directory = "C:\\Users\\Student\\Documents\\Different\\ProgBase\\Term_2\\zCW_2\\CW_2\\CW_2\\testFile";
		int check = dir_exists(directory);
		if (dir_exists == 0) {
			server_invalidResponce(client, "No such directory");
			return;
		}

		FILE * fwPtr = fopen("testFile\\data.txt", "w");
		if (fwPtr == NULL) {
			return;
		}
		fprintf(fwPtr, "%s\n", str);
		fclose(fwPtr);

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

// ANALYSE REQUEST
void server_analyzeRequest(http_request_t * request, socket_t * client, student_t * student) {

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
	// DEFAULT
	// default invalid path
	else {
		server_invalidResponce(client, "Invalid path."); // socket_close() function inside
	}

}