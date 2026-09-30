#ifndef PARSE_TABLE_H
#define PARSE_TABLE_H

#include "grammar.h"
#include "first_follow.h"

#define MAX_TABLE 50

extern char parseTable[MAX_TABLE][MAX_TABLE][MAX_LENGTH];

void createParseTable();
void displayParseTable();

#endif