#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

typedef Queue TCoada;
typedef Queue *AQ;


Queue* createQueue(void){
	Queue* coada=(Queue*)malloc(sizeof(Queue));
	coada->front=NULL;
	coada->rear=NULL;
	coada->size=0;
	return coada;
} 

int isQueueEmpty(Queue *q){
	if(q->front==NULL)return 1;
	return 0;
}

void enqueue(Queue *q, Item elem){
	QueueNode* newnode=(QueueNode*)malloc(sizeof(QueueNode));
	newnode->elem=elem;
	newnode->next=NULL;
	if(q->rear==NULL){
		q->front=newnode;
		q->rear=newnode;
		q->size++;
	}else{
		q->rear->next=newnode;
		q->rear=newnode;
		q->size++;
	}
}

Item front(Queue* q){
	return q->front->elem;
}

void dequeue(Queue* q){
	if(q->front==q->rear){
		free(q->front);
		q->front=NULL;
		q->rear=NULL;
		q->size--;
	} else{
		QueueNode* p=q->front;
		q->front=p->next;
		free(p);
		q->size--;
	}
}

void destroyQueue(Queue *q){
	while(q->front!=NULL){
		dequeue(q);
	}
	free(q);
}

#endif
