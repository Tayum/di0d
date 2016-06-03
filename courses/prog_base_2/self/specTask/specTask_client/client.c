#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include <string.h>

#include "client.h"

void initializeWindowsSocketDLL(WSADATA Data) {
    int status = WSAStartup(MAKEWORD(2, 2), &Data);
	if (status != 0) {
		printf("WSAStartup unsuccessful\n");
	}
}

SOCKET createSocket(void) {
    SOCKET recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (recvSocket == INVALID_SOCKET) {
		printf("Socket creation unsuccessful\n");
		WSACleanup();
		system("pause");
		return 0;
	}
	return recvSocket;
}

// Connect to server socket
void connect_selfFunc(SOCKET recvSocket, SOCKADDR_IN recvSockAddr) {
	if (connect(recvSocket, (SOCKADDR *)&recvSockAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
		printf("Socket could not connect\n");
		closesocket(recvSocket);
		WSACleanup();
		return 0;
	}
}

// Send the request with the name of the file
void sendRequest(const char * IP, const char * fileName, SOCKET recvSocket) {
    char request[200];
    sprintf(request, "GET /%s HTTP/1.1\r\nIP:%s\r\n\r\n", fileName, IP);
    send(recvSocket, request, strlen(request), 0);
}

// Receive the data into the socket and transport it to file
void receive(const char * filePath, const char * fileName, SOCKET recvSocket) {
	int bytes;
	FILE * fWritePtr;
	char buff[1024];
	char * path = calloc(1000, sizeof(char));
	sprintf(path,
		"%s%s", filePath, fileName);
	fWritePtr = fopen(path, "wb");
	if (fWritePtr == NULL) {
		puts("The file cannot be opened for writing. Probably, invalid path.");
		return;
	}
	else {
		do {

			bytes = recv(recvSocket, buff, 1024, 0);
			// To handle the invalid behaviour
			if (bytes >= 0 && bytes < 1024) {
				buff[bytes] = '\0';
			}
			// If the error has occured - close the file stream and delete the created file.
			if (strcmp(buff, "Invalid URI.") == 0 ||
				strcmp(buff, "The file cannot be opened for reading.") == 0 ||
				strcmp(buff, "Invalid file name.") == 0 ||
				strcmp(buff, "Invalid command.") == 0) {

				fclose(fWritePtr);
				if (remove(fileName) != 0) {
					puts("Error removing file.");
				}
				else {
					puts("Something is wrong with the request! Probably, invalid name of file.");
				}
			}
			// Another kind of error
			else {
				if (bytes == SOCKET_ERROR) {
					puts("Recvfrom unsuccessful");
					int rc = closesocket(recvSocket);
					if (rc == SOCKET_ERROR) {
						puts("Close socket unsuccessful");
					}
					rc = WSACleanup();
					if (rc == SOCKET_ERROR) {
						puts("WSACleanup unsuccessful");
					}
					fclose(fWritePtr);
					system("pause");
				}
				else {
					fwrite(buff, sizeof(char), bytes, fWritePtr);
				}
			}

		} while (bytes == 1024);
	}

	fclose(fWritePtr);
}