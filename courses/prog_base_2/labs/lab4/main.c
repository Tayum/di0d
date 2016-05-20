/* cJSON.c/cJSON.h ARE PROVIDED BY Dave Gamble (DaveGamble repo) AND ARE TAKEN *AS IS*!
I DO NOT OWN ANY OF THIS, ALL RIGHTS BELONG TO THE OWNER! */

/* main.c represents the main cycle of our program;
Things like initialization of the primary data / port opening / socket binding
are situated here */

#include <stdio.h>
#include <stdlib.h>

#include "server.h"

//INIT SOCKET
static socket_t * winSock;

int main(void) {
	// initializing first three investors for program to start with
	invArr_t * investorArray = invArr_new();
	investor_t * investors[3];
	for (int i = 0; i < sizeof(investors) / sizeof(investors[0]); i++) {
		investors[i] = investor_new();
	}
	investor_fill(investors[0], 0, "Garrosh", "Warrior", "Hellscream", 8.9, 1970, 25, 9, 46, 10000000, "ArmorUp");
	investor_fill(investors[1], 1, "Anduin", "Priest", "Wrynn", 5.6, 1995, 15, 3, 21, 1000000, "LesserHeal");
	investor_fill(investors[2], 2, "Rexxar", "Hunter", "Face", 8.1, 1985, 20, 1, 31, 5000000, "SteadyShot");
	for (int i = 0; i < sizeof(investors) / sizeof(investors[0]); i++) {
		invArr_addInv(investorArray, investors[i]);
	}
	// initializing_END

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
		server_analyzeRequest(&request, client, investorArray);

		socket_free(client);
	}

	// end of program
	socket_close(winSock);
	socket_free(winSock);
	for (int i = 0; i < sizeof(investors) / sizeof(investors[0]); i++) {
		investor_free(investors[i]);
	}
	invArr_free(investorArray);
	lib_free();
	return 0;
}