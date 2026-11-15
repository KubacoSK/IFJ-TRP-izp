CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -I.

all: ifj26

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c -o utils.o

scanner.o: scanner.c scanner.h error.h
	$(CC) $(CFLAGS) -c scanner.c -o scanner.o

hashtable.o: hashtable.c hashtable.h utils.h
	$(CC) $(CFLAGS) -c hashtable.c -o hashtable.o

symtable.o: symtable.c symtable.h hashtable.h utils.h
	$(CC) $(CFLAGS) -c symtable.c -o symtable.o

codegen.o: codegen.c codegen.h symtable.h hashtable.h error.h utils.h
	$(CC) $(CFLAGS) -c codegen.c -o codegen.o

parser.o: parser.c parser.h scanner.h symtable.h codegen.h error.h
	$(CC) $(CFLAGS) -c parser.c -o parser.o

main.o: main.c parser.h symtable.h scanner.h codegen.h error.h
	$(CC) $(CFLAGS) -c main.c -o main.o

ifj26: main.o parser.o codegen.o scanner.o symtable.o hashtable.o utils.o
	$(CC) $(CFLAGS) main.o parser.o codegen.o scanner.o symtable.o hashtable.o utils.o -o ifj26

test_scanner: scanner.o tests/test_scanner.c
	$(CC) $(CFLAGS) scanner.o tests/test_scanner.c -o test_scanner_runner
	./test_scanner_runner
	@rm -f test_scanner_runner

test_ht: utils.o hashtable.o tests/test_hashtable.c
	$(CC) $(CFLAGS) utils.o hashtable.o tests/test_hashtable.c -o test_ht_runner
	./test_ht_runner
	@rm -f test_ht_runner

test_symtable: utils.o hashtable.o symtable.o tests/test_symtable.c
	$(CC) $(CFLAGS) utils.o hashtable.o symtable.o tests/test_symtable.c -o test_symtable_runner
	./test_symtable_runner
	@rm -f test_symtable_runner

test: test_scanner test_ht test_symtable

check: test
	
build-check: all check

clean:
	rm -f *.o ifj26 test_runner test_scanner_runner test_ht_runner test_symtable_runner

.PHONY: all test test_scanner test_ht test_symtable check build-check clean
