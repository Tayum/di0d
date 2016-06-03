#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include <conio.h>

#include "client.h"

int main(void) {
	// INIT SOCKET
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    char * ip = "127.0.0.1";
	char * pathToSaveFile = "recvFiles\\";
	char * fileName = "Lab5_ProgBase.rar";

    // INIT WinSock DLL
    initializeWindowsSocketDLL(Data);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr)); // 'Zero' the sock_addr struct
	recvSockAddr.sin_port = htons(5000); // port
	recvSockAddr.sin_family = AF_INET; // address family: Web
	recvSockAddr.sin_addr.s_addr = inet_addr(ip); // IP address

	// Create socket
	recvSocket = createSocket();
    // Connect to the server
    connect_selfFunc(recvSocket, recvSockAddr);
    // Send request
    sendRequest(ip, fileName, recvSocket);
	// Receive info into the socket (and then into the file)
	receive(pathToSaveFile, fileName, recvSocket);

	// 'Cleaning' sockets
	closesocket(recvSocket);
	WSACleanup();
	// End of program
	puts("\n\nPress ANY KEY to exit the program...");
	getch();
    return 0;
}