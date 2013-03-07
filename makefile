SHELL = /bin/bash

main.out: main.c
	mpicc -std=c99 -o main.out main.c

clean:
	rm -f main.out
