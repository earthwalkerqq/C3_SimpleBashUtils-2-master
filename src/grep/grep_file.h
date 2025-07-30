#ifndef GREP_FILE_H
#define GREP_FILE_H

#include "../common/source.h"

#define COUNT_PATTERNS 5

int grep_with_file_pattern(char *pattern_file, char *filename);
int grep_with_file_pattern_input(char *file_pattern);
int grep_with_file_pattern_file(char *file_pattern, char *filename);
int grep_input_many_patterns(char **pattrens, int len);
int grep_file_many_patterns(char *filename, char **pattrens, int len);
int find_pattern(char *string, char *pattern);
char **read_pattern_from_file(char *filename, int *len, int *error);

#endif