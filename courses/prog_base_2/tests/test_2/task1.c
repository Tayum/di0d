#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "task1.h"
#include "cJSON/cJSON.h"

// ====================TASK 1: STUDENT====================
struct student_s {
	char * student;
	char * group;
	int variant;
};

student_t * student_new(void) {
	student_t * studentSmp = malloc(sizeof(struct student_s));
	studentSmp->student = "NoNameSurname";
	studentSmp->group = "No group";
	studentSmp->variant = 0;
}

void student_free(student_t * self) {
	free(self);
}

void student_fill(student_t * self, char * iden, char * group, int variant) {
	self->student = iden;
	self->group = group;
	self->variant = variant;
}

// ====================TASK 1: cJSON====================

// Constructing a CJSON form from the single investor-struct
// The function is static as far as it is not used in other files.
static cJSON * investor_serializeJSON(const student_t * self) {
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
	cJSON * invJSON = investor_serializeJSON(self);
	char * buffJSON = cJSON_Print(invJSON);
	cJSON_Delete(invJSON);
	return buffJSON;
}


// ====================TASK 1: STUDENT: OTHER====================

// INVALID
void server_invalidResponce(socket_t * client, char * message) {
	char strBuf[1024];
	char * errText = message;

	sprintf(strBuf,
		"HTTP/1.1 404 \n"
		"Content-Type: text/html\n"//application/json
		"Content-Length: %zu\n"
		"\n%s", strlen(errText) + 1, errText);

	socket_write_string(client, strBuf);
	socket_close(client);
}

// INFO ABOUT STUDENT TO CLIENT
void server_API_info(socket_t * client, http_request_t * req, student_t * self) {
	char strBuf[10240];
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		char * studentJSON = student_parseToJSON(self);
		sprintf(strBuf,
			"HTTP/1.1 200 OK\n"
			"Content-Type: application/json\n"
			"Content-Length: %zu\n"
			"Connection: keep-alive\n"
			"\n%s", strlen(studentJSON) + 1, studentJSON);
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

// ANALYSE REQUEST
void server_analyzeRequest(http_request_t * request, socket_t * client, student_t * student) {

	// API: myInfo
	if (strcmp(request->uri, "/info") == 0 || strcmp(request->uri, "/info/") == 0) {
		server_API_info(client, request, student); // socket_close() function inside
	}

	// API: default
	// default invalid path
	else {
		server_invalidResponce(client, "Invalid path."); // socket_close() function inside
	}

}