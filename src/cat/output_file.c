#include "output_file.h"

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
                default:
                    res = EXIT_FAILURE;
                    break;
            }
        }
    }
    return res;
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