#include "split.h"
#include <stdlib.h>
#include <string.h>

/**
 * count_words - Counts the number of words in the input string separated by
 * any character in the sep string.
 * 
 * @input: The input string to be split into words.
 * @sep: The separator characters.
 * 
 * The function counts both regular words and empty words at the start/end if
 * the input starts or ends with a separator. It uses `strspn` and `strcspn` to
 * efficiently skip over separator characters and count words.
 * 
 * Returns: The number of words in the input string.
 */
static int count_words(const char *input, const char *sep) {
    int count = 0;
    const char *pos = input;

    // Count leading empty word if input starts with a separator
    if (*pos && strchr(sep, *pos)) {
        count++;
    }

    // Loop through the input and count words by skipping separators
    while (*pos) {
        pos += strspn(pos, sep); // Skip separator characters
        if (*pos) {
            count++;
            pos += strcspn(pos, sep); // Skip non-separator characters
        }
    }

    // Count trailing empty word if input ends with a separator
    if (*input && strchr(sep, input[strlen(input) - 1])) {
        count++;
    }

    return count;
}

/**
 * copy_word - Allocates and copies a word from the input string.
 * 
 * @start: The start of the word in the input string.
 * @len: The length of the word to be copied.
 * 
 * This function allocates memory for a word and copies it from the input string,
 * ensuring that the copied word is null-terminated.
 * 
 * Returns: A pointer to the newly allocated word.
 */
static char *copy_word(const char *start, size_t len) {
    char *word = malloc(len + 1); // Allocate space for the word plus the null terminator
    if (word) {
        strncpy(word, start, len); // Copy the word from the input string
        word[len] = '\0'; // Null-terminate the string
    }
    return word;
}

/**
 * string_split - Splits a given input string into words based on separator characters.
 * 
 * @input: The input string to be split.
 * @sep: The separator characters to split the input by.
 * @num_words: Pointer to store the number of words found in the input string.
 * 
 * The function splits the input string into words using any character from the `sep`
 * string as a separator. It handles leading and trailing separators by treating them
 * as empty words. The function returns an array of dynamically allocated words, which
 * can be freed later. The number of words is stored in `num_words`.
 * 
 * Returns: A dynamically allocated array of words.
 */
char **string_split(const char *input, const char *sep, int *num_words) {
    *num_words = 0;

    // Handle NULL input or separator
    if (!input || !sep) return NULL;

    // Count the number of words, including handling empty words
    int word_count = count_words(input, sep);
    char **words = calloc(word_count + 1, sizeof(char *)); // Allocate array for words
    if (!words) return NULL;

    const char *pos = input;
    int index = 0;

    // Handle leading empty word if input starts with a separator
    if (*pos && strchr(sep, *pos)) {
        words[index++] = strdup(""); // Add an empty word
    }

    // Split the input string into words based on the separators
    while (*pos) {
        pos += strspn(pos, sep); // Skip separator characters
        if (*pos) {
            const char *start = pos;
            size_t len = strcspn(pos, sep); // Find the length of the word
            words[index++] = copy_word(start, len); // Copy the word
            pos += len; // Move the position to the end of the word
        }
    }

    // Handle trailing empty word if input ends with a separator
    if (*input && strchr(sep, input[strlen(input) - 1])) {
        words[index++] = strdup(""); // Add an empty word
    }

    *num_words = index; // Set the number of words
    return words;
}
