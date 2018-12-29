#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "grammar.h"
#include "symbolLoader.h"

int main(int argc, char const *argv[]) {
    printf("\nChoose grammar source:\n");
    printf("  1. File\n");
    printf("  2. Manual input\n\n");
    printf("Selected option: ");

    char inputType;
    if (!(inputType = getc(stdin))) {
        printf("You must choose either 1 or 2 as the input method!\n\n");
        return 0;
    }

    // Discard all other characters
    while (getc(stdin) != '\n');

    char grammarBuffer[8192];
    if (inputType == '1') {
        printf("Grammar file name: ");

        char nameBuffer[1024];
        if (fgets(nameBuffer, 1024, stdin) == NULL) {
            printf("Given file name is not valid!\n\n");
            return 0;
        }

        nameBuffer[strlen(nameBuffer) - 1] = '\0';

        FILE *inputFile = fopen(nameBuffer, "r");
        if (inputFile == NULL) {
            printf("Given file does not exist!\n\n");
            return 0;
        }

        if (fgets(grammarBuffer, 8192, inputFile) == NULL) {
            printf("Given grammar line is not valid!\n\n");
            return 0;
        }
    } else if (inputType == '2') {
        printf("Enter grammar: ");

        if (fgets(grammarBuffer, 8192, stdin) == NULL) {
            printf("Given grammar line is not valid!\n\n");
            return 0;
        }
    } else {
        printf("You must choose either 1 or 2 as the input method!\n\n");
        return 0;
    }

    LoadResult grammarStatus = loadGrammar(grammarBuffer);
    switch (grammarStatus) {
        case INCORRECT_SYNTAX:
            printf("Syntax error!\n\n");
            return 0;
        case NON_ALNUM_CHAR:
            printf("Symbols can only be alphabetic characters!\n\n");
            return 0;
        case RESERVED_CHAR:
            printf("E cannot be used as a symbol!\n\n");
            return 0;
        case SYMBOL_NOT_DEFINED:
            printf("A symbol is not defined but used!\n\n");
            return 0;
        case SYMBOL_ALREADY_DEFINED:
            printf("A symbol is defined multiple times!\n\n");
            return 0;
        default:
            break;
    }

    printf("\nLoaded grammar:\n");
    printGrammar();

    srand(time(NULL));

    printf("\nWord 1: \"%s\"\n", generateWord(-1));
    printf("Word 2: \"%s\"\n", generateWord(-1));
    printf("Word 3: \"%s\"\n", generateWord(-1));
    printf("Word 4: \"%s\"\n", generateWord(-1));
    printf("Word 5: \"%s\"\n\n", generateWord(-1));

    return 0;
}
