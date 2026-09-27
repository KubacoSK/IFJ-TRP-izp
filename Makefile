CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -I.

all: test

scanner.o: scanner.c scanner.h error.h
	$(CC) $(CFLAGS) -c scanner.c -o scanner.o

test: scanner.o tests/test_scanner.c
	$(CC) $(CFLAGS) scanner.o tests/test_scanner.c -o test_runner
	./test_runner
	@rm -f test_runner scanner.o

clean:
	rm -f *.o test_runner

.PHONY: all test clean
