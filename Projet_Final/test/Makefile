CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I. -g

OBJS = CuTest.o TestNeuralNet.o AllTests.o main.o neural_network.o

all: test

test: $(OBJS)
	$(CC) $(CFLAGS) -o test_runner $(OBJS) -lm

CuTest.o: CuTest.c CuTest.h
	$(CC) $(CFLAGS) -c CuTest.c

TestNeuralNet.o: TestNeuralNet.c neural_network.h CuTest.h
	$(CC) $(CFLAGS) -c TestNeuralNet.c

AllTests.o: AllTests.c CuTest.h TestNeuralNet.c
	$(CC) $(CFLAGS) -c AllTests.c

main.o: main.c CuTest.h
	$(CC) $(CFLAGS) -c main.c

neural_network.o: neural_network.c neural_network.h
	$(CC) $(CFLAGS) -c neural_network.c

clean:
	rm -f *.o test_runner
