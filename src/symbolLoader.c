#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "symbolLoader.h"

// Load terminal symbols from the grammar line
LoadResult loadTerminalSymbols(List *terminalSymbols, char *grammar, int *i) {
    for (; *i < strlen(grammar); *i += 1) {
        char c = grammar[*i];
        if (c == ',') {
            continue;
        }

        if (c == '}') {
            break;
        }

        if (!isalnum(c)) {
            return NON_ALNUM_CHAR;
        }

        if (c == 'E') {
            return RESERVED_CHAR;
        }

        char *symbol = malloc(sizeof(char));
        *symbol = c;

        addToList(terminalSymbols, symbol);
    }

    return SUCCESS;
}

// Load non-terminal symbols from the grammar line
LoadResult loadNonTerminalSymbols(List *nonTerminalSymbols, List *terminalSymbols, char *grammar, int *i) {
    for (; *i < strlen(grammar); *i += 1) {
        char c = grammar[*i];
        if (c == ',') {
            continue;
        }

        if (c == '}') {
            break;
        }

        if (!isalnum(c)) {
            return NON_ALNUM_CHAR;
        }

        if (c == 'E') {
            return RESERVED_CHAR;
        }

        if (getSymbolIndex(terminalSymbols, c) != -1) {
            return SYMBOL_ALREADY_DEFINED;
        }

        char *symbol = malloc(sizeof(char));
        *symbol = c;

        addToList(nonTerminalSymbols, symbol);
    }

    return SUCCESS;
}

// Load grammar rules symbols from the grammar line
LoadResult loadRules(List **rules, List *terminalSymbols, List *nonTerminalSymbols, char *grammar, int *i) {
    for (; *i < strlen(grammar); *i += 1) {
        if (grammar[*i] == '}') {
            break;
        }

        int symbolIndex = getSymbolIndex(nonTerminalSymbols, grammar[*i]);
        if (symbolIndex == -1) {
            return SYMBOL_NOT_DEFINED;
        }

        if (grammar[++(*i)] != ' ' || grammar[++(*i)] != '-' || grammar[++(*i)] != '>' || grammar[++(*i)] != ' ') {
            return INCORRECT_SYNTAX;
        }

        // Move past the space from " -> "
        *i += 1;

        List *ruleChars = initList(5);
        while (*i < strlen(grammar) && grammar[*i] != ',' && grammar[*i] != '}') {
            if (grammar[*i] == '|') {
                addToList(rules[symbolIndex], charListToArray(ruleChars));

                clearList(ruleChars, 1);
                *i += 1;

                continue;
            }

            if (grammar[*i] != 'E' && getSymbolIndex(terminalSymbols, grammar[*i]) == -1 && getSymbolIndex(nonTerminalSymbols, grammar[*i]) == -1) {
                return SYMBOL_NOT_DEFINED;
            }

            char *symbol = malloc(sizeof(char));
            *symbol = grammar[(*i)++];

            addToList(ruleChars, symbol);
        }

        if (ruleChars -> items > 0) {
            addToList(rules[symbolIndex], charListToArray(ruleChars));
        }

        freeList(ruleChars, 1);

        if (grammar[*i] == '}') {
           break;
        }

        // Skip the space after comma
        *i += 1;
    }

    return SUCCESS;
}

// Returns index of the symbol in the given list
int getSymbolIndex(List *symbolList, char symbol) {
    int i = 0;

    for (; i < symbolList -> items; i++) {
        if (*((char*) getFromList(symbolList, i)) == symbol) {
            return i;
        }
    }

    return -1;
}

// Turns a list of char pointers into a string (char array)
char *charListToArray(List *charList) {
    char *array = malloc(sizeof(char) * (charList -> items + 1));

    int i = 0;
    for (; i < charList -> items; i++) {
        array[i] = *((char*) getFromList(charList, i));
    }

    array[i] = '\0';

    return array;
}