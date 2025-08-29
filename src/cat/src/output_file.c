#include "output_file.h"

#include <stdio.h>
#include <stdlib.h>

int output_file(FILE *file, const char *option) {
    int res = EXIT_SUCCESS;
    char ch;
    if (option == NULL)
        while ((ch = getc(file)) != EOF) {
            putc(ch, stdout);
        }
    else {
        if (option[0] != '-')
            res = EXIT_FAILURE;
        else {
            char flag = option[1];
            switch (flag) {
                case 'b':
                    output_nonblank(file);
                    break;
                case 'n':
                    output_number(file);
                    break;
                case 'e':
                    output_end_symbol(file);
                    break;
                case 's':
                    output_squeeze_blank(file);
                    break;
                case 't':
                    output_tab(file);
                    break;
                default:
                    res = EXIT_FAILURE;
            }
        }
    }
    return res;
}

void output_tab(FILE *file) {
    char ch;
    while ((ch = getc(file)) != EOF) {
        if (ch == '\t') {
            printf("^I");
        } else
            putc(ch, stdout);
    }
}

void output_squeeze_blank(FILE *file) {
    char ch;
    char empty_str = 0, first_ch = 1;
    while ((ch = getc(file)) != EOF) {
        if (first_ch && ch == '\n') {
            if (!empty_str++) putc(ch, stdout);
        } else if (first_ch && ch != '\n') {
            first_ch = 0;
            empty_str = 0;
            putc(ch, stdout);
        } else if (!first_ch && ch == '\n') {
            first_ch = 1;
            putc(ch, stdout);
        } else
            putc(ch, stdout);
    }
}

void output_end_symbol(FILE *file) {
    char ch;
    while ((ch = getc(file)) != EOF) {
        if (ch == '\n') {
            putc('$', stdout);
        }
        putc(ch, stdout);
    }
}

void output_number(FILE *file) {
    char ch;
    char first_ch = 1;
    int string_num = 1;
    while ((ch = getc(file)) != EOF) {
        if (first_ch && ch != '\n') {
            printf("%6d  %c", string_num++, ch);
            first_ch = 0;
        } else if (first_ch) {
            printf("%6d  %c", string_num++, ch);
        } else if (ch == '\n') {
            putc(ch, stdout);
            first_ch = 1;
        } else
            putc(ch, stdout);
    }
}

void output_nonblank(FILE *file) {
    char ch;
    char first_char = 1;
    int string_num = 1;
    while ((ch = getc(file)) != EOF) {
        if (first_char && ch != '\n') {
            printf("%6d  %c", string_num++, ch);
            first_char = 0;
        } else if (!first_char && ch == '\n') {
            first_char = 1;
            putc(ch, stdout);
        } else
            putc(ch, stdout);
    }
}