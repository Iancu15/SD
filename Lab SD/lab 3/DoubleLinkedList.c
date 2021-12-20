/*
*	Created by Nan Mihai on 03.03.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 3 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/
#include "DoubleLinkedList.h"

ListNode *createListNode(T value) {
	ListNode *node = (ListNode*) malloc(sizeof(ListNode));
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

List nill(void) {
	List list;
	list.first = list.last = NULL;
	return list;
}

/*
*	Funcție care întoarce o listă cu un singur nod, având valoarea value
*		- alocă memorie
*		- atribuie valoarea
*		- marchează finalul
*		- marchează începutul
*/
List createList(T value) {
	List l;
	ListNode* node=createListNode(value);
	l.first=l.last=node;
	return l;
}

/*
*	Funcție care verifică dacă o listă este vidă
*		- 1 dacă lista este vidă
*		- 0 altfel
*/
int isEmpty(List list) {
	if(list.first==NULL)return 1;
	return 0;
}

/*
*	Funcție care inserează valoarea value în listă la poziția pos daca este validă
*		- funcția va avea ca rezultat noua listă
*		- pot exista duplicate în listă
*		- sunt tratate toate cazurile (first poate fi NULL)
*		- trebuie modificat last dacă inserăm la final
*/
List insertAt(List list, T value, int pos) {
	ListNode* node=createListNode(value);
	if(list.first==NULL){
		list.first=list.last=node;
		return list;
	}
	ListNode* p=list.first;
	int count=0;
	while(p->next!=NULL && count<pos){
		count++;
		p=p->next;
	}
	if(p==list.first && pos==0){
		//printf("%d\n",list.first->value);
		node->next=list.first;
		list.first->prev=node;
		list.first=node;
		//printf("%d\n",list.first->value);
	} else if(p==list.last){
		node->next=NULL;
		node->prev=list.last;
		list.last->next=node;
		list.last=node;
	} else {
		node->next=p;
		node->prev=p->prev;
		p->prev->next=node;
		p->prev=node;
	}
	return list;
}

/*
*	Funcție care verifică dacă value apare sau nu în listă
*		- 1 dacă valoarea există
*		- 0 altfel
*/
int contains(List list, T value) {
	ListNode* p = list.first;
	while(p->next!=NULL && p->value!=value){
		p=p->next;
	}
	if(p->value==value)return 1;
	return 0;
}

/*
*	Funcție care șterge prima apariție a elementului value din listă
*		- rezultatul o să fie lista rezultată după ștergere
*		- funcția trebuie să dealoce memoria nodului șters
*/
List deleteOnce(List list, T value) {
	ListNode* p = list.first;
	while(p->next!=NULL && p->value!=value){
		p=p->next;
	}
	if(p->value==value){
		if(p==list.first){
			if(p->next==NULL){
				free(p);
				list.first=list.last=NULL;
			}else {
				p->next->prev=NULL;
				list.first=p->next;
				free(p);
			}
		} else if(p==list.last){
			if(p->prev==NULL){
				free(p);
				list.first=list.last=NULL;
			}
			else{
				p->prev->next=NULL;
				list.last=p->prev;
				free(p);
			}
		} else {
			p->prev->next=p->next;
			p->next->prev=p->prev;
			free(p);
		}
	}
	return list;
}

/*
*	Funcție care determină lungimea listei
*/
int length(List list) {
	if(list.first==NULL){
		return 0;
	}
	ListNode* p=list.first;
	int count=0;
	while(p->next!=NULL){
		count++;
		p=p->next;
	}
	count++;
	return count;
}

/*
*	Funcție care verifică dacă o listă este palindrom
*		- 1 dacă lista este palindrom
*		- 0 altfel
*	Listă palindrom: lista este egală cu reverse-ul ei (ex. NULL<-1<->2<->1->NULL, NULL<-1<->2<->2<->1->NULL)	
*/
int isPalindrome(List list) {
	ListNode* p = list.first;
	ListNode* g = list.last;
	if(p->next==NULL && g->prev==NULL){
		//printf("CE\n");
		return 1;
	}
	/*if(p->next->next==NULL && g->prev->prev==NULL){
		//printf("CE2\n");
		if(p->value=g->value)return 1;
		return 0;
	}*/
	while(p->next->value != g->prev->value || p->value==g->value){
		//printf("CE3\n");
		if(p->value!=g->value)return 0;
		if(p->next==NULL && g->prev==NULL)return 1;
		if(p->next->next==NULL && g->prev->prev==NULL)return 1;
		p=p->next;
		g=g->prev;
		//printf("%d %d\n", p->value, g->value);
	}
	return 0;
	return 1;
}

/*
*	Funcție care șterge o listă, dealocându-i întreaga memorie
*		- rezultatul funcției o să fie lista vidă
*/
List destroyList(List list) {
	if(list.first==NULL)return list;
	ListNode* p = list.first;
	ListNode* temp;
	while(p!=NULL){
		temp=p;
		p=p->next;
		free(temp);
	}
	list.first=list.last=NULL;
	return list;
}

void drawList(List l, char *name) {
	int i;
	FILE *stream;
	char *buffer;
	ListNode *tmp;

	if (l.first == NULL || name == NULL) {
		stream = fopen("list.dot", "w");
		fprintf(stream, "digraph foo {\n");
		fprintf(stream, "rankdir=LR;\nnode [shape=record, style=filled, fillcolor=yellow];\n");
		fprintf(stream, "b [label=\"NULL\", shape=box, fillcolor=red];\n");
		fprintf(stream, "}\n");
		fclose(stream);
		buffer = (char*) malloc(SIZE*sizeof(char));
		sprintf(buffer, "dot list.dot | neato -n -Tpng -o %s.png", name);
		system(buffer);
		free(buffer);
		return;
	}
	stream = fopen("list.dot", "w");
	fprintf(stream, "digraph foo {\n");
	fprintf(stream, "rankdir=LR;\nnode [shape=record, style=filled, fillcolor=yellow];\n");
	tmp = l.first;
	i = 1;
	fprintf(stream, "a0 [label=\"NULL\", shape=box, fillcolor=red];\n");
	while (tmp != NULL) {
		fprintf(stream, "a%d [label=\"{ <ref1> | <data> %d | <ref2>  }\", width=0.9];\n", i, tmp->value);
		tmp = tmp->next;
		i++;
	}
	fprintf(stream, "b [label=\"NULL\", shape=box, fillcolor=red];\n");
	tmp = l.first;
	i = 1;
	fprintf(stream, "a0:e -> a1:ref1:c      [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false, color=white];");
	fprintf(stream, "a1:ref1:c -> a0      [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false];");
	while (tmp->next != NULL) {
		fprintf(stream, "a%d:ref2:c -> a%d:ref1:c [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false, arrowsize=0.9, color=red];\n", i, i+1);
		fprintf(stream, "a%d:ref1:c -> a%d:ref2:c [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false, arrowsize=0.9, color=blue];\n", i+1, i);
		tmp = tmp->next;
		i++;
	}
	fprintf(stream, "a%d:ref2:c -> b      [arrowhead=vee, arrowtail=dot, dir=both, tailclip=false];\n", i);
	fprintf(stream, "}\n");
	fclose(stream);
	buffer = (char*) malloc(SIZE*sizeof(char));
	sprintf(buffer, "dot list.dot | neato -n -Tpng -o %s.png", name);
	system(buffer);
	free(buffer);
}

