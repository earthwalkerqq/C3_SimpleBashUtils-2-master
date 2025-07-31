#include "grep_flag.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        perror(
            "usage: grep [-A num] [-B num] [-C[num]]\n \
	[-e pattern] [-f file] [--binary-files=value] [--color=when]\n \
	[--context[=num]] [--directories=action] [--label] [--line-buffered]\n \
	[--null] [pattern] [file ...]\n");
        return EXIT_FAILURE;
    }
    int error = processing(argc, argv);
    if (error) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}