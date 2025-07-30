#include "grep_count.h"

int grep_count_line(char *pattern, char *filename) {
    int error = EXIT_SUCCESS;
    error = (filename == NULL) ? grep_count_from_input(pattern) : grep_count_from_file(pattern, filename);
    return error;
}

int grep_count_from_input(char *pattern) {
    int error = EXIT_SUCCESS;
    regex_t regex;
    int reti;
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        perror("Failed to compile regular expression");
        error = EXIT_FAILURE;
    } else {
        for (;;) {
            int size = SIZE_STRING;
            char *string = (char *)malloc(size * sizeof(char));
            char ch;
            int i;
            for (i = 0; (ch = getchar()) != '\n'; i++) {
                if (i > size - 10) {
                    size *= 2;
                    if ((string = realloc(string, size * sizeof(char))) == NULL) {
                        perror("CAN'T MEMORY ALLOCATE");
                        error = EXIT_FAILURE;
                    }
                }
                string[i] = ch;
            }
            if (error) return error;
            string[i] = '\0';
            char *str_tmp = NULL;
            for (str_tmp = string; !regexec(&regex, str_tmp, 0, NULL, 0);)
                str_tmp = print_grep_string(str_tmp, pattern);
            printf("%s\n1\n", str_tmp);
            free(string);
        }
    }
    regfree(&regex);
    return error;
}

int grep_count_from_file(char *pattern, char *filename) {
    int error = EXIT_SUCCESS;
    FILE *file = NULL;
    if ((file = fopen(filename, "r")) == NULL) {
        perror("CAN'T OPEN FILE");
        return EXIT_FAILURE;
    }
    char flag_eof = 0;
    regex_t regex;
    int reti;
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        perror("Failed to compile regular expression");
        return EXIT_FAILURE;
    }
    int count_res = 0;
    for (size_t size = (size_t)SIZE_STRING; !flag_eof && !error; size = (size_t)SIZE_STRING) {
        char *line = (char *)malloc(size * sizeof(char));
        char ch;
        int i;
        for (i = 0; (ch = getc(file)) != '\n'; i++) {
            if (ch == EOF) {
                flag_eof = 1;
                break;
            }
            if (i == (int)(size - 2)) {
                size *= 2;
                if ((line = realloc(line, size * sizeof(char))) == NULL) {
                    perror("CAN'T MEMORY ALLOCATE");
                    error = EXIT_FAILURE;
                    break;
                }
            }
            line[i] = ch;
        }
        line[i] = '\0';
        if (!regexec(&regex, line, 0, NULL, 0)) count_res++;
        free(line);
    }
    printf("%d\n", count_res);
    fclose(file);
    regfree(&regex);
    return error;
}