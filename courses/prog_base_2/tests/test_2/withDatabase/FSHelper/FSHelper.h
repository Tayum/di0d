#ifndef FSHELPER_H_INCLUDED
#define FSHELPER_H_INCLUDED

#include <time.h>

// @Returns: the existence of directory (1) or not (0)
int dir_exists(const char * dirname);

// Prints out list of files in directory
// @Returns: number of files OR -1 if the dirname is not found
int dir_printFiles(const char * dirname);

// @Returns: the existence of file (1) or not (0)
int file_exists(const char * filename);

// @Returns: size of file OR -1 if file is not found
long long file_getSize(const char * filename);

// @Returns: time of creation of file OR (time_t)0 if smth is wrong
time_t file_getCreateTime(const char * filename);

// @Returns: success of the action (1) or not (0)
int file_create(const char * filename);

// @Returns: success of the action (1) or not (0)
int file_remove(const char * filename);

#endif // FSHELPER_H_INCLUDED