all: main.o
	gcc -o program main.o

main.o: main.c
	gcc -c main.c

clean:
	rm *.o 

run:
	./program
