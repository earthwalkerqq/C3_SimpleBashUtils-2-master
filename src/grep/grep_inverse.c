#include "grep_inverse.h"

#include "grep_template.h"

int inverse_grep(char *pattern, char *filename) {
    int error = EXIT_SUCCESS;
    error = (filename == NULL) ? grep_from_input(pattern, 1, 0) : grep_from_file(pattern, filename, 1, 0, 0);
    return error;
}