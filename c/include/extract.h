#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <dir_stuff.h>

// isn't this linux/unix only? might want to
// have something else for windows
#ifdef linux
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <errno.h>
#endif

#ifdef _WIN32
    #error "windows not (yet) supported! just install arch lol"
#endif

int extract_file(const char *filename, const char *dest);
