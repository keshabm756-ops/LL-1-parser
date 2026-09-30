#include <stdio.h>

#include "grammar.h"
#include "first_follow.h"
#include "parse_table.h"
#include "predictive_parser.h"

int main()
{
    printf("\n");
    printf("====================================================================\n");
    printf("                 LL(1) PREDICTIVE PARSER GENERATOR\n");
    printf("====================================================================\n");

    inputGrammar();

    findNonTerminals();

    findTerminals();

    displayGrammar();

    calculateFirst();

    calculateFollow();

    displayFirst();

    displayFollow();

    createParseTable();

    displayParseTable();

    predictiveParse();

    printf("\n\n====================================================================\n");
    printf("                         PROGRAM FINISHED\n");
    printf("====================================================================\n");

    printf("\nPress ENTER to close...");

    getchar();
    getchar();

    return 0;
}