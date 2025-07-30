#include "grep_match.h"

#include "grep_template.h"

int match_string(char *pattern, char *filename) {
    int error = EXIT_SUCCESS;
    error = (filename == NULL) ? grep_from_input(pattern, 0, 0, 1)
                               : grep_from_file(pattern, filename, 0, 0, 0, 1);
    return error;
}