#include <dir_stuff.h>

#ifdef linux
int make_dir(const char *dir_name) {
    struct stat st = {0};

    if(stat(dir_name, &st) == -1) {
        mkdir(dir_name, 0700);
    }
    
    return 0;
}

char *get_working_dir(char *buf, size_t size) {
    return getcwd(buf, size);
}

bool directory_exists(const char *dirname) {
    struct stat s;
    int stat_result = stat(dirname, &s);
    bool exists = true;
    if(stat_result == -1) {
        if(errno = ENOENT) exists = false;
        else {
            printf("stat error\n");
            return true; // just to be safe
        }
    }

    return exists;
}
#endif
