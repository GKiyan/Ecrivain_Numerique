//
// Created by gelin on 11/06/2025.
//

#include "repertoire.h"
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sauvegarde.h"
#include "hachage.h"

int initIterator(WordIterator *it, const char *path) {
    it->file = fopen(path, "r");
    if (!it->file) return 0;
    it->buffer[0] = '\0';
    it->pos = 0;
    it->bufferLen = 0;
    return 1;
}

void closeIterator(WordIterator *it) {
    if (it->file) fclose(it->file);
}

int nextWord(WordIterator *it, char *word, int *end) {
    int i = 0;
    *end = 0;

    while (1) {
        if (it->pos >= (int) it->bufferLen) {
            if (!fgets(it->buffer, sizeof(it->buffer), it->file)) return 0;
            it->bufferLen = strlen(it->buffer);
            it->pos = 0;
        }

        while (it->pos < (int) it->bufferLen) {
            char c = it->buffer[it->pos++];

            if (isalpha(c)) {
                word[i++] = (char) tolower(c);
            } else if (i > 0) {
                if (c == '.' || c == '?' || c == '!') {
                    *end = 1;
                }
                word[i] = '\0';
                return 1;
            } else if (c == '.' || c == '?' || c == '!') {
                *end = 1;
            }
        }

        if (i > 0) {
            word[i] = '\0';
            return 1;
        }
    }
}


char* intToString(int value) {
    // Alloue suffisamment de place pour un int en base 10 + signe + '\0'
    char* str = malloc(12 * sizeof(char));
    if (str == NULL) return NULL; // Vérifie l'allocation
    sprintf(str, "%d", value);
    return str;
}

int stringToInt(char* str) {
    return atoi(str);
}

Markov generateMarkov(const char *path, HashTable ht) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return NULL;
    }

    Markov m = createMarkov(time(NULL), 50);
    unsigned int i = 1;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        char * fullPath = malloc(strlen(path) + strlen(entry->d_name) + 2);
        strcpy(fullPath, path);
        strcat(fullPath, "/");
        strcat(fullPath, entry->d_name);

        WordIterator wordIterator;
        initIterator(&wordIterator, fullPath);
        int predecessor = 0;
        char word[100];
        int end;
        while (nextWord(&wordIterator, word, &end)) {
            int index;
            char* keyStr = intToString(i);
            if (getWordFromIndex(ht, keyStr) == NULL && getIndexFromWord(ht, word) == NULL) {
                insertHashTable(ht, keyStr, word);
                index = i;
                if (m->size <= i) {
                    addStates(m, 50);
                }
                i++;
            }
            else {
                index = stringToInt(getIndexFromWord(ht, word));
            }

            increaseState(m, predecessor, index);
            predecessor = index;
            free(keyStr);
        }
        printf("%s\n", fullPath);

        closeIterator(&wordIterator);
        free(fullPath);
    }

    calcProbabilities(m);
    closedir(dir);
    return m;
}
