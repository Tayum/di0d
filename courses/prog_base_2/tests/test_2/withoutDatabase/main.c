/*  ALERT 1: DON'T FORGET TO INCLUDE sqlite3.h AND sqlite3.c FILES! THEY ARE NOT INCLUDED ON GITHUB
	ALERT 2: DON'T FORGET TO MODIFY/CHECK THE PATH:
	*	The function, that is working with path is situated in: server.c file, __func__ : server_TASK4_data

	ALERT 3: THIS IS THE OLD PROJECT
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "list/list.h" // NO NEED
#include "SQLite/sqlite3.h"

#include "server.h"

//INIT SOCKET
static socket_t * winSock;

int main(void) {
	// Init student
	student_t * student = student_new();
	student_fill(student, "Sergey Romanyuk", "KP-51", 2);
	// Other (init server)
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

	// Main cycle of the program
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

		// check the type/path of request & analyze the method (GET/POST)
		// and provide the client with proper answer
		server_analyzeRequest(&request, client, student);

		socket_free(client);
	}

	// Free
	socket_close(winSock);
	socket_free(winSock);
	lib_free();
	student_free(student);

	// End of program
	printf("\n\nPress ANY KEY to exit the program...");
	getch();
	return 0;
}