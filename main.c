#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *build_sep(int argc, char *argv[]) {
    if (argc <= 1) {
        return strdup(" \t");
    }

    size_t total_length = 0;
    for (int i = 1; i < argc; ++i) {
        total_length += strlen(argv[i]);
    }

    char *sep = malloc(total_length + 1);
    if (!sep) return NULL;

    sep[0] = '\0';
    for (int i = 1; i < argc; ++i) {
        strcat(sep, argv[i]);
    }

    return sep;
}

int main(int argc, char *argv[]) {
    char *sep = build_sep(argc, argv);
    if (!sep) {
        fprintf(stderr, "Failed to allocate memory for separator.\n");
        return 1;
    }

    char buffer[4001];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        if (strcmp(buffer, ".") == 0) break;

        int num_words;
        char **words = string_split(buffer, sep, &num_words);

        for (int i = 0; i < num_words; ++i) {
            printf("[%s]", words[i]);
            free(words[i]);
        }
        printf("\n");

        free(words);
    }

    free(sep);
    return 0;
}
