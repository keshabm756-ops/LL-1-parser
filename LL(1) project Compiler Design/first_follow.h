#ifndef FIRST_FOLLOW_H
#define FIRST_FOLLOW_H

#include "grammar.h"

extern char first[MAX_SYMBOLS][MAX_SYMBOLS];
extern char follow[MAX_SYMBOLS][MAX_SYMBOLS];

extern int firstCount[MAX_SYMBOLS];
extern int followCount[MAX_SYMBOLS];

void calculateFirst();
void calculateFollow();

void displayFirst();
void displayFollow();

#endif