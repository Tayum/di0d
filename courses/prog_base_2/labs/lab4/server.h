/* server.h/server.c are analyzing the type of requests (GET/POST/DELETE),
the way the requests are sent (API (cJSON)/HTML)
and actually the path that requests are sent to. */

#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "libsocket/socket.h"
#include "http/http.h"
#include "investor.h"

void server_analyzeRequest(http_request_t * request, socket_t * client, invArr_t * investorArray);

void server_API_homepage(socket_t * client, char * message);
void server_API_allInvestors(invArr_t * self, socket_t * client, http_request_t * req);
void server_API_investorByID(invArr_t * self, socket_t * client, http_request_t * req, int ID);

void server_HTML_homepage(socket_t * client, char * message);
void server_HTML_allInvestors(invArr_t * self, socket_t * client, http_request_t * req);
void server_HTML_newInvestor(invArr_t * self, socket_t * client);
void server_HTML_investorByID(invArr_t * self, socket_t * client, http_request_t * req, int ID);

void server_invalidResponce(socket_t * client, char * message);

#endif //SERVER_H_INCLUDED