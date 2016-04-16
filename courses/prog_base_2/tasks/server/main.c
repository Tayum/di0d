/* NEXT FILES OF PROJECT:
* cJSON.h - TOOK FROM DAVE GAMBLE REPO
* cJSON.c - TOOK FROM DAVE GAMBLE REPO
* http.h - TOOK FROM PublicHadyniak RERO
* http.c - TOOK FROM PublicHadyniak RERO
* socket.h - TOOK FROM PublicHadyniak RERO
* socket.c - TOOK FROM PublicHadyniak RERO
ARE TOOK AS IS AND WERE NOT MODIFIED!

NEXT FILES OF PROJECT:
* investor.h - MADE USING ANALOGUE FROM PublicHadyniak RERO (student.h)
* investor.c - MADE USING ANALOGUE FROM PublicHadyniak RERO (student.c)
* server.h - MADE USING ANALOGUE FROM PublicHadyniak RERO (main.c)
* server.c - MADE USING ANALOGUE FROM PublicHadyniak RERO (main.c)
* main.c - MADE USING ANALOGUE FROM PublicHadyniak RERO (main.c)
* input.html - MADE USING ANALOGUE FROM PublicHadyniak RERO (POST.html)
WERE MODIFIED BY AUTHOR!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "server.h"

//INIT SOCKET
static socket_t * winSock;

int main(void) {
	int PORT = 5000;
	lib_init();
	winSock = socket_new();
	//CHECKING IF SOCKET IS FREE, CLOSING APP IF NOT
	if (socket_bind(winSock, PORT) == SOCKET_ERR) {
		printf("Cannot bind %i port\n", PORT);
		socket_close(winSock);
		socket_free(winSock);
		return 0;
	}

	socket_listen(winSock);
	char buf[10000];
	socket_t * client = NULL;
	while (1) {
		printf("Awaiting for connections...\n");
		client = socket_accept(winSock);
		//CHECKING IF CLIENT IS NOT NULL, CLOSING APP IF HE IS
		if (client == NULL) {
			printf("NULL client, closing app...\n");
			break;
		}
		int readStatus = socket_read(client, buf, sizeof(buf));
		//SKIPPING EMPTY REQUEST (IT MAY APPEAR FROM TIME TO TIME)
		if (readStatus <= 0) {
			printf("Empty request, skipping...\n");
			socket_close(client);
			socket_free(client);
			continue;
		}
		//PRINTF'ING TO CONSOLE INFO ABOUT REQUEST
		printf(">> Got request (readStatus: %i):\n'%s'\n", readStatus, buf);

		http_request_t request = http_request_parse(buf);

		//ELSE-IF CONDITION LADDER TO CHECK THE PATH
		if (strcmp(request.uri, "/") == 0) {
			server_homepage(client); //socket_close inside
		}
		else if (strcmp(request.uri, "/investors") == 0 || strcmp(request.uri, "/investors/") == 0) {
			server_allInvestors(client, &request); //socket_close inside
		}
		//CONDITION WITH AN INDEX OF THE STUDENT
		else if (strstr(request.uri, "/investors/") != NULL) {
			//CHECKING IF INDEX IS PROPER (LAYS BETWEEN 0-9)
			char * string = strstr(request.uri, "/investors/");
			char * token = strtok(request.uri, "/");
			token = strtok(NULL, "/");
			if (token != NULL && strlen(token) == 1 && isdigit(token[0]) != 0) {
				//CHECKING IF INDEX IS PROPER (LAYS WITHIN THE AMOUNT OF INVESTORS IN OUR STRUCT (3) )
				int index = atoi(token);
				int amount = invArray_getSize();
				if (index < amount && index >= 0) {
					for (int i = 0; i < amount; i++) {
						if (index == i) {
							server_investorById(client, &request, index); //socket_close inside
							break;
						}
					}
				}
				//INDEX IS NOT LAYING WITHIN AMOUNT OF INVESTORS
				else {
					server_invPath(client); //socket_close inside
				}
			}
			//INDEX IS NOT LAYING BETWEEN 0-9
			else {
				server_invPath(client); //socket_close inside
			}
		}
		//INVALID PATH
		else {
			server_invPath(client); //socket_close inside
		}
		socket_free(client);
	}
	//END OF PROGRAM
	socket_close(winSock);
	socket_free(winSock);
	lib_free();
	return 0;
}