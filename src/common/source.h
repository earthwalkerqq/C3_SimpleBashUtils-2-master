#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define SIZE_STRING 100

char *s21_strstr(char *string, const char *pattern);
size_t s21_strlen(const char *string);
char s21_is_lowwer(const char ch);
char s21_is_alpfa(const char ch);
char *print_grep_string(char *string, const char *pattern);
void destroy_char_arr(char **arr, int len);

#endif