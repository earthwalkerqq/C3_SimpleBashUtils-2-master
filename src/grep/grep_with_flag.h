#ifndef GREP_WITH_FLAG_H
#define GREP_WITH_FLAG_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_STRING 100

// int grep_with_flag(const char *option, const char *pattern, const char *file);
int grep_from_input(const char *patter);
int processing(int argc, char *argv[]);
char *s21_strstr(char *string, const char *pattern);
size_t s21_strlen(const char *string);
int grep_without_flag(const char *pattern, FILE *file);
void print_res(char *string, const char *pattern);

#endif