/*
*	Created by Nan Mihai on 16.03.2017
*	Copyright (c) 2017 Nan Mihai. All rights reserved.
*	Laborator 4 - Structuri de date
*	Grupa 312CC
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2016-2017, Seria CC
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct point {
	int x, y;
} Point;

typedef Point T;

typedef struct queue {
	T *data;
	int capacity, size;
	int head, tail;
}*Queue;

Queue initQueue(int capacity);
Queue enqueue(Queue queue, T value);
int isEmpty(Queue queue);
Queue dequeue(Queue queue);
T first(Queue queue);
Queue freeQueue(Queue queue);
