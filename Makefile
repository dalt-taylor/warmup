CC = gcc
CFLAGS = -D_XOPEN_SOURCE=700 -Og -g -std=c11 -Wall -pedantic -fsanitize=address
LDFLAGS = -fsanitize=address

all: split

split: split.o main.o
	$(CC) $(CFLAGS) -o split split.o main.o $(LDFLAGS)

split.o: split.c split.h
	$(CC) $(CFLAGS) -c split.c

main.o: main.c split.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o split
