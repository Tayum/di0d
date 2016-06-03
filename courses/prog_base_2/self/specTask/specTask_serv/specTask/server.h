#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "libsocket/socket.h"
#include "http/http.h"

void server_analyzeRequest(http_request_t * request, socket_t * client);

void server_getFile(socket_t * client, http_request_t * req);

#endif //SERVER_H_INCLUDED