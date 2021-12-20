#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>


/* We assume there is a defined primitive type Item. */

typedef struct {
    Item content;
    int prior; /* You will compare elements based on this. */
} ItemType;

typedef struct heap {
    long int capacity;
    long int size;
    ItemType *elem;
} PriQueue, *APriQueue;


APriQueue makeQueue(int capacity) {
	if(capacity <= 0){
		printf("ERROR\n");
		return NULL;
	}

	APriQueue heap = (APriQueue)malloc(sizeof(PriQueue));
	if(!heap)exit(1);

	heap->capacity = capacity;
	heap->size = 0;

	heap->elem = (ItemType*)malloc(sizeof(ItemType) * capacity);
	if(!heap->elem)exit(1);

	return heap;
}

int getLeftChild(int i) {
	return 2*i;
}

int getRightChild(int i) {
	return 2*i + 1;
}

int getParent(int i) {
	return i/2;
}

ItemType getMax(APriQueue h) {
	return h->elem[1];
}

void siftUp(APriQueue h, int idx) {
	if(idx > 1 && h->elem[idx/2].prior < h->elem[idx].prior){
		ItemType aux = h->elem[idx/2];
		h->elem[idx/2] = h->elem[idx];
		h->elem[idx] = aux;
		siftUp(h, idx/2);
	}
}

void insert(APriQueue h, ItemType x) {
	if(h->size == h->capacity){
		h->capacity *= 2;
		//ItemType* z = realloc(h->elem, h->capacity);
		//if(!z)exit(1);
		//h->elem = z;
		h->elem = (ItemType*)realloc(h->elem, h->capacity);
	}

	h->elem[++h->size] = x;
	siftUp(h, h->size);
}

void siftDown(APriQueue h, int idx) {
	ItemType aux;
	int l = 2*idx;
	int r = 2*idx + 1;
	if(l <= h->size && h->elem[l].prior > h->elem[idx].prior){
		if(r <= h->size && h->elem[r].prior > h->elem[l].prior){
			aux = h->elem[idx];
			h->elem[idx] = h->elem[r];
			h->elem[r] = aux;

			siftDown(h, r);
		} else{
			aux = h->elem[idx];
			h->elem[idx] = h->elem[l];
			h->elem[l] = aux;

			siftDown(h, l);
		}
	}
}

ItemType removeMax(APriQueue h) {
	ItemType max = h->elem[1];
	h->elem[1] = h->elem[h->size];
	h->size--;
	siftDown(h, 1);

	return max;
}

#endif

