#include "grep_file.h"

int grep_with_file_pattern(char *pattern_file, char *filename, char most_arg_flag) {
    int error = EXIT_SUCCESS;
    if (filename == NULL) {
        error = grep_with_file_pattern_input(pattern_file);
    } else if (most_arg_flag) {
        error = grep_with_file_pattern_file(pattern_file, filename, 0);
    } else {
        error = grep_with_file_pattern_file(pattern_file, filename, -1);
    }
    return error;
}

int grep_with_file_pattern_input(char *file_pattern) {
    int error = EXIT_SUCCESS;
    char **patterns = NULL;
    int len;
    patterns = read_pattern_from_file(file_pattern, &len, &error);
    if (!error) {
        error = grep_input_many_patterns(patterns, len, 0);
    }
    destroy_char_arr(patterns, len);
    free(patterns);
    return error;
}

int grep_with_file_pattern_file(char *file_pattern, char *filename, char hide_flag) {
    int error = EXIT_SUCCESS;
    char **patterns = NULL;
    int len = 0;
    patterns = read_pattern_from_file(file_pattern, &len, &error);
    if (!error) {
        error = grep_file_many_patterns(filename, patterns, len, 0, 0, 0, hide_flag);
    }
    destroy_char_arr(patterns, len);
    free(patterns);
    return error;
}

int grep_input_many_patterns(char **patterns, int len, char inverse_flag) {
    int error = EXIT_SUCCESS;
    int size = SIZE_STRING;
    char *string = (char *)malloc(size * sizeof(char));
    for (;;) {
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
        char flag = 0;
        for (int i = 0; i < len && !flag; i++)
            flag = find_pattern(string, patterns[i], NULL, inverse_flag, 0, -1);
        free(string);
    }
    return error;
}

int grep_file_many_patterns(char *filename, char **patterns, int len, char inverse_flag, char error_flag,
                            char num_flag, char hide_flag) {
    int error = EXIT_SUCCESS;
    FILE *file = NULL;
    if ((file = fopen(filename, "r")) == NULL) {
        if (error_flag) return EXIT_FAILURE;
        perror("CAN'T OPEN FILE");
        return EXIT_FAILURE;
    }
    char flag_eof = 0;
    int count_num = 1;
    for (int size = SIZE_STRING; !flag_eof && !error; size = SIZE_STRING, count_num++) {
        char ch;
        char *line = (char *)malloc(size * sizeof(char));
        if (line == NULL) {
            return EXIT_FAILURE;
        }
        int i;
        for (i = 0; (ch = getc(file)) != '\n' && !flag_eof; i++) {
            if (ch == EOF)
                flag_eof = 1;
            else if (size - 10 < i) {
                size *= 2;
                if ((line = (char *)realloc(line, size * sizeof(char))) == NULL) {
                    perror("CAN'T RELOCATE MEMORY");
                    error = EXIT_FAILURE;
                    break;
                }
            }
            line[i] = ch;
        }
        if (!error) {
            line[i] = '\0';
            char flag = 0;
            for (int j = 0; j < len && !flag; j++) {
                if (num_flag)
                    flag = find_pattern(line, patterns[j], filename, inverse_flag, count_num, hide_flag);
                else
                    flag = find_pattern(line, patterns[j], filename, inverse_flag, 0, hide_flag);
            }
        }
        free(line);
    }
    fclose(file);
    return error;
}

int find_pattern(char *string, char *pattern, char *filename, char invers_flag, int count_num,
                 char hide_flag) {
    int res = EXIT_FAILURE;
    if (string == NULL || pattern == NULL) return res;
    regex_t regex;
    int reti;
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        perror("Failed to compile regular expression");
    } else {
        reti = regexec(&regex, string, 0, NULL, 0);
        if (!reti && !invers_flag) {
            char *str_tmp;
            char has_iter = 0, first_flag = 1;
            for (str_tmp = string; !reti; has_iter = 1, first_flag = 0) {
                if (!hide_flag) printf("%s:", filename);
                if (count_num && first_flag) printf("%d:", count_num);
                str_tmp = print_grep_string(str_tmp, pattern);
                reti = regexec(&regex, str_tmp, 0, NULL, 0);
            }
            if (has_iter) printf("%s\n", str_tmp);
            res = EXIT_SUCCESS;
        } else if (reti & invers_flag) {
            if (!hide_flag) printf("%s:", filename);
            (count_num) ? printf("%d:%s\n", count_num, string) : printf("%s\n", string);
            res = EXIT_SUCCESS;
        }
    }
    regfree(&regex);
    return res;
}

char **read_pattern_from_file(char *filename, int *len, int *error) {
    FILE *file = NULL;
    if ((file = fopen(filename, "r")) == NULL) {
        perror("CAN'T OPEN FILE");
        *error = EXIT_FAILURE;
        return NULL;
    }
    char flag_eof = 0;
    int size_arr = COUNT_PATTERNS;
    char **patterns_arr = (char **)malloc(size_arr * sizeof(char *));
    if (patterns_arr == NULL) {
        perror("CAN'T REALLOC MEMORY");
        *error = EXIT_FAILURE;
        return NULL;
    }
    for (*len = 0; !flag_eof && !(*error); (*len)++) {
        if (size_arr < *len + 2) {
            size_arr *= 2;
            patterns_arr = (char **)realloc(patterns_arr, size_arr * sizeof(char *));
            if (patterns_arr == NULL) {
                perror("CAN'T REALLOC MEMORY");
                *error = EXIT_FAILURE;
                break;
            }
        }
        char ch;
        int size = SIZE_STRING;
        char *line = (char *)malloc(size * sizeof(char));
        if (line == NULL) {
            perror("CAN'T REALLOC MEMORY");
            *error = EXIT_FAILURE;
            break;
        }
        int j;
        for (j = 0; (ch = getc(file)) != '\n' && ch != EOF; j++) {
            if (j > size - 10) {
                size *= 2;
                line = (char *)realloc(line, size * sizeof(char));
                if (line == NULL) {
                    perror("CAN'T REALLOC MEMORY");
                    *error = EXIT_FAILURE;
                    break;
                }
            }
            line[j] = ch;
        }
        line[j] = '\0';
        if (j > 0) {
            patterns_arr[*len] = line;
        } else {
            free(line);
            (*len)--;
        }
        if (ch == EOF) {
            flag_eof = 1;
        }
    }
    fclose(file);
    return patterns_arr;
}