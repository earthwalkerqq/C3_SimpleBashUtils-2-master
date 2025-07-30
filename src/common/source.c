#include "source.h"

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

size_t s21_strlen(const char *string) {
    size_t len;
    for (len = 0; string[len]; len++);
    return len;
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

char *print_grep_string(char *string, const char *pattern) {
    char *start = s21_strstr(string, pattern);
    int i;
    for (i = 0; string + i != start; i++) putchar(string[i]);
    printf("\033[31m%s\033[0m", pattern);
    return string + i + s21_strlen(pattern);
}

void destroy_char_arr(char **arr, int len) {
    for (int i = 0; i < len; i++) {
        free(arr[i]);
    }
}