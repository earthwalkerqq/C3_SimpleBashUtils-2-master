#ifndef OUTPUT_FILE_H
#define OUTPUT_FILE_H

#include <stdio.h>
#include <stdlib.h>

int output_file(FILE *file, const char *option);
void output_nonblank(FILE *file);

#endif