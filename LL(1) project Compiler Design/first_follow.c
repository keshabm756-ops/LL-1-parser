#include <stdio.h>
#include "first_follow.h"

char first[MAX_SYMBOLS][MAX_SYMBOLS];
char follow[MAX_SYMBOLS][MAX_SYMBOLS];

int firstCount[MAX_SYMBOLS];
int followCount[MAX_SYMBOLS];

int getNonTerminalIndex(char symbol)
{
    for (int i = 0; i < nonTerminalCount; i++)
    {
        if (nonTerminals[i] == symbol)
        {
            return i;
        }
    }

    return -1;
}

void addToSet(char set[], int *count, char symbol)
{
    for (int i = 0; i < *count; i++)
    {
        if (set[i] == symbol)
        {
            return;
        }
    }

    set[(*count)++] = symbol;
}

void firstOfSymbol(
    char symbol,
    char result[],
    int *resultCount
)
{
    if (symbol == '#')
    {
        addToSet(result, resultCount, '#');
        return;
    }

    if (isTerminal(symbol))
    {
        addToSet(result, resultCount, symbol);
        return;
    }

    int index = getNonTerminalIndex(symbol);

    if (index == -1)
    {
        return;
    }

    for (int i = 0; i < productionCount; i++)
    {
        if (productions[i].lhs != symbol)
        {
            continue;
        }

        char *rhs = productions[i].rhs;

        if (rhs[0] == '#')
        {
            addToSet(result, resultCount, '#');
            continue;
        }

        int allNullable = 1;

        for (int j = 0; rhs[j] != '\0'; j++)
        {
            char temp[MAX_SYMBOLS];
            int tempCount = 0;

            firstOfSymbol(
                rhs[j],
                temp,
                &tempCount
            );

            int hasEpsilon = 0;

            for (int k = 0; k < tempCount; k++)
            {
                if (temp[k] == '#')
                {
                    hasEpsilon = 1;
                }
                else
                {
                    addToSet(
                        result,
                        resultCount,
                        temp[k]
                    );
                }
            }

            if (!hasEpsilon)
            {
                allNullable = 0;
                break;
            }
        }

        if (allNullable)
        {
            addToSet(result, resultCount, '#');
        }
    }
}

void calculateFirst()
{
    for (int i = 0; i < nonTerminalCount; i++)
    {
        firstCount[i] = 0;
    }

    for (int i = 0; i < nonTerminalCount; i++)
    {
        firstOfSymbol(
            nonTerminals[i],
            first[i],
            &firstCount[i]
        );
    }
}

void calculateFollow()
{
    for (int i = 0; i < nonTerminalCount; i++)
    {
        followCount[i] = 0;
    }

    int startIndex = getNonTerminalIndex(startSymbol);

    if (startIndex != -1)
    {
        addToSet(
            follow[startIndex],
            &followCount[startIndex],
            '$'
        );
    }

    int changed = 1;

    while (changed)
    {
        changed = 0;

        for (int i = 0; i < productionCount; i++)
        {
            char lhs = productions[i].lhs;
            char *rhs = productions[i].rhs;

            int lhsIndex = getNonTerminalIndex(lhs);

            for (int j = 0; rhs[j] != '\0'; j++)
            {
                char current = rhs[j];

                if (!isNonTerminal(current))
                {
                    continue;
                }

                int currentIndex =
                    getNonTerminalIndex(current);

                int nullable = 1;

                for (int k = j + 1; rhs[k] != '\0'; k++)
                {
                    char next = rhs[k];

                    char temp[MAX_SYMBOLS];
                    int tempCount = 0;

                    firstOfSymbol(
                        next,
                        temp,
                        &tempCount
                    );

                    int hasEpsilon = 0;

                    for (int x = 0; x < tempCount; x++)
                    {
                        if (temp[x] == '#')
                        {
                            hasEpsilon = 1;
                        }
                        else
                        {
                            int oldCount =
                                followCount[currentIndex];

                            addToSet(
                                follow[currentIndex],
                                &followCount[currentIndex],
                                temp[x]
                            );

                            if (oldCount !=
                                followCount[currentIndex])
                            {
                                changed = 1;
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
                    for (int x = 0;
                         x < followCount[lhsIndex];
                         x++)
                    {
                        int oldCount =
                            followCount[currentIndex];

                        addToSet(
                            follow[currentIndex],
                            &followCount[currentIndex],
                            follow[lhsIndex][x]
                        );

                        if (oldCount !=
                            followCount[currentIndex])
                        {
                            changed = 1;
                        }
                    }
                }
            }
        }
    }
}

void displayFirst()
{
    printf("\n\n============================================================\n");
    printf("                       FIRST SETS\n");
    printf("============================================================\n\n");

    for (int i = 0; i < nonTerminalCount; i++)
    {
        printf(" FIRST(%c) = { ",
               nonTerminals[i]);

        for (int j = 0; j < firstCount[i]; j++)
        {
            printf("%c ", first[i][j]);
        }

        printf("}\n");
    }
}

void displayFollow()
{
    printf("\n\n============================================================\n");
    printf("                      FOLLOW SETS\n");
    printf("============================================================\n\n");

    for (int i = 0; i < nonTerminalCount; i++)
    {
        printf(" FOLLOW(%c) = { ",
               nonTerminals[i]);

        for (int j = 0; j < followCount[i]; j++)
        {
            printf("%c ", follow[i][j]);
        }

        printf("}\n");
    }
}