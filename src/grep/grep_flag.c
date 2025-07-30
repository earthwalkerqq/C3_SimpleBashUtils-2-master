#include "grep_flag.h"

int processing(int argc, char *argv[]) {
    int error = EXIT_SUCCESS;
    int (*func)(char *, char *);
    if (argc == 2)
        error = grep_from_input(argv[1], 0, 0, 0);
    else if (argc == 3 && *(argv[1]) == '-') {
        func = processing_option(argv[1][1]);
        if (func == NULL) {
            perror("UNCORRECT OPTION");
            error = EXIT_FAILURE;
        } else
            error = func(argv[2], NULL);
    } else if (argc == 3)
        error = grep_from_file(argv[1], argv[2], 0, 0, 0, 0);
    else if (argc == 4 && *(argv[1]) == '-') {
        func = processing_option(argv[1][1]);
        if (func == NULL) {
            perror("UNCORRECT OPTION");
            error = EXIT_FAILURE;
        } else
            error = func(argv[2], argv[3]);
    } else {
        perror("MOST OR LESS ARGUMENT GIVEN");
        error = EXIT_FAILURE;
    }
    return error;
}

int (*processing_option(char option))(char *, char *) {
    int (*res_func)(char *, char *) = NULL;
    switch (option) {
        case 'e':
            res_func = grep_with_template;
            break;
        case 'i':
            res_func = grep_ignore_registre;
            break;
        case 'v':
            res_func = inverse_grep;
            break;
        case 'c':
            res_func = grep_count_line;
            break;
        case 'n':
            res_func = grep_with_line_nun;
            break;
        case 's':
            res_func = grep_without_error;
            break;
        case 'f':
            res_func = grep_with_file_pattern;
            break;
        case 'o':
            res_func = match_string;
            break;
    }
    return res_func;
}