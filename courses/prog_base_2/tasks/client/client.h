#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#define NO_FLAGS_SET 0	// for recieve func
#define PORT 80	// standart port
#define MAXBUFLEN 20480 //maxBuff length

#pragma comment(lib,"ws2_32.lib") //Winsock Library

int initializeWindowsSocketDLL(WSADATA Data);
SOCKET createSocket();
void connecting(SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
void sendRequest(const char * host_name, SOCKET recvSocket);
void recieve(SOCKET recvSocket, char * maxBuff);
void getBySecret(char * maxBuff, char * host_name, SOCKET recvSocket);
int avgValue(char * maxBuff);
void sendPost(SOCKET recvSocket, char * host_name, int avg);

#endif // CLIENT_H_INCLUDED