CC = gcc
CFLAGS = -O0 -g -Wall

.PHONY: all
all: minheap quicksort hash_table	

minheap: minheap.c
	$(CC) $(CFLAGS) -o $@ $^ 

quicksort: quicksort.c
	$(CC) $(CFLAGS) -o $@ $^ 

hash_table: hash_table.c
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean
clean:
	@rm -rf *.o minheap quicksort hash_table *.dSYM
