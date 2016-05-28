#ifndef TASK1_H_INCLUDED
#define TASK1_H_INCLUDED

#include "http/http.h"
#include "libsocket/socket.h"

typedef struct student_s student_t;

student_t * student_new(void);
void student_free(student_t * self);
void student_fill(student_t * self, char * iden, char * group, int variant);

void server_analyzeRequest(http_request_t * request, socket_t * client, student_t * student);

#endif // TASK1_H_INCLUDED