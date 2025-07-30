#include "grep_without_error.h"

#include "grep_template.h"

int grep_without_error(char *pattern, char *filename) {
    (filename == NULL) ? grep_from_input(pattern, 0, 0, 0) : grep_from_file(pattern, filename, 0, 1, 0, 0);
    return EXIT_SUCCESS;
}