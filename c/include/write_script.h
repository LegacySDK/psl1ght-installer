#pragma once
#include <stdio.h>
#include <string.h>

#ifdef linux
    #include <unistd.h>
    #include <sys/stat.h>
#endif

int write_script(const char *install_location);
