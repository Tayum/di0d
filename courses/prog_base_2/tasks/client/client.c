#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include <string.h>

#include "client.h"

//BASIC FUNC
int initializeWindowsSocketDLL(WSADATA Data) {
    int status;
    status = WSAStartup(MAKEWORD(2, 2), &Data);
	if (status != 0) {
		printf("ERROR: WSAStartup unsuccessful\r\n");
		return 0;
	}
    return status;
}

//BASIC FUNC
SOCKET createSocket() {
    SOCKET recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (recvSocket == INVALID_SOCKET) {
		printf("ERROR: socket unsuccessful\r\n");
		WSACleanup();
		system("pause");
		return 0;
	}
	return recvSocket;
}

//BASIC FUNC
void connecting(SOCKET recvSocket, SOCKADDR_IN recvSockAddr) {
	if (connect(recvSocket, (SOCKADDR*)&recvSockAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
		printf("ERROR: socket could not connect\r\n");
		closesocket(recvSocket);
		WSACleanup();
		return 0;
	}
}

//BASIC FUNC
void sendRequest (const char * host_name, SOCKET recvSocket) {
    char request[200];
    sprintf(request, "GET /var/15 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
    send(recvSocket, request, strlen(request), 0);
}

//BASIC FUNC
void recieve(SOCKET recvSocket, char * maxBuff) {
    int status;
    int numrcv;
    numrcv = recv(recvSocket, maxBuff, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR) {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
		if (status == SOCKET_ERROR) {
			printf("ERROR: closesocket unsuccessful\r\n");
		}
        status = WSACleanup();
		if (status == SOCKET_ERROR) {
			printf("ERROR: WSACleanup unsuccessful\r\n");
		}
        system("pause");
        return (1);
    }
}

void getBySecret(char * maxBuff, char * host_name, SOCKET recvSocket) {
	char request[200];
	char * secret;
	secret = strstr(maxBuff, "secret");
	sprintf(request, "GET /var/15?%s HTTP/1.1\r\nHost:%s\r\n\r\n", secret, host_name);
	send(recvSocket, request, strlen(request), 0);
}

int avgValue(char * maxBuff) {
	char * smallBuff;
	char * token;
	int matrixSum = 0;
	int counter = 0;
	int avg;
	smallBuff = strstr(maxBuff, "Content-Length:");
	token = strtok(smallBuff, "\n");
	token = strtok(NULL, "\n");
	token = strtok(NULL, "\n");
	token = strtok(token, " ");
	while (token != NULL) {
		matrixSum += atoi(token);
		counter++;
		token = strtok(NULL, " ");
	}
	avg = (int)(matrixSum / counter);
	return avg;
}

void sendPost(SOCKET recvSocket, char * host_name, int avg) {
	char result[30];
	char request[200];
	sprintf(result, "result=%i", avg);
	sprintf(request, "POST /var/15 HTTP/1.1\r\nHost: %s\r\nContent-length: %d\r\n\r\n%s\r\n", host_name, strlen(result), result);
	send(recvSocket, request, strlen(request), 0);
}