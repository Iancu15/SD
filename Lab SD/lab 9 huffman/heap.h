#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>


/* We assume there is a defined primitive type Item. */

// typedef struct {
//     Item content;
//     int prior;
// } ItemType;

typedef struct heap {
    long int capacity;
    long int size;
    HuffmanNode *elem;
} PriQueue, *APriQueue;


APriQueue makeQueue(int capacity) {
    APriQueue h = (APriQueue) malloc(sizeof(APriQueue));
    h->elem = (HuffmanNode*) malloc(capacity * sizeof(HuffmanNode));
    h->capacity = capacity;
    h->size = 0;

    return h;
}

void freeQueue(APriQueue h){
	free(h->elem);
	free(h);
}

int getLeftChild(int i) {
    return 2 * i + 1;
}

int getRightChild(int i) {
    return 2 * i + 2;
}

int getParent(int i) {
    return floor((i - 1) / 2);
}

void siftUp(APriQueue h, int idx) {
    int parent = getParent(idx);

    while (parent >= 0 && h->elem[parent].prior > h->elem[idx].prior) {
        HuffmanNode aux = h->elem[parent];
        h->elem[parent] = h->elem[idx];
        h->elem[idx] = aux;

        idx = parent;
        parent = getParent(idx);
    }
}

void insert(APriQueue h, HuffmanNode x) {
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->elem = (HuffmanNode *) realloc(h->elem, h->capacity * sizeof(HuffmanNode));
    }

    h->elem[h->size] = x;
    h->size++;
    siftUp(h, h->size - 1);
}

HuffmanNode getMin(APriQueue h) {
    return h->elem[0];
}

void siftDown(APriQueue h, int idx) {
    int leftChild = getLeftChild(idx);
    int rightChild = getRightChild(idx);
    int smallest = idx;

    if (leftChild < h->size && h->elem[leftChild].prior < h->elem[smallest].prior) {
        smallest = leftChild;
    }

    if (rightChild < h->size && h->elem[rightChild].prior < h->elem[smallest].prior) {
        smallest = rightChild;
    }

    if (smallest != idx) {
        HuffmanNode aux = h->elem[smallest];
        h->elem[smallest] = h->elem[idx];
        h->elem[idx] = aux;

        /* Carry on. */
        siftDown(h, smallest);
    }
}

HuffmanNode removeMin(APriQueue h) {
    HuffmanNode max = getMin(h);
    HuffmanNode last = h->elem[h->size - 1];

    /* Remove the last elem from the vector. */
    h->size--;

    /* Set latest elem as the first and call heapify downwards. */
    h->elem[0] = last;
    siftDown(h, 0);

    return max;
}

#endif

