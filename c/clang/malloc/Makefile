CC = gcc
CFLAGS =-O0 -g -Wall

malloc: main.c malloc.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean

clean:
	rm -rf malloc *.o *.dSYM
