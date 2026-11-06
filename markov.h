//
// Created by gelin on 11/06/2025.
//

#ifndef ECRIVAIN_NUMERIQUE_MARKOV_H
#define ECRIVAIN_NUMERIQUE_MARKOV_H

typedef struct {
    unsigned int seed;
    unsigned int size;
    double** transition;
    unsigned int state;
} markov, *Markov;

/**
 * @brief Creates and initializes a Markov object.
 *
 * This function allocates memory for a Markov object, sets its seed, initializes its
 * transition matrix with zeroes, and sets its initial state to 0. The random seed
 * for the Markov object is set using the provided `seed` parameter.
 *
 * @param seed The seed value used for random number generation.
 * @param size The size of the transition matrix (a square matrix with `size x size` dimensions).
 * @return A pointer to the newly created and initialized Markov object.
 *
 * @note The caller is responsible for freeing the allocated memory for the Markov object
 *       and its internal components when it is no longer needed.
 */
Markov createMarkov(unsigned int seed, unsigned int size);

/**
 * Frees all memory allocated for the given Markov structure.
 *
 * This function deallocates memory for the transition matrix
 * and the Markov structure itself. It is essential to call
 * this function to prevent memory leaks after the Markov object
 * is no longer needed.
 *
 * @param m A pointer to the Markov structure to be freed.
 */
void freeMarkov(Markov m);

/**
 * @brief Expands the number of states in the transition matrix of a Markov model.
 *
 * This function adds a specified number of new states to the transition matrix
 * of a given Markov model. The transition matrix is dynamically resized, and all
 * entries corresponding to the new states are initialized to 0.0. Both existing and
 * newly added rows and columns are updated accordingly.
 *
 * @param m Pointer to the Markov model whose states need to be expanded.
 * @param numberOfStates The number of new states to add to the Markov model.
 */
void addStates(Markov m, unsigned int numberOfStates);

/**
 * @brief Increments the transition count between two states in a Markov model.
 *
 * This function updates the transition matrix of the provided Markov model
 * by incrementing the transition count for a specific state transition
 * (from a source state to a target state). If either of the specified states
 * is outside the bounds of the model's size, the function performs no operation.
 *
 * @param m Pointer to the Markov structure containing the transition matrix.
 * @param from The index of the source state.
 * @param to The index of the target state.
 */
void increaseState(Markov m, unsigned int from, unsigned int to);

/**
 * Calculates and normalizes the transition probabilities for a Markov model.
 *
 * This function iterates through the transition matrix of the given Markov
 * structure and ensures that the probabilities in each row sum up to 1. If the
 * sum of probabilities in a row is greater than 0, each value in the row is
 * divided by the total sum to normalize it.
 *
 * The input Markov model, `m`, must contain valid data, including a non-NULL
 * transition matrix and a specified size.
 *
 * @param m A pointer to the Markov structure containing the transition matrix
 *          that will be normalized.
 */
void calcProbabilities(Markov m);

/**
 * Determines the next state of a given Markov chain based on its transition probabilities.
 *
 * The function simulates a random transition from the current state of the Markov chain
 * to the next state. It uses the transition matrix associated with the given Markov chain
 * struct to compute the next state probabilistically. The function assumes that the
 * transition probabilities for each state are normalized (i.e., they sum up to 1).
 *
 * The random number generator used is seeded as defined in the Markov struct.
 *
 * @param m A pointer to the Markov chain structure containing the current state,
 *          transition probabilities, and other data related to the Markov chain.
 *
 * @return The updated state of the Markov chain. If the probabilities are not
 *         properly normalized, the function may exhibit undefined behavior
 *         or return an invalid state.
 */
int nextState(Markov m);

/**
 * Sets the current state of the Markov model.
 *
 * This function updates the state of the given Markov model to the specified state index.
 * If the provided state index is out of bounds (greater than or equal to the size of the model),
 * it prints an error message and does not modify the state.
 *
 * @param m      A pointer to the Markov model whose state is to be updated.
 * @param state  The index of the state to set as the current state.
 */
void setState(Markov m, unsigned int state);

/**
 * @brief Prints the transition matrix of a Markov structure.
 *
 * This function iterates through the transition matrix of the provided
 * Markov structure and prints its elements in a formatted manner. Each
 * element of the matrix is printed with a precision of two decimal places.
 * The rows of the matrix are printed line by line.
 *
 * @param m Pointer to a Markov structure containing the transition matrix
 *          to be printed.
 */
void printMarkov(Markov m);

#endif //ECRIVAIN_NUMERIQUE_MARKOV_H
