# Nom de l'exécutable
EXEC = main

# Liste des fichiers sources
SRCS = main.c hachage.c markov.c repertoire.c sauvegarde.c

# Obtenir la liste des fichiers objets en remplaçant .c par .o
OBJS = $(SRCS:.c=.o)

# Options du compilateur
CFLAGS = -Wall -Wextra -std=c99 -g

# Compilation
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Règle générique pour compiler les fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

# Recompiler entièrement
re: fclean $(EXEC)

.PHONY: clean fclean re
