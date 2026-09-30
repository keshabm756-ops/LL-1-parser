#include <stdio.h>
#include <string.h>
#include "predictive_parser.h"

void predictiveParse()
{
    char input[MAX_LENGTH];

    printf("\n\n============================================================\n");
    printf("                     INPUT STRING\n");
    printf("============================================================\n\n");

    printf("Enter input string: ");
    scanf("%s", input);

    strcat(input, "$");

    char stack[MAX_LENGTH];

    int top = 0;

    stack[top++] = '$';
    stack[top++] = startSymbol;

    int inputIndex = 0;

    while (top > 0)
    {
        char topSymbol = stack[top - 1];
        char currentInput = input[inputIndex];

        if (topSymbol == '$' &&
            currentInput == '$')
        {
            printf("\n------------------------------------------------------------\n");
            printf("                  INPUT STRING ACCEPTED\n");
            printf("------------------------------------------------------------\n");

            return;
        }

        if (topSymbol == currentInput)
        {
            top--;
            inputIndex++;

            continue;
        }

        if (!isNonTerminal(topSymbol))
        {
            printf("\n------------------------------------------------------------\n");
            printf("                  INPUT STRING REJECTED\n");
            printf("------------------------------------------------------------\n");

            return;
        }

        int row = -1;
        int column = -1;

        for (int i = 0; i < nonTerminalCount; i++)
        {
            if (nonTerminals[i] == topSymbol)
            {
                row = i;
                break;
            }
        }

        for (int i = 0; i < terminalCount; i++)
        {
            if (terminals[i] == currentInput)
            {
                column = i;
                break;
            }
        }

        if (row == -1 ||
            column == -1 ||
            strlen(parseTable[row][column]) == 0)
        {
            printf("\n------------------------------------------------------------\n");
            printf("                  INPUT STRING REJECTED\n");
            printf("------------------------------------------------------------\n");

            return;
        }

        char production[MAX_LENGTH];

        strcpy(
            production,
            parseTable[row][column]
        );

        top--;

        char *rhs =
            strchr(production, '>');

        if (rhs != NULL)
        {
            rhs++;

            if (rhs[0] != '#')
            {
                int length = strlen(rhs);

                for (int i = length - 1;
                     i >= 0;
                     i--)
                {
                    if (top < MAX_LENGTH - 1)
                    {
                        stack[top++] = rhs[i];
                    }
                }
            }
        }
    }

    printf("\n------------------------------------------------------------\n");
    printf("                  INPUT STRING REJECTED\n");
    printf("------------------------------------------------------------\n");
}