.PHONY:all
all: receve test

test:test.c
	gcc -o test test.c
receve:receve.c
	gcc -o receve receve.c

.PHONY clean:
	rm -rf receve test tmp
