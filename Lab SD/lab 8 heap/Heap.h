#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize){
	if(maxHeapSize <= 0){
		printf("ERROR\n");
		return NULL;
	}

	APriQueue heap = (APriQueue)malloc(sizeof(PriQueue));
	if(!heap)exit(1);

	heap->maxHeapSize = maxHeapSize;
	heap->size = 0;

	heap->elem = (ItemType*)malloc(sizeof(ItemType) * maxHeapSize);
	if(!heap->elem)exit(1);

	return heap;
}

int getLeftChild(int i){
	return 2*i + 1;
}

int getRightChild(int i) {
	return 2*i + 2;
}

int getParent(int i) {
	return (i - 1)/2;
}

ItemType getMax(APriQueue h) {
	return h->elem[0];
}

void siftUp(APriQueue h, int idx) {
	int p = getParent(idx);
	if(idx > -1 && h->elem[p].prior < h->elem[idx].prior){
		ItemType aux = h->elem[p];
		h->elem[p] = h->elem[idx];
		h->elem[idx] = aux;
		siftUp(h, p);
	}
}


void insert(PriQueue *h, ItemType x) {
	if(h->size == h->maxHeapSize){
		h->maxHeapSize *= 2;
		//ItemType* z = realloc(h->elem, h->capacity);
		//if(!z)exit(1);
		//h->elem = z;
		h->elem = (ItemType*)realloc(h->elem, h->maxHeapSize);
	}

	h->elem[h->size] = x;
	siftUp(h, h->size);
	h->size++;
}

void siftDown(APriQueue h, int idx){
	ItemType aux;
	int l = getLeftChild(idx);
	int r = getRightChild(idx);
	if(l < h->size && h->elem[l].prior > h->elem[idx].prior){
		if(r < h->size && h->elem[r].prior > h->elem[l].prior){
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

void removeMax(APriQueue h) {
	ItemType max = h->elem[0];
	h->elem[0] = h->elem[--h->size];
	siftDown(h, 0);
}

void freeQueue(APriQueue h){
	free(h->elem);
	free(h);
}

#endif

