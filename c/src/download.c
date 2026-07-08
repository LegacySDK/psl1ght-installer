#include <download.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

int download_ps3dev(const char *filename, const char *url) {
    // check if the file already exists
    if(access(filename, F_OK) == 0) {
        printf("%s already exists, skipping download\n", filename);
        return 0;
    }

    printf("downloading ps3dev.zip...\n");

    FILE *fp = fopen(filename, "wb");
    if(fp == NULL) {
        printf("cannot open %s for writing\n", filename);
        return 1;
    }

    // init curl
    CURL *curl = curl_easy_init();
    if(!curl) {
        printf("error while initializing curl\n");
        return 1;
    }

    // download ps3dev.zip
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    CURLcode result = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    fclose(fp);

    if(result != CURLE_OK) {
        printf("error while downloading ps3dev\n");
        return 1;
    }

    return 0;
}
