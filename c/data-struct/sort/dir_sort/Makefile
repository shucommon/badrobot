CFLAG=-c -Wall -g -I../

main: main.o common.o

main.o:
	gcc $(CFLAG) main.c

common.o:
	gcc $(CFLAG) ../common.c

.PHONY: clean
clean:
	rm *.o main
