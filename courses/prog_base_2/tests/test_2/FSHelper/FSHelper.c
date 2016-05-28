#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

#include "FSHelper.h"


int dir_exists(const char * dirname) {
	struct stat buffer;
	return (stat(dirname, &buffer) == 0) && S_ISDIR(buffer.st_mode);
}


int dir_printFiles(const char * dirname) {
	DIR *dp;
	struct dirent *ep;
	int file_count = 0;
	dp = opendir(dirname);
	if (dp != NULL) {
		while ((ep = readdir(dp))) {
			if (32 == dp->wdirp->data.dwFileAttributes) { // dp->dd_dta.attrib
				puts(dp->ent.d_name); // dp->dd_dir.d_name
				file_count++;
			}
		}
		(void)closedir(dp);
		return file_count;
	}
	else {
		return -1;
	}
}


int file_exists(const char * filename)
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

long long file_getSize(const char * filename) {
	struct stat st;
	if (0 != stat(filename, &st)) {
		return -1;
	}
	long long size = st.st_size;
	return size;
}


time_t file_getCreateTime(const char * filename) {
	struct stat st;
	if (0 != stat(filename, &st)) {
		return (time_t)0;
	}
	return st.st_ctime;
}


int file_create(const char * filename) {
	FILE * fp;
	int success = NULL != (fp = fopen(filename, "ab+"));
	if (!success) {
		return 0;
	}
	fclose(fp);
	return 1;
}


int file_remove(const char * filename) {
	return 0 == remove(filename);
}