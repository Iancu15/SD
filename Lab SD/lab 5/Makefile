all: lab5

lab5: tree.o main.c
	gcc main.c tree.o -o lab5 -g

tree.o: tree.c tree.h
	gcc -c tree.c -g

clean:
	rm -f *.o *~ lab5
