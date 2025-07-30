#ifndef GREP_FLAG_H
#define GREP_FLAG_H

#include "grep_count.h"
#include "grep_file.h"
#include "grep_ignore.h"
#include "grep_inverse.h"
#include "grep_num.h"
#include "grep_template.h"
#include "grep_without_error.h"

int processing(int argc, char *argv[]);
int (*processing_option(char option))(char *, char *);

#endif