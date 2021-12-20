#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
/*
*	Created by Nan Mihai on 03.03.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 3 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 	100

typedef int T;

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode {
	T value; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List {
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
} List;

ListNode *createListNode(T value);
List createList(T value);
List nill(void);
int isEmpty(List list);
List insertAt(List list, T value, int pos);
int contains(List list, T value);
List deleteOnce(List list, T value);
int length(List list);
List destroyList(List list);
int isPalindrome(List list);
void drawList(List l, char *name);

#endif
