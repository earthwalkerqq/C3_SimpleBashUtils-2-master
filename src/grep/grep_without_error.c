#include "grep_without_error.h"

#include "grep_template.h"

int grep_without_error(char *pattern, char *filename, char most_arg_flag) {
    if (filename == NULL) {
        grep_from_input(pattern, 0, 0, 0);
    } else if (most_arg_flag) {
        grep_from_file(pattern, filename, 0, 1, 0, 0, 0);
    } else {
        grep_from_file(pattern, filename, 0, 1, 0, 0, -1);
    }
    return EXIT_SUCCESS;
}