/* cJSON.c/cJSON.h ARE PROVIDED BY Dave Gamble (DaveGamble repo) AND ARE TAKEN *AS IS*!
I DO NOT OWN ANY OF THIS, ALL RIGHTS BELONG TO THE OWNER! */

/* sqlite3.c/sqlite3.h ARE PROVIDED BY 'SQLite' AND ARE TAKEN *AS IS*!
I DO NOT OWN ANY OF THIS, ALL RIGHTS BELONG TO THE OWNERS! */

/* main.c represents the main cycle of our program;
Things like initialization of the database / port opening / socket binding
are situated here.
The main function of the program - server_analyzeRequest() - is also called here
(but the full description (body) of it can be found in server.c file) */

#include <stdio.h>
#include <stdlib.h>

#include "server.h"

//INIT SOCKET
static socket_t * winSock;

int main(void) {
	// Initializing database
	database_t * database = database_new("investors.db");

	int PORT = 5000;
	lib_init();
	winSock = socket_new();

	// Checking if socket is not busy, closing app if it is
	if (socket_bind(winSock, PORT) == SOCKET_ERR) {
		printf("Cannot bind %i port\n", PORT);
		socket_close(winSock);
		socket_free(winSock);
		return 0;
	}

	socket_listen(winSock);
	char buf[10000];
	socket_t * client = NULL;
	// main cycle of the program
	while (1) {
		printf("Awaiting for connections...\n");
		client = socket_accept(winSock);

		// Checking if client is not null, closing app if he is
		if (client == NULL) {
			printf("NULL client, closing app...\n");
			break;
		}

		int readStatus = socket_read(client, buf, sizeof(buf));

		// Skipping empty request (may appear from time to time)
		if (readStatus <= 0) {
			printf("Empty request, skipping...\n");
			socket_close(client);
			socket_free(client);
			continue;
		}

		// Printing info about the received request to console
		printf(">> Got request (readStatus: %i):\n'%s'\n", readStatus, buf);
		http_request_t request = http_request_parse(buf);

		// check the type/path of request (API/HTML) & analyze the method (GET/POST/DELETE)
		// and provide the client with proper answer
		server_analyzeRequest(&request, client, database);

		socket_free(client);
	}

	// end of program
	socket_close(winSock);
	socket_free(winSock);
	database_free(database);
	lib_free();
	return 0;
}