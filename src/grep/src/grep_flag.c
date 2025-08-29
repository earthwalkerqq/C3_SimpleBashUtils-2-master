#include "grep_flag.h"

#include <stdio.h>

#include "grep_count.h"
#include "grep_file.h"
#include "grep_hide.h"
#include "grep_ignore.h"
#include "grep_inverse.h"
#include "grep_match.h"
#include "grep_num.h"
#include "grep_template.h"
#include "grep_without_error.h"

int processing(int argc, char *argv[]) {
    int error = 0;
    int (*func)(char *, char *, char);
    if (argc == 2)
        error = grep_from_input(argv[1], 0, 0, 0);
    else if (argc == 3 && *(argv[1]) == '-') {
        func = processing_option(argv[1][1]);
        if (func == NULL) {
            perror("UNCORRECT OPTION");
            error = 1;
        } else
            error = func(argv[2], NULL, 0);
    } else if (argc == 3)
        error = grep_from_file(argv[1], argv[2], 0, 0, 0, 0, 0);
    else if (argc == 4 && *(argv[1]) == '-') {
        func = processing_option(argv[1][1]);
        if (func == NULL) {
            perror("UNCORRECT OPTION");
            error = 1;
        } else
            error = func(argv[2], argv[3], 0);
    } else if (*(argv[1]) == '-') {
        func = processing_option(argv[1][1]);
        if (func == NULL) {
            perror("UNCORRECT OPTION");
            error = 1;
        } else {
            for (int i = 3; i < argc && !error; i++) {
                error = func(argv[2], argv[i], 1);
            }
        }
    } else {
        for (int i = 2; i < argc && !error; i++) {
            error = grep_from_file(argv[1], argv[i], 0, 0, 0, 0, 0);
        }
    }
    return error;
}

int (*processing_option(char option))(char *, char *, char) {
    int (*res_func)(char *, char *, char) = NULL;
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
        case 'h':
            res_func = grep_hide_filename;
            break;
    }
    return res_func;
}