#include "split.h"
#include <stdlib.h>
#include <string.h>

static int count_words(const char *input, const char *sep) {
    int count = 0;
    const char *pos = input;

    while (*pos) {
        pos += strspn(pos, sep); // Skip separator characters
        if (*pos) {
            count++;
            pos += strcspn(pos, sep); // Skip non-separator characters
        }
    }

    return count;
}

static char *copy_word(const char *start, size_t len) {
    char *word = malloc(len + 1);
    if (word) {
        strncpy(word, start, len);
        word[len] = '\0';
    }
    return word;
}

char **string_split(const char *input, const char *sep, int *num_words) {
    *num_words = 0;

    if (!input || !sep) return NULL;

    int word_count = count_words(input, sep);
    char **words = calloc(word_count + 1, sizeof(char *));
    if (!words) return NULL;

    const char *pos = input;
    int index = 0;

    while (*pos) {
        pos += strspn(pos, sep); // Skip separator characters
        if (*pos) {
            const char *start = pos;
            size_t len = strcspn(pos, sep); // Length of the word
            words[index++] = copy_word(start, len);
            pos += len;
        }
    }

    *num_words = index;
    return words;
}
