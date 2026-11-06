//
// Created by gelin on 11/06/2025.
//

#ifndef ECRIVAIN_NUMERIQUE_HACHAGE_H
#define ECRIVAIN_NUMERIQUE_HACHAGE_H

// words

/**
 * @brief Definition of the type string
 *
 */
typedef char *string;

/**
 * @brief Definition of a linked list cell and a linked list
 *
 * The structure contains the key (a string), the value (an integer),
 * and a pointer to the next cell in the list.
 * A linked list is just a pointer on the first cell (if it exists).
 */
typedef struct cell{
    string key; /**< Key of the cell */
    string value; /**< Value of the cell */
    struct cell *nextCell; /**< Pointer to the next cell in the list */
} Cell, *List;


/**
 * @brief Creates a new, empty linked list
 *
 * This function initializes a new linked list by returning a NULL pointer,
 * indicating the list is empty and does not contain any elements.
 *
 * @return A pointer to the newly created, empty linked list
 */
List newList();

/**
 * @brief Frees the memory allocated for a linked list
 *
 * This function deallocates the memory associated with every cell in the
 * linked list, including the dynamically allocated elements within each
 * cell, such as the key string. It ensures that no memory leaks occur
 * by recursively freeing every cell in the list starting from the head.
 *
 * @param L Pointer to the head of the linked list to be freed
 */
void freeList(List L);


/**
 * @brief Prints the contents of a linked list.
 *
 * This function iterates through the provided linked list and prints its content
 * in a formatted manner. The format of the output depends on the value of the
 * @p type parameter:
 * - If @p type is 0, only the values in the list are printed.
 * - If @p type is not 0, the key-value pairs of the list are printed.
 *
 * @param L Pointer to the head of the linked list to be printed.
 * @param type Specifies the format for printing:
 *      - 0: Outputs only the values.
 *      - Non-zero: Outputs key-value pairs.
 */

void printList(List L,int type);

/**
 * @brief Searches for a specific key in a linked list
 *
 * This function traverses through a linked list to locate the first cell
 * containing the specified key. It compares the given key with the key of
 * each cell in the list. If a match is found, a pointer to that cell is returned.
 * If the key is not found, the function returns NULL.
 *
 * @param L Pointer to the linked list where the search is performed
 * @param key The key to search for in the linked list
 *
 * @return A pointer to the cell containing the key if found, or NULL if not found
 */
Cell* findKeyInList(List L, string key);

/**
 * @brief Deletes the first occurrence of a key from a linked list.
 *
 * This function traverses the given linked list, searching for the first occurrence
 * of the specified key. If found, the corresponding cell is removed from the list,
 * the allocated memory for the key and the cell is freed, and the updated linked list
 * is returned. If the key is not found, the list remains unchanged.
 *
 * @param L Pointer to the head of the linked list from which the key should be removed.
 * @param key The key to search for and delete from the list.
 *
 * @return A pointer to the modified linked list, with the first occurrence of the key removed
 *         if found, or the original list if the key was not found.
 */
List delKeyInList(List L, string key);

/**
 * @brief Adds a key-value pair to a linked list
 *
 * This function creates a new cell containing the specified key-value pair
 * and inserts it at the beginning of the linked list.
 *
 * @param L Pointer to the linked list where the key-value pair will be added
 * @param key The string key to add to the list
 * @param value The integer value associated with the key
 * @return A pointer to the modified linked list with the new element added
 */
List addKeyValueInList(List L, string key, string value);

// HASHTABLES

typedef struct {
    unsigned int size;
    unsigned int count;
    List* words;
    List* indexs;
} hashTable;

typedef hashTable* HashTable;

/**
 * @brief Creates a hash table with the specified size.
 *
 * This function initializes a hash table, allocates memory for its
 * structure, and creates the necessary linked words for storing elements.
 * Each bucket in the hash table is represented by a linked list.
 *
 * @param size The number of buckets in the hash table.
 * @return A newly created hash table with the given size.
 */
HashTable createHashTable(unsigned int size);

/**
 * @brief Frees the memory used by the hash table and its associated resources.
 *
 * This function releases all memory allocated for the hash table, including
 * memory for the linked words at each bucket and the array storing the buckets.
 *
 * @param ht Pointer to the hash table to be freed.
 */
void freeHashTable(HashTable ht);

/**
 * @brief Computes a hash value for the given key using the djb2 algorithm.
 *
 * This function generates a hashed value for a given string key by applying the
 * djb2 hash algorithm, which is a widely used and efficient algorithm for hashing strings.
 * The resulting hash value is mapped into the range [0, size - 1].
 *
 * @param key A pointer to the unsigned char array (string) to be hashed.
 *            The key should be null-terminated.
 * @param size The size of the hash table or the range within which the hash result
 *             should fall.
 *
 * @return An unsigned integer denoting the hash value of the input key, modulo the
 *         specified size.
 */
unsigned int hash_function(unsigned char * key, unsigned int size);

/**
 * @brief Resizes a hash table to accommodate more elements
 *
 * This function doubles the size of the hash table and rehashes
 * all the existing elements to redistribute them evenly among the new buckets.
 *
 * @param ht Pointer to the hash table to be resized
 *
 * The function performs the following operations:
 * - Allocates new memory for the buckets based on the new size
 *   (double the existing size of the hash table).
 * - Initializes all the new buckets.
 * - Iterates through the existing buckets and rehashes each key-value pair
 *   into the new buckets using the hash function.
 * - Frees the memory used by the existing buckets.
 *
 * Postconditions:
 * - All elements in the hash table are reorganized according to the new size
 *   to maintain their integrity in the hash table structure.
 * - The hash table size will be updated to its new size.
 *
 * The function assumes the hash table and its buckets have been properly
 * initialized and contain valid data before resizing.
 */
void doubleSizeHashTable(HashTable ht);

/**
 * Inserts a key-value pair into the hash table.
 *
 * If the hash table's load factor exceeds 0.75, the table is resized
 * to accommodate additional entries. The resizing process increases the
 * size of the hash table and redistributes existing entries to the new
 * structure. After ensuring sufficient capacity, the specified key-value
 * pair is inserted into the hash table.
 *
 * Resolves collisions using an appropriate strategy (e.g., chaining).
 *
 * @param ht Pointer to the hash table where the key-value pair will be inserted.
 *           The hash table must be properly initialized before calling this function.
 * @param key The string key associated with the value. The key must be a valid,
 *            non-null, null-terminated string.
 * @param value The value to associate with the given key. This is stored as an
 *              unsigned integer in the hash table.
 */
void insertHashTable(HashTable ht, string key, string value);

/**
 * @brief Inserts a key-value pair into the hash table without resizing.
 *
 * @param ht The hash table in which the key-value pair should be inserted.
 * @param key The key to be inserted.
 * @param value The value associated with the key to be inserted.
 *
 * This function inserts a key-value pair into a hash table without performing
 * any resizing operations. The hash table must be initialized before calling
 * this function. The key is hashed using a hash function to determine the index
 * of the corresponding bucket. The key-value pair is then added to the bucket’s
 * linked list, and the count of items in the hash table is incremented.
 *
 * If the hash table pointer (ht) is NULL, the function does nothing.
 */
void insertHashTableWithoutResizing(HashTable ht, string key, string value);

/**
 * @brief Retrieves the value associated with a given key in a hash table.
 *
 * This function searches for the specified key within the hash table and
 * returns the corresponding value if the key exists. If the key is not
 * found, the function returns 0.
 *
 * @param ht The hash table to search in. It is assumed to be properly
 *           initialized and populated using other relevant functions
 *           like insertHashTableWithoutResizing.
 * @param key The key to look for in the hash table. It should be a
 *            null-terminated string.
 *
 * @return The value associated with the key if it exists. If the key
 *         is not found, the function returns -1.
 *
 * @note Collision resolution in the hash table is assumed to use
 *       chaining with linked words.
 * @warning The function does not validate input parameters, such as
 *          checking if `ht` or `key` is NULL.
 */
string getWordFromIndex(HashTable ht, string index);

string getIndexFromWord(HashTable ht, string word);

/**
 * @brief Prints the contents of a hash table.
 *
 * @param h The hash table to be printed.
 *
 * Each index of the hash table is printed along with the corresponding list
 * of key-value pairs or values stored at that index. The output format is:
 * List i: [(key 1, value 1), (key 2, value 2), ..., (key k, value k)], where `i`
 * is the index in the hash table.
 */
void printHashTable(HashTable h);

#endif //ECRIVAIN_NUMERIQUE_HACHAGE_H
