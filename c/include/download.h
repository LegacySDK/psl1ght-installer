#pragma once

#include <stdio.h>
#include <string.h>
#include <curl-8.21.0/include/curl/curl.h>

#ifdef linux
    #include <unistd.h>
#endif

int download_ps3dev(const char *filename, const char *url);
