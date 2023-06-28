#include <stdlib.h>
#include <stdio.h>
#include "ceml_parse.h"


int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *path_to_eml = argv[1];
    FILE* eml_file = fopen(path_to_eml, "r+");
    if (!eml_file) {
        puts("file doesn't opened");
        return 1;
    }
    ceml_parse(eml_file);
    fclose(eml_file);
    return 0;
}
