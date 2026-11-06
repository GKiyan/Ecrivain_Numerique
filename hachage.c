//
// Created by gelin on 11/06/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hachage.h"

/**
 * @brief Creates a new linked list
 *
 * @return A pointer to the newly created linked list
 */
List newList() {
    return NULL;
}

/**
 * @brief Frees the memory used by a linked list
 *
 * @param L Pointer to the linked list to be freed
 */
void freeList(List L) {
    if (L == NULL) {
        free(L);
        return;
    }
    free(L->value);
    free(L->key);
    freeList(L->nextCell);
    free(L);
}

/**
 * @brief Prints the contents of a linked list
 *
 * @param L Pointer to the linked list to be printed
 * @param type If type==0, prints only the values, otherwise print the couples (key,vlaue)
 *
 * Prints the linked list in the following way if k!=0:
 * [(key 1, value 1),(key 2, value 2), … ,(key k, value k)]
 * Prints the linked list in the following way if k==0:
 * [value 1,value 2,…,value k]
 */

void printList(List L, int type) {
    List tmp = L;

    printf("[");
    if (L==NULL) {
        printf("]");
        return;
    }

    while (tmp->nextCell != NULL) {
        if (type == 0) {
            printf("%s,", tmp->value);
        }
        else {
            printf("(%s, %s),", tmp->key, tmp->value);
        }
        tmp = tmp->nextCell;
    }

    if (type == 0) {
        printf("%s", tmp->value);
    }
    else {
        printf("(%s, %s)", tmp->key, tmp->value);
    }

    printf("]");

}

/**
 * @brief Finds a key in a linked list
 *
 * @param L Pointer to the linked list to search in
 * @param key Key to search for
 *
 * @return A pointer to the first cell containing the key, or NULL if the key is not found
 */
Cell* findKeyInList(List L, string key) {
    Cell* tmp = L;
    while (tmp != NULL) {
        if (tmp->key == key
            || (tmp->key != NULL && key != NULL && strcmp(tmp->key, key) == 0)) {
            return tmp;
        }
        tmp = tmp->nextCell;
    }
    return NULL;
}

/**
 * @brief Deletes a key from a linked list
 *
 * @param L Pointer to the linked list to search in
 * @param key Key to delete
 *
 * @return A pointer to the modified linked list
 * Only the first occurrence of the key is deleted.
 */
List delKeyInList(List L, string key) {
    List tmp = L;
    List pred = NULL;
    while (tmp != NULL) {
        if (tmp->key == key || (tmp->key != NULL && key != NULL && strcmp(tmp->key, key) == 0)) {
            if (pred == NULL) L = tmp->nextCell;
            else pred->nextCell = tmp->nextCell;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
            return L;
        }
        pred = tmp;
        tmp = tmp->nextCell;
    }
    return L;
}

/**
 * @brief Adds a key-value pair to a linked list
 *
 * @param L Pointer to the linked list to add to
 * @param key Key to add
 * @param value Value to add
 *
 * @return A pointer to the modified linked list
 *
 * The key-value pair is added at the beginning of the list
 */

List addKeyValueInList(const List L, string key, string value) {
    const List cel = malloc(sizeof(Cell));
    cel->nextCell = L;
    if (key == NULL) {
        cel->key = key;
    }
    else {
        cel->key = malloc(strlen(key) + 1);
        strcpy(cel->key, key);
    }
    if (value == NULL) {
        cel->value = value;
    }
    else {
        cel->value = malloc(strlen(value) + 1);
        strcpy(cel->value, value);
    }
    return cel;
}



// HASHTABLES

HashTable createHashTable(unsigned int size) {
    HashTable ht = malloc(sizeof(hashTable));
    ht->size = size;
    ht->count = 0;
    ht->words = malloc(sizeof(List) * size);
    ht->indexs = malloc(sizeof(List) * size);
    for (unsigned int i = 0; i < size; i++) {
        ht->words[i] = newList();
        ht->indexs[i] = newList();
    }
    return ht;
}

void freeHashTable(HashTable ht) {
    for (unsigned int i = 0; i < ht->size; i++) {
        freeList(ht->words[i]);
        freeList(ht->indexs[i]);
    }
    free(ht->words);
    free(ht->indexs);
    free(ht);
}

unsigned int hash_function(unsigned char * key, unsigned int size) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return (unsigned int)( hash % size);
}

void doubleSizeHashTable(HashTable ht) {
    unsigned int newSize = ht->size * 2;
    List* newWords = malloc(sizeof(List) * newSize);
    List* newIndexs = malloc(sizeof(List) * newSize);
    for (unsigned int i = 0; i < newSize; i++) {
        newWords[i] = newList();
        newIndexs[i] = newList();
    }

    for (unsigned int i = 0; i < ht->size; i++) {
        List current = ht->words[i];
        List currentBis = ht->indexs[i];
        while (current != NULL) {
            unsigned int newIndex = hash_function((unsigned char *) current->key, newSize);
            newWords[newIndex] = addKeyValueInList(newWords[newIndex], current->key, current->value);
            current = current->nextCell;
        }
        while (currentBis != NULL) {
            unsigned int newIndex = hash_function((unsigned char *) currentBis->key, newSize);
            newIndexs[newIndex] = addKeyValueInList(newIndexs[newIndex], currentBis->key, currentBis->value);
            currentBis = currentBis->nextCell;
        }
        freeList(ht->words[i]);
        freeList(ht->indexs[i]);
    }
    ht->indexs = newIndexs;
    ht->words = newWords;
    ht->size = newSize;
}

void insertHashTableWithoutResizing(HashTable ht, string key, string value) {
    if (ht == NULL) {
        return;
    }
    unsigned int indexHash = hash_function((unsigned char *)key, ht->size);
    unsigned int wordHash = hash_function((unsigned char *)value, ht->size);
    if (findKeyInList(ht->words[indexHash], key) != NULL) {
        return;
    }
    if (findKeyInList(ht->indexs[wordHash], value) != NULL) {
        return;
    }
    ht->words[indexHash] = addKeyValueInList(ht->words[indexHash], key, value);
    ht->indexs[wordHash] = addKeyValueInList(ht->indexs[wordHash], value, key);
    ht->count++;
}

void insertHashTable(HashTable ht, string key, string value) {
    if (ht == NULL) {
        return;
    }
    if (ht->count >= ht->size * 0.75) { // Resize if load factor exceeds 0.75
        doubleSizeHashTable(ht);
    }
    insertHashTableWithoutResizing(ht, key, value);
}

string getWordFromIndex(HashTable ht, string index) {
    unsigned int indexHash = hash_function((unsigned char *)index, ht->size);
    Cell* cell = findKeyInList(ht->words[indexHash], index);
    if (cell != NULL) {
        return cell->value;
    }
    return NULL; // Key not found
}

string getIndexFromWord(HashTable ht, string word) {
    unsigned int wordHash = hash_function((unsigned char *)word, ht->size);
    Cell* cell = findKeyInList(ht->indexs[wordHash], word);
    if (cell != NULL) {
        return cell->key;
    }
    return NULL;
}

void printHashTable(HashTable ht) {
    for (unsigned int i = 0; i < ht->size; i++) {
        printf("List %d: ", i);
        printList(ht->words[i], 1);
        printf("\n");
    }
    printf("Index: ");
    for (unsigned int i = 0; i < ht->size; i++) {
        printf("List %d: ", i);
        printList(ht->indexs[i], 1);
        printf("\n");
    }
}



