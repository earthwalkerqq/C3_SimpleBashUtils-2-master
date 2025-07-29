#ifndef GREP_WITH_FLAG_H
#define GREP_WITH_FLAG_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_STRING 100
#define COUNT_PATTERNS 5

int processing(int argc, char *argv[]);
int (*processing_option(char option))(char *, char *);
int inverse_grep(char *pattern, char *filename);
int grep_ignore_registre(char *pattern, char *filename);
int grep_count_line(char *pattern, char *filename);
int grep_with_template(char *pattern, char *filename);
int grep_with_line_nun(char *pattern, char *filename);
int grep_without_flag(const char *pattern, FILE *file);
int grep_without_error(char *pattern, char *filename);
int grep_from_file(char *pattern, char *filename, char inverse_flag, char error_flag);
int grep_input_with_line_num(char *pattern);
int grep_file_with_line_num(char *pattern, char *filename);
int grep_count_from_file(char *pattern, char *filename);
void print_res(char *string, const char *pattern);
char *print_grep_string(char *string, const char *pattern);
int grep_from_input(char *pattern, char inverse_flag);
int grep_count_from_input(char *pattern);
size_t s21_strlen(const char *string);
char *s21_strstr(char *string, const char *pattern);
char s21_is_lowwer(const char ch);
char s21_is_alpfa(const char ch);

#endif