#include "grep_ignore.h"

#include "grep_template.h"

int grep_ignore_registre(char *pattern, char *filename) {
    int error = EXIT_FAILURE;
    int len_new_pattern = 0;
    int size = SIZE_STRING;
    char *new_pattern = (char *)malloc(size * sizeof(char));
    for (int i = 0; (size_t)i < s21_strlen(pattern); i++) {
        if (s21_is_alpfa(pattern[i])) {
            if (len_new_pattern > size - 10) {
                size *= 2;
                if ((new_pattern = realloc(new_pattern, size * sizeof(char))) == NULL) {
                    perror("CAN'T ALLOCATE OBJECT");
                    free(new_pattern);
                    return EXIT_FAILURE;
                }
            }
            int dif = (int)'a' - (int)'A';
            new_pattern[len_new_pattern++] = '[';
            new_pattern[len_new_pattern++] = pattern[i];
            new_pattern[len_new_pattern++] =
                (s21_is_lowwer(pattern[i])) ? (int)pattern[i] - dif : (int)pattern[i] + dif;
            new_pattern[len_new_pattern++] = ']';
        } else
            new_pattern[len_new_pattern++] = pattern[i];
    }
    new_pattern[len_new_pattern] = '\0';
    error = grep_with_template(new_pattern, filename);
    free(new_pattern);
    return error;
}