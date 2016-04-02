#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <windows.h>
#include <conio.h>

#include "client.h"

int main(void) {
	//BASIC VARS
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    int numrcv = 0;
    struct hostent * remoteHost;
    char * ip;
    const char * host_name = "pb-homework.appspot.com";
    char maxBuff[MAXBUFLEN];
    memset(maxBuff,0,MAXBUFLEN);
	//MOD VAR
	int avg = 0;

    // BASIC: Initialize Windows Socket DLL
    status = initializeWindowsSocketDLL(Data);

	// BASIC: Get IP address from host name
	remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("\n==========\nIP address is: %s\n==========\n", ip);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr)); // zero the sockaddr_in structure
    recvSockAddr.sin_port=htons(PORT);              // specify the port portion of the address
    recvSockAddr.sin_family=AF_INET;                // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr= inet_addr(ip);    // specify ip address

	// BASIC: Create socket
	recvSocket = createSocket();

    // BASIC: Connecting
    connecting(recvSocket, recvSockAddr);

    // BASIC: Sending request
    sendRequest(host_name, recvSocket);

	// BASIC: receiving info and secret
	recieve(recvSocket, maxBuff);
	// MOD: GET by secret
    getBySecret(maxBuff, host_name, recvSocket);
	// BASIC: receiving info + secret info
    recieve(recvSocket, maxBuff);
	// Buff with all needed info
	puts("==========\nWE GOT THIS INFO:");
	printf("\n%s\n==========\n", maxBuff);

	//MOD: Finding avg
	avg = avgValue(maxBuff);
	printf("\n=====\nAverage value: %i\n=====\n\n", avg);
	//MOD: GET by post
    sendPost(recvSocket, host_name, avg);

	// BASIC: receiving result info
    recieve(recvSocket, maxBuff);
	// Buff with a result info
	puts("==========\nTHIS IS THE RESULT:");
	printf("\n%s\n==========\n", maxBuff);

	// closing the sockets and etc.
	closesocket(recvSocket);
	WSACleanup();

	//end of program
	puts("\nPress ANY KEY to exit the program...");
	getch();
    return 0;
}