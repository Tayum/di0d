#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#pragma comment(lib,"ws2_32.lib") // Windows socket library

void initializeWindowsSocketDLL(WSADATA Data);
SOCKET createSocket();
void connect_selfFunc(SOCKET recvSocket, SOCKADDR_IN recvSockAddr);
void sendRequest(const char * IP, const char * fileName, SOCKET recvSocket);
void receive(const char * filePath, const char * fileName, SOCKET recvSocket);

#endif // CLIENT_H_INCLUDED