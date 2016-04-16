#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "libsocket/socket.h"
#include "http.h"
#include "investor.h"

investor_t investorArray[];
int invArray_getSize(void);

void server_homepage(socket_t * client);
void server_allInvestors(socket_t * client, http_request_t * req);
void server_investorById(socket_t * client, http_request_t * req, int index);
void server_invPath(socket_t * client);

#endif //SERVER_H_INCLUDED