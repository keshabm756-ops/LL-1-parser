#include <stdio.h>
#include <string.h>
#include "grammar.h"

Production productions[MAX_PRODUCTIONS];
int productionCount = 0;

char nonTerminals[MAX_SYMBOLS];
int nonTerminalCount = 0;

char terminals[MAX_SYMBOLS];
int terminalCount = 0;

char startSymbol;

int isNonTerminal(char symbol)
{
    for (int i = 0; i < nonTerminalCount; i++)
    {
        if (nonTerminals[i] == symbol)
        {
            return 1;
        }
    }

    return 0;
}

int isTerminal(char symbol)
{
    if (symbol == '#')
    {
        return 0;
    }

    return !isNonTerminal(symbol);
}

void inputGrammar()
{
    int n;

    printf("\n============================================================\n");
    printf("                    GRAMMAR INPUT\n");
    printf("============================================================\n");

    printf("\nEnter number of productions: ");
    scanf("%d", &n);

    productionCount = 0;

    printf("\nEnter productions:\n");
    printf("Example: E=TQ\n");
    printf("Use | for alternatives\n");
    printf("Use # for epsilon\n\n");

    for (int i = 0; i < n; i++)
    {
        char input[MAX_LENGTH];

        printf("Production %d: ", i + 1);
        scanf("%s", input);

        char lhs = input[0];

        if (i == 0)
        {
            startSymbol = lhs;
        }

        char *equalSign = strchr(input, '=');

        if (equalSign == NULL)
        {
            printf("Invalid production. Try again.\n");
            i--;
            continue;
        }

        char *rhs = equalSign + 1;

        char *alternative = strtok(rhs, "|");

        while (alternative != NULL)
        {
            if (productionCount < MAX_PRODUCTIONS)
            {
                productions[productionCount].lhs = lhs;

                strcpy(
                    productions[productionCount].rhs,
                    alternative
                );

                productionCount++;
            }

            alternative = strtok(NULL, "|");
        }
    }
}

void findNonTerminals()
{
    nonTerminalCount = 0;

    for (int i = 0; i < productionCount; i++)
    {
        char lhs = productions[i].lhs;

        int exists = 0;

        for (int j = 0; j < nonTerminalCount; j++)
        {
            if (nonTerminals[j] == lhs)
            {
                exists = 1;
                break;
            }
        }

        if (!exists)
        {
            nonTerminals[nonTerminalCount++] = lhs;
        }
    }
}

void findTerminals()
{
    terminalCount = 0;

    for (int i = 0; i < productionCount; i++)
    {
        char *rhs = productions[i].rhs;

        for (int j = 0; rhs[j] != '\0'; j++)
        {
            char symbol = rhs[j];

            if (symbol == '#')
            {
                continue;
            }

            if (!isNonTerminal(symbol))
            {
                int exists = 0;

                for (int k = 0; k < terminalCount; k++)
                {
                    if (terminals[k] == symbol)
                    {
                        exists = 1;
                        break;
                    }
                }

                if (!exists)
                {
                    terminals[terminalCount++] = symbol;
                }
            }
        }
    }

    int dollarExists = 0;

    for (int i = 0; i < terminalCount; i++)
    {
        if (terminals[i] == '$')
        {
            dollarExists = 1;
            break;
        }
    }

    if (!dollarExists)
    {
        terminals[terminalCount++] = '$';
    }
}

void displayGrammar()
{
    printf("\n\n============================================================\n");
    printf("                    GRAMMAR DETAILS\n");
    printf("============================================================\n\n");

    printf("Productions:\n\n");

    for (int i = 0; i < productionCount; i++)
    {
        printf(" %2d. %c -> %s\n",
               i + 1,
               productions[i].lhs,
               productions[i].rhs);
    }

    printf("\nNon-Terminals : ");

    for (int i = 0; i < nonTerminalCount; i++)
    {
        printf("%c ", nonTerminals[i]);
    }

    printf("\n");

    printf("Terminals     : ");

    for (int i = 0; i < terminalCount; i++)
    {
        printf("%c ", terminals[i]);
    }

    printf("\n");

    printf("Start Symbol  : %c\n", startSymbol);
}