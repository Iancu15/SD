/*
 * Util.h
 *
 *  Created on: May 3, 2016
 *      Author: dan
 */

#ifndef UTIL_H_
#define UTIL_H_

%%%%%%%%%%%
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
%%%%%%%%%%%%%%%
typedef struct StackNode{
	Item elem;
	struct StackNode *next;
}StackNode;

typedef StackNode TCelSt; // Redenumirea unui nod la notatiile din curs 
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
}Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;//  // Redenumirea unui pointer la stiva la notatiile din curs
%%%%%%%%%%%%%%%%%%%%

typedef struct ListNode{
	int key;
	struct ListNode *next;
	struct ListNode *prev;
}ListNode;

typedef struct List{
	ListNode* head;
}List;

typedef List Stack;
typedef List Queue;

List* createList(void);
void destroyList(List* list);
int isListEmpty(List *list);

Stack* createStack(void);
void destroyStack(Stack* stack);
void push(Stack* stack, int key);
void pop(Stack* stack);
int isStackEmpty(Stack* stack);
int top(Stack* stack);


Queue* createQueue(void);
void destroyQueue(Queue* queue);
void enqueue(Queue* queue, int key);
void dequeue(Queue* queue);
int isQueueEmpty(Queue *queue);
int front(Queue* queue);

#endif /* UTIL_H_ */
