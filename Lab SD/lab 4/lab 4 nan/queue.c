/*
*	Created by Nan Mihai on 16.03.2017
*	Copyright (c) 2017 Nan Mihai. All rights reserved.
*	Laborator 4 - Structuri de date
*	Grupa 312CC
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2016-2017, Seria CC
*/

#include "queue.h"

Queue initQueue(int capacity) {
	Queue queue = (Queue) malloc(sizeof(struct queue));
	queue->head = queue->tail = 0;
	queue->size = 0;
	queue->capacity = capacity;
	queue->data = (T*) malloc(capacity*sizeof(T));
	return queue;
}

Queue enqueue(Queue queue, T value) {
	if(queue->capacity > queue->size) {
		//Adaug doar daca mai am loc
		queue->data[queue->tail] = value;
		queue->tail = (queue->tail + 1) % queue->capacity;
		queue->size++;
	}
	return queue;
}

int isEmpty(Queue queue) {
	if(queue->size == 0) {
		return 1;
	} else {
		return 0;
	}
}

Queue dequeue(Queue queue) {
	if(!isEmpty(queue)) {
		queue->head = (queue->head + 1) % queue->capacity;
		queue->size--;
	}
	return queue;
}

T first(Queue queue) {
	if(!isEmpty(queue)) {
		return queue->data[queue->head];
	} else {
		Point p;
		p.x = -1;
		p.y = -1;
		return p;
	}
}

Queue freeQueue(Queue queue) {
	free(queue->data);
	free(queue);
	return NULL;
}
