#include "grep_inverse.h"

#include "grep_template.h"
#include "source.h"

int inverse_grep(char *pattern, char *filename, char most_arg_flag) {
    int error = 0;
    if (filename == NULL) {
        error = grep_from_input(pattern, 1, 0, 0);
    } else if (most_arg_flag) {
        error = grep_from_file(pattern, filename, 1, 0, 0, 0, 0);
    } else {
        error = grep_from_file(pattern, filename, 1, 0, 0, 0, -1);
    }
    return error;
}