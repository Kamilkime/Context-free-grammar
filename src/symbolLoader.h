#ifndef _SYMBOLLOADER_H_IS_INCLUDED_
#define _SYMBOLLOADER_H_IS_INCLUDED_

#include "list.h"

typedef enum LoadResult {SUCCESS, INCORRECT_SYNTAX, NON_ALNUM_CHAR, RESERVED_CHAR, SYMBOL_NOT_DEFINED, SYMBOL_ALREADY_DEFINED} LoadResult;

// Load terminal symbols from the grammar line
LoadResult loadTerminalSymbols(List *targetList, char *grammar, int *i);

// Load non-terminal symbols from the grammar line
LoadResult loadNonTerminalSymbols(List *targetList, List *terminalSymbols, char *grammar, int *i);

// Load grammar rules symbols from the grammar line
LoadResult loadRules(List **targetList, List *terminalSymbols, List *nonTerminalSymbols, char *grammar, int *i);

// Returns index of the symbol in the given list
int getSymbolIndex(List *symbolList, char symbol);

// Turns a list of char pointers into a string (char array)
char *charListToArray(List *charList);

#endif