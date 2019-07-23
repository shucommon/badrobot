CC = gcc
CFLAGS = -O0 -g -Wall


minheap: minheap.c
	$(CC) $(CFLAGS) -o $@ $^ 

quicksort: quicksort.c
	$(CC) $(CFLAGS) -o $@ $^ 

.PHONY: clean
clean:
	@rm -rf *.o minheap minheap.dSYM quicksort quicksort.dSYM
