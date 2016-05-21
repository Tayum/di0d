#ifndef CHAT_H_INCLUDED
#define CHAT_H_INCLUDED

#include "list.h"
#include "user.h"

#define YES 1
#define NO 0

typedef struct chat_s chat_t;
typedef struct message_s message_t;

typedef void(*alert)(user_t * receiver, chat_t * chat);

// free() a line after usage!
char * chat_getName(const chat_t * self);

// free a list with list_free() after usage!
list_t * chat_getUserList(const chat_t * self)

#endif // CHAT_H_INCLUDED
