# Nom du compilateur
CC = gcc

# Options de compilation (SDL2 inclus via sdl2-config)
CFLAGS = -Wall -Wextra -O2 -std=c11 $(shell sdl2-config --cflags)

# Options d'édition de liens : SDL2 et bibliothèque mathématique
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lm

# Liste des fichiers source
SRCS = main.c neural_network.c data.c sdl_display.c save.c ui_manager.c

# Génération des fichiers objets
OBJS = $(SRCS:.c=.o)

# Nom de l'exécutable final
EXEC = spirales

# Cible par défaut : construire l'exécutable
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

cleanid:
	find . -type f -name "*:Zone.Identifier" -exec rm -f {} +

clean:
	rm -f $(OBJS) $(EXEC) *.bin
	find . -type f -name "*:Zone.Identifier" -exec rm -f {} +
