CC=gcc
CFLAGS= -g -O2 -I./src/
SRC= ./src/cregex.c test.c
ESRC= ./src/cregex.c example.c
OBJ=$(ESRC:.c=.o)

test:
	$(CC) $(CFLAGS) $(SRC) -o $@

example: $(ESRC) $(OBJ)
	$(CC) $(CFLAGS) -o $@  $(OBJ)

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS)

.PHONY=clean example
clean:
	-rm -f test example
	-rm $(OBJ)
