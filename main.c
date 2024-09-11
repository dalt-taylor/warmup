#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * build_sep - Constructs the separator string from command line arguments.
 * 
 * @argc: The number of command line arguments.
 * @argv: The array of command line arguments.
 * 
 * If no command line arguments are provided, the default separator is set to
 * a space and a tab (" \t"). If arguments are provided, they are concatenated
 * together to form the separator string.
 * 
 * Returns: A dynamically allocated string containing the separators.
 */
char *build_sep(int argc, char *argv[]) {
    // If no arguments are given, default separator is space and tab
    if (argc <= 1) {
        return strdup(" \t");
    }

    // Calculate total length of all argument strings for separator
    size_t total_length = 0;
    for (int i = 1; i < argc; ++i) {
        total_length += strlen(argv[i]);
    }

    // Allocate memory for the separator string
    char *sep = malloc(total_length + 1);
    if (!sep) return NULL;

    // Concatenate arguments to form the separator string
    sep[0] = '\0'; // Initialize the separator string
    for (int i = 1; i < argc; ++i) {
        strcat(sep, argv[i]);
    }

    return sep;
}

/**
 * main - The main function that reads input lines, splits them into words, and prints the result.
 * 
 * @argc: The number of command line arguments.
 * @argv: The array of command line arguments.
 * 
 * The main function reads lines of input (up to 4000 characters), splits each line
 * into words using the `string_split` function with the provided or default separator,
 * prints each word surrounded by square brackets, and exits when a line with just a
 * period (".") is entered. The function ensures no memory leaks by freeing dynamically
 * allocated memory.
 * 
 * Returns: 0 on success, 1 on failure.
 */
int main(int argc, char *argv[]) {
    // Build the separator string based on command line arguments
    char *sep = build_sep(argc, argv);
    if (!sep) {
        fprintf(stderr, "Failed to allocate memory for separator.\n");
        return 1;
    }

    // Buffer to hold input lines, supporting up to 4000 characters
    char buffer[4001];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character from input

        // Exit if the input is a period (".") with no other text
        if (strcmp(buffer, ".") == 0) break;

        // Split the input line into words based on the separator
        int num_words;
        char **words = string_split(buffer, sep, &num_words);

        // Print each word surrounded by square brackets
        for (int i = 0; i < num_words; ++i) {
            printf("[%s]", words[i]);
            free(words[i]); // Free each word
        }
        printf("\n");

        free(words); // Free the array of words
    }

    free(sep); // Free the separator string
    return 0;
}
