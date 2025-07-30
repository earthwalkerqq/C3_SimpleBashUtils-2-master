#include "grep_template.h"

int grep_with_template(char *pattern, char *filename) {
    int error = EXIT_SUCCESS;
    error = (filename == NULL) ? grep_from_input(pattern, 0, 0) : grep_from_file(pattern, filename, 0, 0, 0);
    return error;
}

int grep_from_input(char *pattern, char inverse_flag, char num_flag) {
    int error = EXIT_SUCCESS;
    regex_t regex;
    int reti;
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        perror("Failed to compile regular expression");
        error = EXIT_FAILURE;
    } else {
        int count_num;
        for (count_num = 1;; count_num++) {
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
            if (inverse_flag) {
                if (!regexec(&regex, string, 0, NULL, 0))
                    (num_flag) ? printf("%d:%s\n", count_num, string) : printf("%s\n", string);
            } else {
                char has_iter = 0, flag_first = 1;
                char *str_tmp = NULL;
                for (str_tmp = string; !regexec(&regex, str_tmp, 0, NULL, 0); flag_first = 0, has_iter = 1) {
                    if (num_flag && flag_first) printf("%d:", count_num);
                    str_tmp = print_grep_string(str_tmp, pattern);
                }
                if (has_iter) printf("%s\n", str_tmp);
            }
            free(string);
        }
    }
    regfree(&regex);
    return error;
}

int grep_from_file(char *pattern, char *filename, char inverse_flag, char error_flag, char num_flag) {
    int error = EXIT_SUCCESS;
    FILE *file = NULL;
    if ((file = fopen(filename, "r")) == NULL) {
        if (error_flag) return EXIT_FAILURE;
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
    int count_num = 1;
    for (size_t size = (size_t)SIZE_STRING; !flag_eof && !error; size = (size_t)SIZE_STRING, count_num++) {
        char *line = (char *)malloc(size * sizeof(char));
        if (line == NULL) {
            fclose(file);
            regfree(&regex);
            return EXIT_FAILURE;
        }
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
        reti = regexec(&regex, line, 0, NULL, 0);
        if (inverse_flag && reti)
            printf("%s\n", line);
        else if (!inverse_flag && !reti) {
            char has_iter = 0, flag_first = 1;
            char *str_tmp = NULL;
            for (str_tmp = line; !reti;
                 reti = regexec(&regex, str_tmp, 0, NULL, 0), flag_first = 0, has_iter = 1) {
                if (num_flag && flag_first) printf("%d:", count_num);
                str_tmp = print_grep_string(str_tmp, pattern);
            }
            if (has_iter) printf("%s\n", str_tmp);
        }
        free(line);
    }
    fclose(file);
    regfree(&regex);
    return error;
}