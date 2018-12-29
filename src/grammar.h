#ifndef _GRAMMAR_H_IS_INCLUDED_
#define _GRAMMAR_H_IS_INCLUDED_

#include "list.h"
#include "symbolLoader.h"

// Load grammar from a given line
LoadResult loadGrammar(char *grammar);

// Check if the given word is valid with a given grammar
int checkWord(char *word, int nonTerminalIndex);

// Generate a new word valid with a given grammar
char *generateWord(int nonTerminalIndex);

// Print grammar
void printGrammar(void);

#endif