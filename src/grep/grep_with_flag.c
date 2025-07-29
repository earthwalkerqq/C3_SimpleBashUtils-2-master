#include "grep_with_flag.h"

int processing(int argc, char *argv[]) {
    int error = EXIT_SUCCESS;
    int (*func)(char *, char *);
    if (argc == 2)
        error = grep_from_input(argv[1], 0);
    else if (argc == 3 && *(argv[1]) == '-') {
        func = processing_option(argv[1][1]);
        if (func == NULL) {
            perror("UNCORRECT OPTION");
            error = EXIT_FAILURE;
        } else
            error = func(argv[2], NULL);
    } else if (argc == 3)
        error = grep_from_file(argv[1], argv[2], 0, 0);
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
            res_func = break;
    }
    return res_func;
}

int grep_with_file_pattern(char *pattern_file, char *filename) {
    int error = EXIT_SUCCESS;
    error = (filename == NULL) ?: ;
    return error;
}

int grep_with_file_pattern_input(char *file_pattern) {
    int error = EXIT_SUCCESS;
    FILE *file = NULL;
    if ((file = fopen(file_pattern, "r")) == NULL) {
        perror("CAN'T OPEN FILE");
        return EXIT_FAILURE;
    }
    // regex_t regex;
    // int reti;
    // reti = regcomp(&regex, pattern, REG_EXTENDED);
    // if (reti) {
    //     perror("Failed to compile regular expression");
    //     return EXIT_FAILURE;
    // }
    char flag_eof = 0;
    int size_arr = COUNT_PATTERNS;
    char **patterns_arr = (char **)malloc(size_arr * sizeof(char *));
    if (patterns_arr == NULL) {
        perror("CAN'T REALLOC MEMORY");
        return EXIT_FAILURE;
    }
    int i;
    for (i = 0; !flag_eof && !error; i++) {
        if (size_arr < i + 2) {
            size_arr *= 2;
            patterns_arr = (char **)realloc(patterns_arr, size_arr * sizeof(char *));
            if (patterns_arr == NULL) {
                perror("CAN'T REALLOC MEMORY");
                error = EXIT_FAILURE;
                break;
            }
        }
        char ch;
        int size = SIZE_STRING;
        char *line = (char *)malloc(size * sizeof(char));
        if (line == NULL) {
            perror("CAN'T REALLOC MEMORY");
            error = EXIT_FAILURE;
            break;
        }
        int j;
        for (j = 0; (ch = getc(file)) != '\n' && ch != EOF; j++) {
            if (j > size - 10) {
                size *= 2;
                line = (char *)realloc(line, size * sizeof(char));
                if (line == NULL) {
                    perror("CAN'T REALLOC MEMORY");
                    error = EXIT_FAILURE;
                    break;
                }
            }
            line[j] = ch;
        }
        line[j] = '\0';
        if (ch == EOF) {
            flag_eof = 1;
            break;
        }
    }

    destroy_char_arr(patterns_arr, i);
    free(patterns_arr);
    return error;
}

void destroy_char_arr(char **arr, int len) {
    for (int i = 0; i < len; i++) {
        free(arr[i]);
    }
}

int grep_without_error(char *pattern, char *filename) {
    (filename == NULL) ? grep_from_input(pattern, 0) : grep_from_file(pattern, filename, 0, 1);
    return EXIT_SUCCESS;
}

int grep_with_line_nun(char *pattern, char *filename) {
    int error = EXIT_SUCCESS;
    error =
        (filename == NULL) ? grep_input_with_line_num(pattern) : grep_file_with_line_num(pattern, filename);
    return error;
}

int grep_input_with_line_num(char *pattern) {
    int error = EXIT_SUCCESS;
    regex_t regex;
    int reti;
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        perror("Failed to compile regular expression");
        error = EXIT_FAILURE;
    } else {
        int count_line;
        for (count_line = 1;; count_line++) {
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
            char flag_first = 1, has_iter = 0;
            ;
            for (str_tmp = string; !regexec(&regex, str_tmp, 0, NULL, 0); has_iter = 1) {
                if (flag_first) {
                    flag_first = 0;
                    printf("%d:", count_line);
                }
                str_tmp = print_grep_string(str_tmp, pattern);
            }
            if (has_iter) printf("%s\n", str_tmp);
            free(string);
        }
    }
    regfree(&regex);
    return error;
}

int grep_file_with_line_num(char *pattern, char *filename) {
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
    int num_line = 1;
    for (size_t size = (size_t)SIZE_STRING; !flag_eof && !error; size = (size_t)SIZE_STRING, num_line++) {
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
        char flag_first = 1, has_iter = 0;
        char *str_tmp = NULL;
        for (str_tmp = line; !regexec(&regex, str_tmp, 0, NULL, 0); has_iter = 1) {
            if (flag_first) {
                flag_first = 0;
                printf("%d:", num_line);
            }
            str_tmp = print_grep_string(str_tmp, pattern);
        }
        if (has_iter) printf("%s\n", str_tmp);
        free(line);
    }
    fclose(file);
    regfree(&regex);
    return error;
}

int grep_count_line(char *pattern, char *filename) {
    int error = EXIT_SUCCESS;
    error = (filename == NULL) ? grep_count_from_input(pattern) : grep_count_from_file(pattern, filename);
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

char *print_grep_string(char *string, const char *pattern) {
    char *start = s21_strstr(string, pattern);
    int i;
    for (i = 0; string + i != start; i++) putchar(string[i]);
    printf("\033[31m%s\033[0m", pattern);
    return string + i + s21_strlen(pattern);
}

int inverse_grep(char *pattern, char *filename) {
    int error = EXIT_SUCCESS;
    error = (filename == NULL) ? grep_from_input(pattern, 1) : grep_from_file(pattern, filename, 1, 0);
    return error;
}

int grep_ignore_registre(char *pattern, char *filename) {
    int error = EXIT_FAILURE;
    int len_new_pattern = 0;
    int size = SIZE_STRING;
    char *new_pattern = (char *)malloc(size * sizeof(char));
    for (int i = 0; (size_t)i < s21_strlen(pattern); i++) {
        if (s21_is_alpfa(pattern[i])) {
            if (len_new_pattern > size - 10) {
                size *= 2;
                if ((new_pattern = realloc(new_pattern, size * sizeof(char))) == NULL) {
                    perror("CAN'T ALLOCATE OBJECT");
                    free(new_pattern);
                    return EXIT_FAILURE;
                }
            }
            int dif = (int)'a' - (int)'A';
            new_pattern[len_new_pattern++] = '[';
            new_pattern[len_new_pattern++] = pattern[i];
            new_pattern[len_new_pattern++] =
                (s21_is_lowwer(pattern[i])) ? (int)pattern[i] - dif : (int)pattern[i] + dif;
            new_pattern[len_new_pattern++] = ']';
        } else
            new_pattern[len_new_pattern++] = pattern[i];
    }
    new_pattern[len_new_pattern] = '\0';
    error = grep_with_template(new_pattern, filename);
    free(new_pattern);
    return error;
}

int grep_with_template(char *pattern, char *filename) {
    int error = EXIT_SUCCESS;
    error = (filename == NULL) ? grep_from_input(pattern, 0) : grep_from_file(pattern, filename, 0, 0);
    return error;
}

int grep_without_flag(const char *pattern, FILE *file) {
    int error = EXIT_SUCCESS;
    char flag_eof = 0;
    regex_t regex;
    int reti;
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        perror("Failed to compile regular expression");
        return EXIT_FAILURE;
    }
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
        reti = regexec(&regex, line, 0, NULL, 0);
        if (!reti) print_res(line, pattern);
        free(line);
    }
    regfree(&regex);
    return error;
}

int grep_from_file(char *pattern, char *filename, char inverse_flag, char error_flag) {
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
        reti = regexec(&regex, line, 0, NULL, 0);
        if (inverse_flag && reti)
            printf("%s\n", line);
        else if (!inverse_flag && !reti) {
            char has_iter = 0;
            char *str_tmp = NULL;
            for (str_tmp = line; !reti; reti = regexec(&regex, str_tmp, 0, NULL, 0), has_iter = 1)
                str_tmp = print_grep_string(str_tmp, pattern);
            if (has_iter) printf("%s\n", str_tmp);
        }
        free(line);
    }
    fclose(file);
    regfree(&regex);
    return error;
}

void print_res(char *string, const char *pattern) {
    char *start = s21_strstr(string, pattern);
    if (start == NULL)
        printf("%s\n", string);
    else {
        int i;
        for (i = 0; string + i != start; i++) putchar(string[i]);
        printf("\033[31m%s\033[0m", pattern);
        printf("%s\n", string + i + s21_strlen(pattern));
    }
}

int grep_from_input(char *pattern, char inverse_flag) {
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
            reti = regexec(&regex, string, 0, NULL, 0);
            if (inverse_flag && reti)
                printf("%s\n", string);
            else if (!inverse_flag && !reti)
                print_res(string, pattern);
            free(string);
        }
    }
    regfree(&regex);
    return error;
}

char s21_is_lowwer(const char ch) {
    char res = 0;
    if (ch >= 'a' && ch <= 'z') res = 1;
    return res;
}

char s21_is_alpfa(const char ch) {
    char res = 0;
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) res = 1;
    return res;
}

size_t s21_strlen(const char *string) {
    size_t len;
    for (len = 0; string[len]; len++);
    return len;
}

char *s21_strstr(char *string, const char *pattern) {
    char *res = NULL;
    for (int i = 0; string[i] && res == NULL; i++) {
        if (string[i] == *pattern) {
            const char *find_string = pattern + 1;
            char flag = 0;
            for (int j = i + 1; *find_string && !flag; j++, find_string++) {
                if (string[j] != *find_string) flag = 1;
            }
            if (!flag) res = string + i;
        }
    }
    return res;
}