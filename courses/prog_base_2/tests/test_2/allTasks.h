#ifndef ALLTASKS_H_INCLUDED
#define ALLTASKS_H_INCLUDED

#include "http/http.h"
#include "libsocket/socket.h"
#include "student.h"

void server_analyzeRequest(http_request_t * request, socket_t * client, student_t * student);

#endif // ALLTASKS_H_INCLUDED