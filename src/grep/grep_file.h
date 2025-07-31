#ifndef GREP_FILE_H
#define GREP_FILE_H

#include "../common/source.h"

#define COUNT_PATTERNS 5

int grep_with_file_pattern(char *pattern_file, char *filename, char most_arg_flag);
int grep_with_file_pattern_input(char *file_pattern);
int grep_with_file_pattern_file(char *file_pattern, char *filename, char hide_flag);
int grep_file_many_patterns(char *filename, char **patterns, int len, char inverse_flag, char error_flag,
                            char num_flag, char hide_flag);
int grep_input_many_patterns(char **patterns, int len, char inverse_flag);
int find_pattern(char *string, char *pattern, char *filename, char invers_flag, int count_num,
                 char hide_flag);
char **read_pattern_from_file(char *filename, int *len, int *error);

#endif