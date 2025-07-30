#ifndef GREP_TEMPLATE_H
#define GREP_TEMPLATE_H

#include "../common/source.h"

int grep_with_template(char *pattern, char *filename);
int grep_from_input(char *pattern, char inverse_flag, char num_flag, char match_flag);
int grep_from_file(char *pattern, char *filename, char inverse_flag, char error_flag, char num_flag,
                   char match_flag);

#endif