#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "server.h"
#include "FSHelper/FSHelper.h"


void server_analyzeRequest(http_request_t * request, socket_t * client) {

	if (strcat(request->uri, "/") != NULL) {
		server_getFile(client, request); // socket_close() function inside
	}

	else {
		socket_write_string(client, "Invalid URI.");
		socket_close(client);
	}

}


void server_getFile(socket_t * client, http_request_t * req) {
	// =====GET=====
	if (strcmp(req->method, "GET") == 0) {
		char * line = req->uri;
		char * token = strtok(line, "/");
		// Name of file to read the info from
		char * fileReadName = calloc(1000, sizeof(char));
		sprintf(fileReadName,
			"files\\%s", token);
		// Whether file exists
		int rc = file_exists(fileReadName);
		if (rc == 0) {
			socket_write_string(client, "Invalid file name.");
			socket_close(client);
			free(fileReadName);
			return;
		}
		else if (rc == 1) {
			// File exists:
			FILE * fileRPtr;
			fileRPtr = fopen(fileReadName, "rb");
			if (fileRPtr == NULL) {
				socket_write_string(client, "The file cannot be opened for reading.");
				socket_close(client);
				fclose(fileRPtr);
				free(fileReadName);
				return;
			}
			char buff[1024];
			// While the end of file is not reached, read (maximum of) 1024 bytes at one time
			// and pass them to client's socket 'proportionally'
			while (!feof(fileRPtr)) {
				int bytes = fread(buff, sizeof(char), sizeof(buff), fileRPtr);
				socket_write(client, buff, bytes);
			}
			fclose(fileRPtr);

			socket_close(client);
			free(fileReadName);
		}
	}
	// =====Invalid command=====
	else {
		socket_write_string(client, "Invalid command.");
		socket_close(client);
	}
}