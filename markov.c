//
// Created by gelin on 11/06/2025.
//

#include <stdlib.h>
#include <stdio.h>
#include "markov.h"

Markov createMarkov(unsigned int seed, unsigned int size) {
    srand(seed);
    Markov m = malloc(sizeof(markov));
    m->seed = seed;
    m->transition = malloc(sizeof(double*) * size);
    m->size = size;
    m->state = 0;
    for (int i = 0; i < m->size; i++) {
        m->transition[i] = malloc(sizeof(double) * size);
        for (int j = 0; j < m->size; j++) {
            m->transition[i][j] = 0.0; 
        }
    }
    return m;
}

void freeMarkov(Markov m) {
    for (int i = 0; i < m->size; i++) {
        free(m->transition[i]);
    }
    free(m->transition);
    free(m);
}

void addStates(Markov m, unsigned int numberOfStates) {
    unsigned int newSize = m->size + numberOfStates;

// Étendre les anciennes lignes
    for (unsigned int i = 0; i < m->size; i++) {
        m->transition[i] = realloc(m->transition[i], sizeof(double) * newSize);
        for (unsigned int j = m->size; j < newSize; j++) {
            m->transition[i][j] = 0.0;
        }
    }

// Étendre les lignes (nouvelles)
    m->transition = realloc(m->transition, sizeof(double*) * newSize);
    for (unsigned int i = m->size; i < newSize; i++) {
        m->transition[i] = malloc(sizeof(double) * newSize);
        for (unsigned int j = 0; j < newSize; j++) {
            m->transition[i][j] = 0.0;
        }
    }
    m->size = newSize;
}

void increaseState(Markov m, unsigned int from, unsigned int to) {
    if (from >= m->size || to >= m->size) {
        return; // Invalid state indices
    }
    m->transition[from][to]++;
}

void calcProbabilities(Markov m) {
    for (unsigned int i = 0; i < m->size; i++) {
        double sum = 0.0;
        for (unsigned int j = 0; j < m->size; j++) {
            sum += m->transition[i][j];
        }
        if (sum > 0) {
            for (unsigned int j = 0; j < m->size; j++) {
                m->transition[i][j] /= sum;
            }
        }
    }
}

int nextState(Markov m) {
    unsigned int count = 0;
    for (unsigned int i = 0; i < m->size; i++) {
        if (m->transition[m->state][i] > 0.0)
            count++;
    }

    if (count == 0) return m->state;

    unsigned int choice = rand() % count;
    unsigned int idx = 0;
    for (unsigned int i = 0; i < m->size; i++) {
        if (m->transition[m->state][i] > 0.0) {
            if (choice == 0) {
                m->state = i;
                return (int) i;
            }
            choice--;
        }
    }

    return -1;
}


void setState(Markov m, unsigned int state) {
    if (state >= m->size) {
        printf("Invalid state index\n");
        return;
    }
    m->state = state;
}

void printMarkov(Markov m) {
    for (unsigned int i = 0; i < m->size; i++) {
        for (unsigned int j = 0; j < m->size; j++) {
            printf("[%.2f] ", m->transition[i][j]);
        }
        printf("\n");
    }
}