#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	List* l=(List*)malloc(sizeof(ListNode));
	l->first=NULL;
	l->last=NULL;
	return l;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	if(list->first!=NULL)return 0;
	return 1;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	ListNode* p;
	if(list->first==NULL)return 0;
	for(p=list->first;p->elem!=elem && p->next!=NULL;p=p->next){}
	if(p->elem==elem)return 1;
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAt(List* list, Item elem, int pos){
	/*ListNode* p;
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	if(list == NULL) {
		free(newnode);
		return;
	}
	newnode->elem=elem;
	int count=0;
	/*for(p=list->first;count<pos && p->next!=NULL;p=p->next){
		count++;
	}*/
	/*if(pos==-1){
		newnode->next=list->first;
		list->first->prev=newnode;
	} 
	/*else {
		newnode->next=p;
		newnode->prev=p->prev;
		p->prev->next=p;
		p->prev=newnode;
	}*/
	return;
}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem){
	ListNode* p;
	if(list == NULL) return;
	for(p=list->first;p->elem!=elem && p->next!=NULL;p=p->next){}
	if(p->next==NULL){
		p->prev->next=NULL;
		p->prev=NULL;
		free(p);
	} else {
		p->prev->next=p->next;
		p->next=NULL;
		p->prev=NULL;
		free(p);
	}
}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list){
	ListNode* p;
	int count=1;
	if(list == NULL) return 0;
	if(list->first==NULL) return 0;
	for(p=list->first;p!=list->last;p=p->next){
		count++;
	}
	printf("%d\n",count);
	return count;
}
// -----------------------------------------------------------------------------



/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
void destroyList(List* list){
	// Guard against young player errors
	if(list == NULL) return;

	//TODO: Cerinta 1g
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
