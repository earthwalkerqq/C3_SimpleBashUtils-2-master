#include "grep_with_flag.h"

int processing(int argc, char *argv[]) {
    int error = EXIT_SUCCESS;
    switch (argc) {
        case 2:
            error = grep_from_input(argv[1]);
            break;
        case 3: {
            FILE *file = NULL;
            if ((file = fopen(argv[2], "r")) == NULL) {
                perror("CAN'T OPEN FILE");
                error = EXIT_FAILURE;
            } else {
                error = grep_without_flag(argv[1], file);
                fclose(file);
            }
            break;
        }
        case 4:
            break;
        default:
            error = EXIT_FAILURE;
    }
    return error;
}

int grep_without_flag(const char *pattern, FILE *file) {
    int error = EXIT_SUCCESS;
    char flag_eof = 0;
    regex_t regex;
    int reti;
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        perror("Не удалось скомпилировать регулярное выражение");
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

void print_res(char *string, const char *pattern) {
    char *start = s21_strstr(string, pattern);
    int i;
    for (i = 0; string + i != start; i++) putchar(string[i]);
    printf("\033[31m%s\033[0m", pattern);
    printf("%s\n", string + i + s21_strlen(pattern));
}

int grep_from_input(const char *pattern) {
    int res = EXIT_SUCCESS;
    regex_t regex;
    int reti;
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        perror("Не удалось скомпилировать регулярное выражение");
        res = EXIT_FAILURE;
    } else {
        for (;;) {
            char *string = (char *)malloc(SIZE_STRING * sizeof(char));
            char ch;
            int i;
            for (i = 0; (ch = getchar()) != '\n'; i++) string[i] = ch;
            string[i] = '\0';
            reti = regexec(&regex, string, 0, NULL, 0);
            if (!reti) print_res(string, pattern);
            free(string);
        }
    }
    regfree(&regex);
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
            for (int j = i + 1; *find_string && !flag; find_string++) {
                if (string[j] != *find_string) flag = 1;
            }
            if (!flag) res = string + i;
        }
    }
    return res;
}

// int grep_with_flag(const char *option, const char *pattern, const char *file) {
//     int res = EXIT_SUCCESS;
//     if (file == NULL) {

//     } else {

//     }
//     return res;
// }