#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grammar.h"

static List *terminalSymbols;
static List *nonTerminalSymbols;
static List **rules;

static char startSymbol;

// Load grammar from a given line
LoadResult loadGrammar(char *grammar) {
    int i = 0;

    // Check syntax
    if (grammar[i++] != '{') {
        return INCORRECT_SYNTAX;
    }

    // Load terminal symbols
    terminalSymbols = initList(5);

    LoadResult terminalResult = loadTerminalSymbols(terminalSymbols, grammar, &i);
    if (terminalResult != SUCCESS) {
        return terminalResult;
    }

    // Check syntax
    if (grammar[++i] != ',' || grammar[++i] != '{') {
        return INCORRECT_SYNTAX;
    }

    // Switch to next character
    i++;

    // Load nonTerminal symbols
    nonTerminalSymbols = initList(5);

    LoadResult nonTerminalResult = loadNonTerminalSymbols(nonTerminalSymbols, terminalSymbols, grammar, &i);
    if (nonTerminalResult != SUCCESS) {
        return nonTerminalResult;
    }

    // Check syntax
    if (grammar[++i] != ',' || grammar[++i] != '{') {
        return INCORRECT_SYNTAX;
    }

    // Switch to next character
    i++;

    // Load rules
    rules = malloc(sizeof(List*) * nonTerminalSymbols -> items);
    
    int j = 0;
    for (; j < nonTerminalSymbols -> items; j++) {
        rules[j] = initList(5);
    }

    LoadResult ruleResult = loadRules(rules, terminalSymbols, nonTerminalSymbols, grammar, &i);
    if (ruleResult != SUCCESS) {
        return ruleResult;
    }

    // Check syntax
    if (grammar[++i] != ',') {
        return INCORRECT_SYNTAX;
    }

    // Load start symbol
    if (getSymbolIndex(nonTerminalSymbols, grammar[++i]) == -1) {
        return SYMBOL_NOT_DEFINED;
    }

    startSymbol = grammar[i];

    return SUCCESS;
}

// Check if the given word is valid with a given grammar
int checkWord(char *word, int nonTerminalIndex) {
    // TODO
    return 0;
}

// Generate a new word valid with a given grammar
char *generateWord(int nonTerminalIndex) {
    if (nonTerminalIndex == -1) {
        nonTerminalIndex = getSymbolIndex(nonTerminalSymbols, startSymbol);
    }

    List *ruleList = rules[nonTerminalIndex];
    int ruleIndex = rand() % ruleList -> items;

    char* rule = (char*) getFromList(ruleList, ruleIndex);

    // Check if the selected rule outputs an empty word
    if (!strcmp(rule, "E")) {
        return "";
    }

    List *rulePartResults = initList(5);

    int i = 0, resultLength = strlen(rule), resultShift = 0;
    for (; i < strlen(rule); i++) {
         nonTerminalIndex = getSymbolIndex(nonTerminalSymbols, rule[i]);

        // Non-terminal symbol found - change it to terminal-only chars string
        if (nonTerminalIndex != -1) {
            char *partResult = generateWord(nonTerminalIndex);

            resultLength += strlen(partResult) - 1;
            addToList(rulePartResults, partResult);
        } else {
            char *partResult = malloc(sizeof(char) + 1);

            partResult[0] = rule[i];
            partResult[1] = '\0';

            addToList(rulePartResults, partResult);
        }
    }

    char *ruleResult = malloc(sizeof(char) * resultLength + 1);

    for (i = 0; i < rulePartResults -> items; i++) {
        char *partResult = (char*) getFromList(rulePartResults, i);

        strcpy(ruleResult + (sizeof(char) * resultShift), partResult);
        resultShift += strlen(partResult);
    }

    ruleResult[resultLength] = '\0';
    return ruleResult;
}

// Print grammar
void printGrammar(void) {
    int i;
    
    printf("  Terminal symbols:");
    for (i = 0; i < terminalSymbols -> items; i++) {
        printf(" %c", *((char*) getFromList(terminalSymbols, i)));

        if (i == terminalSymbols -> items - 1) {
            printf("\n");
        } else {
            printf(",");
        }
    }

    printf("  Non terminal symbols:");
    for (i = 0; i < nonTerminalSymbols -> items; i++) {
        printf(" %c", *((char*) getFromList(nonTerminalSymbols, i)));

        if (i == nonTerminalSymbols -> items - 1) {
            printf("\n");
        } else {
            printf(",");
        }
    }

    printf("  Rules: ");

    int hasPrintedAny = 0;
    for (i = 0; i < nonTerminalSymbols -> items; i++) {
        List *ruleList = rules[i];
        if (ruleList -> items == 0) {
            continue;
        }

        if (hasPrintedAny) {
            printf(", ");
        }

        printf("%c -> ", *((char*) getFromList(nonTerminalSymbols, i)));

        int j = 0;
        for (; j < ruleList -> items; j++) {
            printf("%s", (char*) getFromList(ruleList, j));

            if (j != ruleList -> items - 1) {
                printf("|");
            } 
        }

        hasPrintedAny = 1;
    }

    printf("\n  Start symbol: %c\n", startSymbol);
}