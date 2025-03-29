# Répertoire source
SRC_DIR = src

# Fichiers sources
SRC = $(SRC_DIR)/neural_network.c $(SRC_DIR)/data.c
BENCH = benchmark.c

# Nom de l'exécutable
BENCH_EXE = run_bench

# Options
CFLAGS = -Wall -Wextra -O2 -I$(SRC_DIR)
LIBS = -lm

# Compilateur
CC = gcc

# Règle de compilation
all: $(BENCH_EXE)

$(BENCH_EXE): $(SRC) $(BENCH)
	$(CC) $(CFLAGS) $(SRC) $(BENCH) -o $@ $(LIBS)

run-bench: $(BENCH_EXE)
	./$(BENCH_EXE)

clean:
	rm -f *.o $(BENCH_EXE)
