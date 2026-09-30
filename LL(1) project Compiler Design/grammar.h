#ifndef GRAMMAR_H
#define GRAMMAR_H

#define MAX_PRODUCTIONS 50
#define MAX_SYMBOLS 50
#define MAX_LENGTH 100

typedef struct
{
    char lhs;
    char rhs[MAX_LENGTH];
} Production;

extern Production productions[MAX_PRODUCTIONS];
extern int productionCount;

extern char nonTerminals[MAX_SYMBOLS];
extern int nonTerminalCount;

extern char terminals[MAX_SYMBOLS];
extern int terminalCount;

extern char startSymbol;

void inputGrammar();
void findNonTerminals();
void findTerminals();
void displayGrammar();

int isNonTerminal(char symbol);
int isTerminal(char symbol);

#endif