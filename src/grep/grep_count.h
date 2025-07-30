#ifndef GREP_COUNT_H
#define GREP_COUNT_H

#include "../common/source.h"

int grep_count_line(char *pattern, char *filename);
int grep_count_from_input(char *pattern);
int grep_count_from_file(char *pattern, char *filename);

#endif