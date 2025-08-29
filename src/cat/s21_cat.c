#include <stdlib.h>

#include "output_file.h"

int output_file(FILE *file, const char *option);

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        perror("MORE OR LESS ARGUMENTS");
        return EXIT_FAILURE;
    }
    FILE *file = NULL;
    if ((file = (argc == 3) ? fopen(argv[2], "r") : fopen(argv[1], "r")) == NULL) {
        perror("CAN'T OPEN FILE");
        return EXIT_FAILURE;
    }
    int error;
    error = (argc == 3) ? output_file(file, argv[1]) : output_file(file, NULL);
    if (error) {
        perror("FAIL FROM OPTION");
        return EXIT_FAILURE;
    }
    fclose(file);
    return EXIT_SUCCESS;
}