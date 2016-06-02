/* Investor array struct with opened body.
This file is needed for proper incapsulation of data. */

#ifndef INVARRSTRUCT_H_INCLUDED
#define INVARRSTRUCT_H_INCLUDED

#include "list/list.h"

struct invArr_s {
	list_t * investors;
};

#endif // INVARRSTRUCT_H_INCLUDED
