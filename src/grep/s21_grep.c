#include <stdio.h>
#include <stdlib.h>

#include "grep_flag.h"

#define er_message \
    "usage: grep [-A num] [-B num] [-C[num]]\n \
                [-e pattern] [-f file] [--binary-files=value] [--color=when]\n \
                [--context[=num]] [--directories=action] [--label] [--line-buffered]\n \
                [--null] [pattern] [file ...]\n"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        perror(er_message);
        return EXIT_FAILURE;
    }
    int error = processing(argc, argv);
    if (error) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}