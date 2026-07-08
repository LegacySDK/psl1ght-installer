#include <write_script.h>

// the linux build should write a .sh script,
// the windows build a .bat script

#ifdef linux
int write_script(const char *install_location) {
    char script_name[512] = {0};
    sprintf(script_name, "%s/enter_env.sh", install_location);

    // check if the script already exists
    if(access(script_name, F_OK) == 0) {
        printf("script %s already exists, skipping script creation\n", script_name);
        return 0;
    }

    printf("writing script \"%s\"\n", script_name);
    // never big enough
    char buffer[4096] = {0};

    sprintf(buffer, "#!/bin/bash\nexport PS3DEV=\"%s/ps3dev/\"\n"
                    "export PSL1GHT=\"%s/psl1ght_install\"\n"
                    "export PATH=\"$PS3DEV/ppu/bin:$PS3DEV/spu/bin:$PATH\"\n"
                    "echo -e \"\\033[0;32mAll environment variables set!\\033[0m\"\n"
                    "bash",
                    install_location, install_location);

    FILE *file;
    file = fopen(script_name, "wb");
    if(!file) {
        printf("couldn't open script file for writing\n");
        return 1;
    }
    fwrite(buffer, strlen(buffer), 1, file);

    fclose(file);

    // mark as executable
    if(chmod(script_name, 0755) == -1) {
        printf("couldn't set script as executable");
        return 1;
    }

    return 0;
}
#endif
