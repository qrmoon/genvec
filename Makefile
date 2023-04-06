CC=clang
CFLAGS=$(shell cat compile_flags.txt)
LFLAGS=

all: example

example: example.c vector.h
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(word 1,$^)

run: example
	./example

clean:
	rm example
