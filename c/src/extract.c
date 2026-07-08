#include <extract.h>

// TODO: use a proper library, for now this will do
int extract_file(const char *filename, const char *dest) {
    if(directory_exists(dest)) {
        printf("%s already extracted into %s, skipping\n", filename, dest);
        return 0;
    }

    printf("extracting \"%s\" into \"%s\"\n", filename, dest);

    // if you think that's too big then fuck you, the stack is
    // big enough
    char command[1024] = {0};
    sprintf(command, "unzip %s -d %s > /dev/null", filename, dest);
    return system(command);
}
