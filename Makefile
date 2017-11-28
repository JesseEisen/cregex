CC=gcc
CFLAGS= -g -O2
SRC= ./src/cregex.c test.c
ESRC= ./src/cregex.c example.c
INC= -I./src/

test:
	$(CC) $(CFLAGS) $(SRC) $(INC) -o $@

example:
	$(CC) $(CFLAGS) $(INC) $(ESRC) -o $@

.PHONY=clean example
clean:
	-rm -f test example
