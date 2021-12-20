all: lab3

lab3: DoubleLinkedList.o main.c
	gcc main.c DoubleLinkedList.o -o lab3 -g

DoubleLinkedList.o: DoubleLinkedList.c DoubleLinkedList.h
	gcc -c DoubleLinkedList.c -g

clean:
	rm -f *.o *~ lab3
