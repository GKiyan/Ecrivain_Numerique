//
// Created by gelin on 11/06/2025.
//

#ifndef ECRIVAIN_NUMERIQUE_REPERTOIRE_H
#define ECRIVAIN_NUMERIQUE_REPERTOIRE_H


#include <stdio.h>
#include "markov.h"
#include "hachage.h"

typedef struct {
    FILE *file;
    char buffer[1024];
    int pos;
    size_t bufferLen;
} WordIterator;

int initIterator(WordIterator *it, const char *path);
int nextWord(WordIterator *it, char *word, int *end);
void closeIterator(WordIterator *it);

char* intToString(int value);
int stringToInt(char* str);
Markov generateMarkov(const char * path, HashTable ht);

#endif //ECRIVAIN_NUMERIQUE_REPERTOIRE_H
