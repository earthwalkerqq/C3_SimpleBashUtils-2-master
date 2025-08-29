#ifndef GREP_FLAG_H
#define GREP_FLAG_H

int processing(int argc, char *argv[]);
int (*processing_option(char option))(char *, char *, char);

#endif