#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



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

Stack* createStack(void){
	Stack* stiva=(Stack*)malloc(sizeof(Stack));
	stiva->head=NULL;
	stiva->size=0;
	return stiva;
}

int isStackEmpty(Stack* stack){
	if(stack->head==NULL)return 1;
	return 0;
}

void push(Stack *stack, Item elem){
	StackNode* newnode=(StackNode*)malloc(sizeof(StackNode));
	newnode->elem=elem;
	newnode->next=stack->head;
	stack->head=newnode;
	stack->size++;
}

Item top(Stack *stack){	
	return stack->head->elem;
} 

void pop(Stack *stack){
	StackNode* p=stack->head;
	stack->head=p->next;
	free(p);
	stack->size--;
}

void destroyStack(Stack *stack){
	while(stack->head!=NULL)pop(stack);
	free(stack);
}

#endif 
