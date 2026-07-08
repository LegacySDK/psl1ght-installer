#include <configure_psl1ght.h>

int configure_psl1ght(const char *location) {
    char psl1ght_install[512] = {0};
    char ps3dev_install[512] = {0};
    sprintf(psl1ght_install, "%s/psl1ght_install", location);
    sprintf(ps3dev_install, "%s/ps3dev", location);

    if(directory_exists(psl1ght_install)) {
        printf("PSL1GHT already installed, skipping\n");
        return 0;
    }

    // git clone
    printf("cloning psl1ght...\n");
    char command[512] = {0};
    sprintf(command, "git clone " PSL1GHT_GIT_URL " %s/psl1ght_git", location);
    system(command);

    // mkdir psl1ght_install
    if(make_dir(psl1ght_install) != 0) {
        printf("couldn't create psl1ght_install directory\n");
        return 1;
    }

    // set PSL1GHT and PS3DEV
    setenv("PSL1GHT", psl1ght_install, 1);
    setenv("PS3DEV", ps3dev_install, 1);

    // make, make, make...
    char prev_working_dir[512] = {0};
    if(get_working_dir(prev_working_dir, sizeof(prev_working_dir)) == NULL) {
        printf("couldn't get working dir\n");
        return 1;
    }

    sprintf(command, "%s/psl1ght_git", location); // might aswell reuse command
    chdir(command);
    printf("building psl1ght...\n");
    system("make install-ctrl > /dev/null");
    system("make > /dev/null");
    system("make install > /dev/null");
    chdir(prev_working_dir);

    return 0;
}
