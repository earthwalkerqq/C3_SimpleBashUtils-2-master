#include "grep_num.h"

#include "grep_template.h"

int grep_with_line_nun(char *pattern, char *filename, char most_arg_flag) {
    int error = EXIT_SUCCESS;
    if (filename == NULL) {
        error = grep_from_input(pattern, 0, 1, 0);
    } else if (most_arg_flag) {
        error = grep_from_file(pattern, filename, 0, 0, 1, 0, 0);
    } else {
        error = grep_from_file(pattern, filename, 0, 0, 1, 0, -1);
    }
    return error;
}