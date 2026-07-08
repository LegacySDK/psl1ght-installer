#pragma once
#include <stdio.h>

#ifdef linux
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <errno.h>
#endif

bool directory_exists(const char *dirname);
char *get_working_dir(char *buf, size_t size);
int make_dir(const char *dir_name);
