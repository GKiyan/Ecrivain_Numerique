# Ecrivain Numerique

A "digital writer" in C: it learns from a set of French texts and generates new text with a Markov chain.

## How it works

1. **Reading**: every text file in the input folder is read word by word.
2. **Indexing**: each distinct word gets an index, stored in a custom hash table (separate chaining with linked lists).
3. **Learning**: word-to-word transitions are recorded in the transition matrix of a Markov chain.
4. **Generating**: starting from a state, the chain picks the next word at random among the observed successors. The text is printed and written to `text.txt`.

## Project structure

| File | Role |
|---|---|
| `main.c` | Entry point: builds the model and generates text |
| `markov.c/.h` | Markov chain (transition matrix, state, next-state picking) |
| `hachage.c/.h` | Hash table and linked lists (word ↔ index) |
| `repertoire.c/.h` | Folder reading, word iterator, model building |
| `sauvegarde.c/.h` | Writing the generated text to a file |
| `datatxt/` | Default input corpus (a short poem) |
| `dataset/` | Larger French corpora (Hugo, Stendhal, Gide, Loti, Molière, ...) |

## Build and run

Requires a C compiler and `make`.

```bash
make
./main
```

The program reads the texts in `datatxt/` and generates text until you stop it (`Ctrl+C`). To train on a larger corpus, copy files from `dataset/` into `datatxt/`, or change the folder passed to `generateMarkov` in `main.c`.

Other targets: `make clean` (remove object files), `make fclean` (also remove the executable), `make re` (rebuild everything).
