all: lab6

lab6: tree.o main.c
	gcc main.c tree.o -o lab6 -g

tree.o: tree.c tree.h
	gcc -c tree.c -g

clean:
	rm -f *.o *~ lab6 rm *.dot
