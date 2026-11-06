#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "hachage.h"
#include "markov.h"
#include "repertoire.h"
#include "sauvegarde.h"

int main() {

    /*
    Markov m = createMarkov(time(NULL), 10);
    increaseState(m, 0, 1);
    increaseState(m, 0, 2);
    increaseState(m, 0, 3);
    increaseState(m, 0, 4);
    calcProbabilities(m);
    unsigned int i = 0;
    i = nextState(m);
    printf("Next state: %d\n", i);
    printMarkov(m);
    */

    /*
    List l = newList();
    l = addKeyValueInList(l, "key1", "1");
    l = addKeyValueInList(l, "key2", "2");
    l = addKeyValueInList(l, "key3", "3");
    printf("List: ");
    printList(l, 1);
    freeList(l);
    printf("\n");

    HashTable ht = createHashTable(10);
    insertHashTable(ht, "key1", "1");
    insertHashTable(ht, "key2", "2");
    insertHashTable(ht, "key3", "3");
    insertHashTable(ht, "key4", "4");
    insertHashTable(ht, "key5", "5");
    insertHashTable(ht, "key6", "6");
    insertHashTable(ht, "key7", "7");
    printHashTable(ht);

    printf("\n");
    insertHashTable(ht, "key8", "8");
    insertHashTable(ht, "key9", "9");
    insertHashTable(ht, "key10", "10");
    insertHashTable(ht, "key11", "11");
    printHashTable(ht);
    freeHashTable(ht);
    */
    HashTable ht = createHashTable(50);
    Markov m = generateMarkov("datatxt", ht);
    //printf("HT:");
    //printHashTable(ht);
    //printf("Markov:");
    //printMarkov(m);

    printf("ICI\n");

    saveText("text.txt", "");
    int fd = openFileConcat("text.txt");
    int state = 0;
    printHashTable(ht);
    while (state >= 0){
        state = nextState(m);
        //printf("\n%d ", state);
        if (state == 0) {
            addText(fd, ". ");
            printf(". ");
            continue;
        }
        addText(fd, getWordFromIndex(ht, intToString(state)));
        addText(fd, " ");
        printf(" %s", getWordFromIndex(ht, intToString(state)));
    }

    return 0;
}