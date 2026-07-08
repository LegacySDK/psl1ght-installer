// made by miskaa and hlelo :3
// have fun suffering while reading whatever this is
#include <stdio.h>
#include <stdlib.h>
#include <download.h>
#include <extract.h>
#include <write_script.h>
#include <configure_psl1ght.h>
#include <string.h>
#include <dir_stuff.h>

#define PS3DEV_URL "https://hlelo.cc/files/ps3dev.zip"
#define DEFAULT_FILENAME "./ps3dev.zip"
#define DEFAULT_EXTRACT_DESTINATION "./legacysdk-ps3-kit" // also the install location i guess

char extract_destination[512] = DEFAULT_EXTRACT_DESTINATION;

void print_help() {
    printf("help menu\n  --help: show this menu\n  --location [LOCATION]: install the kit to LOCATION\n");
}

int main(int argc, char *argv[]) {
    // parse args
    int advancement = 1;
    while(advancement < argc) {
        if(strcmp(argv[advancement], "--help") == 0) {
            print_help();
            return 0;
        } else if(strcmp(argv[advancement], "--location") == 0) {
            advancement++;
            if(advancement >= argc) {
                printf("error: please provide a location!\n");
                print_help();
                return 1;
            }
            if(strlen(argv[advancement]) >= 512) {
                printf("location is too big!\n");
                return 1;
            }
            if(directory_exists(argv[advancement])) {
                printf("error: location \"%s\" already exists\n", argv[advancement]);
                return 1;
            }

            strcpy(extract_destination, argv[advancement]);
            advancement++;
        } else {
            printf("unrecognized command line argument: %s\n", argv[advancement]);
            return 1;
        }
    }


    const int download_result = download_ps3dev(DEFAULT_FILENAME, PS3DEV_URL);
    if(download_result != 0) {
        printf("an error occured while downloading ps3dev.zip!\n  - URL: %s\n", PS3DEV_URL);
        return download_result;
    }

    const int extract_result = extract_file(DEFAULT_FILENAME, extract_destination);
    if(extract_result != 0) {
        printf("an error occured while extracting ps3dev");
        return extract_result;
    }

    char install_real_path[512] = {0};
    if(realpath(extract_destination, install_real_path) == NULL) {
        printf("error while resolving install real path\n");
        return 1;
    }

    const int psl1ght_result = configure_psl1ght(install_real_path);
    if(psl1ght_result != 0) {
        printf("cloudn't configure psl1ght\n");
        return psl1ght_result;
    }

    const int script_result = write_script(install_real_path);
    if(script_result != 0) {
        printf("couldn't write script");
        return script_result;
    }

    printf("done! you can now start using the development kit by running %s/enter_env.sh\n", extract_destination);

    return 0;
}
