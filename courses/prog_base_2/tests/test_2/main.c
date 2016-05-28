#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "list/list.h"
#include "SQLite/sqlite3.h"
#include "FSHelper/FSHelper.h"

#include "allTasks.h"

//INIT SOCKET
static socket_t * winSock;

int main(void) {
	// INIT STUDENT
	student_t * student = student_new();
	student_fill(student, "Sergey Romanyuk", "KP-51", 2);
	// OTHER
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
		server_analyzeRequest(&request, client, student);

		socket_free(client);
	}

	// end of program
	socket_close(winSock);
	socket_free(winSock);
	lib_free();
	student_free(student);

	// End of program
	printf("\n\nPress ANY KEY to exit the program...");
	getch();
	return 0;
}