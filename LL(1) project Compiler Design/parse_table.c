#include <stdio.h>
#include <string.h>
#include "parse_table.h"

char parseTable[MAX_TABLE][MAX_TABLE][MAX_LENGTH];

int getTerminalIndex(char symbol)
{
    for (int i = 0; i < terminalCount; i++)
    {
        if (terminals[i] == symbol)
        {
            return i;
        }
    }

    return -1;
}

int contains(char set[], int count, char symbol)
{
    for (int i = 0; i < count; i++)
    {
        if (set[i] == symbol)
        {
            return 1;
        }
    }

    return 0;
}

void firstOfString(
    char rhs[],
    char result[],
    int *resultCount
)
{
    int nullable = 1;

    for (int i = 0; rhs[i] != '\0'; i++)
    {
        char symbol = rhs[i];

        if (symbol == '#')
        {
            if (!contains(result, *resultCount, '#'))
            {
                result[(*resultCount)++] = '#';
            }

            return;
        }

        if (isTerminal(symbol))
        {
            if (!contains(result, *resultCount, symbol))
            {
                result[(*resultCount)++] = symbol;
            }

            nullable = 0;
            break;
        }

        int index = -1;

        for (int j = 0; j < nonTerminalCount; j++)
        {
            if (nonTerminals[j] == symbol)
            {
                index = j;
                break;
            }
        }

        if (index == -1)
        {
            nullable = 0;
            break;
        }

        int hasEpsilon = 0;

        for (int j = 0; j < firstCount[index]; j++)
        {
            char f = first[index][j];

            if (f == '#')
            {
                hasEpsilon = 1;
            }
            else
            {
                if (!contains(result, *resultCount, f))
                {
                    result[(*resultCount)++] = f;
                }
            }
        }

        if (!hasEpsilon)
        {
            nullable = 0;
            break;
        }
    }

    if (nullable)
    {
        if (!contains(result, *resultCount, '#'))
        {
            result[(*resultCount)++] = '#';
        }
    }
}

void createParseTable()
{
    for (int i = 0; i < MAX_TABLE; i++)
    {
        for (int j = 0; j < MAX_TABLE; j++)
        {
            parseTable[i][j][0] = '\0';
        }
    }

    for (int p = 0; p < productionCount; p++)
    {
        char lhs = productions[p].lhs;
        char *rhs = productions[p].rhs;

        char firstSet[MAX_SYMBOLS];
        int firstSetCount = 0;

        firstOfString(
            rhs,
            firstSet,
            &firstSetCount
        );

        int lhsIndex = -1;

        for (int i = 0; i < nonTerminalCount; i++)
        {
            if (nonTerminals[i] == lhs)
            {
                lhsIndex = i;
                break;
            }
        }

        if (lhsIndex == -1)
        {
            continue;
        }

        for (int i = 0; i < firstSetCount; i++)
        {
            char symbol = firstSet[i];

            if (symbol == '#')
            {
                continue;
            }

            int terminalIndex =
                getTerminalIndex(symbol);

            if (terminalIndex != -1)
            {
                snprintf(
                    parseTable[lhsIndex][terminalIndex],
                    MAX_LENGTH,
                    "%c->%s",
                    lhs,
                    rhs
                );
            }
        }

        if (contains(
                firstSet,
                firstSetCount,
                '#'))
        {
            for (int i = 0;
                 i < followCount[lhsIndex];
                 i++)
            {
                char symbol =
                    follow[lhsIndex][i];

                int terminalIndex =
                    getTerminalIndex(symbol);

                if (terminalIndex != -1)
                {
                    snprintf(
                        parseTable[lhsIndex][terminalIndex],
                        MAX_LENGTH,
                        "%c->%s",
                        lhs,
                        rhs
                    );
                }
            }
        }
    }
}

int getProductionNumber(const char *production)
{
    for (int i = 0; i < productionCount; i++)
    {
        char productionText[MAX_LENGTH];

        snprintf(
            productionText,
            MAX_LENGTH,
            "%c->%s",
            productions[i].lhs,
            productions[i].rhs
        );

        if (strcmp(
                production,
                productionText) == 0)
        {
            return i + 1;
        }
    }

    return 0;
}

void displayParseTable()
{
    printf("\n\n");
    printf("====================================================================\n");
    printf("                         LL(1) PARSE TABLE\n");
    printf("====================================================================\n\n");

    printf("Production Numbers:\n\n");

    for (int i = 0; i < productionCount; i++)
    {
        printf(" %2d. %c -> %s\n",
               i + 1,
               productions[i].lhs,
               productions[i].rhs);
    }

    printf("\n");

    printf("+------------");

    for (int i = 0; i < terminalCount; i++)
    {
        printf("+--------");
    }

    printf("+\n");

    printf("| %-10s ", "");

    for (int i = 0; i < terminalCount; i++)
    {
        printf("| %-6c ", terminals[i]);
    }

    printf("|\n");

    printf("+------------");

    for (int i = 0; i < terminalCount; i++)
    {
        printf("+--------");
    }

    printf("+\n");

    for (int i = 0; i < nonTerminalCount; i++)
    {
        printf("| %-10c ", nonTerminals[i]);

        for (int j = 0; j < terminalCount; j++)
        {
            if (strlen(parseTable[i][j]) == 0)
            {
                printf("| %-6s ", "");
            }
            else
            {
                int productionNumber =
                    getProductionNumber(
                        parseTable[i][j]
                    );

                printf("| %-6d ", productionNumber);
            }
        }

        printf("|\n");

        printf("+------------");

        for (int j = 0; j < terminalCount; j++)
        {
            printf("+--------");
        }

        printf("+\n");
    }

    printf("\n====================================================================\n");
}