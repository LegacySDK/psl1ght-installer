#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <dir_stuff.h>

#ifdef linux
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

#define PSL1GHT_GIT_URL "https://github.com/ps3dev/PSL1GHT.git"

int configure_psl1ght(const char *location);
