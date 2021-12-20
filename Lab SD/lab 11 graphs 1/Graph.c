#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphM* createGraphAdjMatrix(int numberOfNodes){
	TGraphM* graph = malloc(sizeof(TGraphM));
	graph->Ma = (int**)malloc(sizeof(int*) * numberOfNodes);
	graph->nn = numberOfNodes;

	int i;
	for(i = 0; i < numberOfNodes; i++) {
		graph->Ma[i] = (int*)calloc(sizeof(int), numberOfNodes);
	}

	return graph;
}

TGraphL* createGraphAdjList(int numberOfNodes){
	TGraphL* list = malloc(sizeof(TGraphL));
	list->adl = (ATNode*)malloc(sizeof(ATNode) * numberOfNodes);
	list->nn = numberOfNodes;

	int i;
	for(i = 0; i < numberOfNodes; i++) {
		// list->adl[i] = (ATNode)malloc(sizeof(TNode));
		list->adl[i] = NULL;
	}

	return list;
}

void addEdgeMatrix(TGraphM* graph, int v1, int v2){
	graph->Ma[v1][v2] = 1;
	graph->Ma[v2][v1] = 1;
}

void addEdgeList(TGraphL* graph, int v1, int v2){
	TNode* newnode = malloc(sizeof(TNode));
	newnode->v = v2;

	if(graph->adl[v1] == NULL) {
		graph->adl[v1] = newnode;
		graph->adl[v1]->next = NULL;
	} else {
		newnode->next = graph->adl[v1];
		graph->adl[v1] = newnode;
	}

	TNode* newnode2 = malloc(sizeof(TNode));
	newnode2->v = v1;

	if(graph->adl[v2] == NULL) {
		graph->adl[v2] = newnode2;
		graph->adl[v2]->next = NULL;
	} else{
		newnode2->next = graph->adl[v2];
		graph->adl[v2] = newnode2;
	}
}

void removeEdgeMatrix(TGraphM* graph, int v1, int v2){
	graph->Ma[v1][v2] = 0;
	graph->Ma[v2][v1] = 0;
}

void removeNodeMatrix(TGraphM* graph, int v){
	int i;
	for(i = 0; i < graph->nn; i++) {
		graph->Ma[v][i] = 0;
		graph->Ma[i][v] = 0;
	}

	graph->nn--;
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	TNode* p = graph->adl[v1];

	if (p != NULL) {
		if (p->v == v2) {
			graph->adl[v1] = graph->adl[v1]->next;
			free(p);
		} else {

			while(p->next != NULL){
				if (p->next->v == v1)
					break;

				p = p->next;
			}

			if (p->next != NULL) {
				if (p->next->v == v2) {
					TNode* g = p->next;
					p->next = p->next->next;

					free(g);
				}
			}

			if (p->next == NULL && p->v == v1) {
				free(p);
			}
		}
	}

	p = graph->adl[v2];

	if (p != NULL) {
		if (p->v == v1) {
			graph->adl[v2] = graph->adl[v2]->next;
			free(p);
		} else {
			while(p->next != NULL){
				if (p->next->v == v1)
					break;

				p = p->next;
			}

			if (p->next != NULL) {
				if (p->next->v == v1) {
					TNode* g = p->next;
					p->next = p->next->next;

					free(g);
				}
			}

			if (p->next == NULL && p->v == v1) {
				free(p);
			}
		}
	}
}

void removeNodeList(TGraphL* graph, int v){
	int i;
	for(i = 0; i < graph->nn; i++) {
		removeEdgeList(graph, v, i);
	}

	graph->nn--;
}


void destroyGraphAdjMatrix(TGraphM *graph){
	int i;
	for(i = 0; i < graph->nn; i++) {
		free(graph->Ma[i]);
	}

	free(graph->Ma);
	free(graph);
}

void destroyGraphAdjList(TGraphL* graph){
	int numberOfNodes = graph->nn;

	int i;
	for(i = 0; i < numberOfNodes; i++) {
		TNode* p = graph->adl[i];

		if (p != NULL) {
			while(p->next != NULL) {
				TNode* temp = p;
				p = p->next;
				free(temp);
			}

			free(p);
		}
	}

	free(graph->adl);
	free(graph);
}

List* dfsIterativeGM(TGraphM* graph, int s){
	Stack* stack = createStack();
	List* list = createList();
	int* val = calloc(sizeof(int), graph->nn);

	push(stack, s);
	while(!isStackEmpty(stack)) {
		int elem = top(stack);
		pop(stack);
		val[elem] = 1;

		ListNode* newnode = malloc(sizeof(ListNode));

		newnode->key = elem;
		newnode->prev = list->head;
		newnode->next = list->head->next;
		list->head->next = newnode;

		int i;
		for(i = 0; i < graph->nn; i++) {
			if (val[i] == 0) {
				push(stack, i);
				val[i] = -1;
			}
		}
	}
	
	free(stack);
	free(val);

	return list;
}

void dfsRecGMHelper(TGraphM* G,int* visited, List* path, int s){
	visited[s] = 1;

	ListNode* newnode = malloc(sizeof(ListNode));
	newnode->key = s;
	newnode->prev = path->head;
	newnode->next = path->head->next;
	path->head->next = newnode;

	if (path->head->prev == path->head) {
		path->head->prev = newnode;
	}

	int i;
	for(i = 0; i < G->nn; i++) {
		if (visited[i] == 0 && G->Ma[s][i] == 1) {
			dfsRecGMHelper(G, visited, path, i);
		}
	}
}

List* dfsRecursiveGM(TGraphM* G, int s){
	List* list = createList();
	int* val = calloc(sizeof(int), G->nn);

	dfsRecGMHelper(G, val, list, s);

	free(val);

	return list;
}

void dfsRecGLHelper(TGraphL* G, int* visited, List* path, int s){
	visited[s] = 1;

	ListNode* newnode = malloc(sizeof(ListNode));
	newnode->key = s;
	newnode->prev = path->head;
	newnode->next = path->head->next;
	path->head->next = newnode;

	if (path->head->prev == path->head) {
		path->head->prev = newnode;
	}

	if (G->adl[s] != NULL) {
		TNode* i;
		for(i = G->adl[s]; i->next != NULL; i = i->next) {
			if (visited[i->v] == 0) {
				dfsRecGLHelper(G, visited, path, i->v);
			}
		}

		if (visited[i->v] == 0) {
			dfsRecGLHelper(G, visited, path, i->v);
		}
	}
}

List* dfsRecursiveGL(TGraphL* G, int s){
	List* list = createList();
	int* val = calloc(sizeof(int), G->nn);

	dfsRecGLHelper(G, val, list, s);

	free(val);

	return list;
}

List* bfsGL(TGraphL* graph, int s){
	Queue* stack = createQueue();
	List* list = createList();
	int* val = calloc(sizeof(int), graph->nn);

	enqueue(stack, s);
	while(!isQueueEmpty(stack)) {
		int elem = front(stack);
		dequeue(stack);
		val[elem] = 1;
		ListNode* newnode = malloc(sizeof(ListNode));

		newnode->key = elem;
		newnode->prev = list->head;
		newnode->next = list->head->next;
		list->head->next = newnode;

		if (list->head->prev == list->head) {
				list->head->prev = newnode;
		}

		if (graph->adl[elem] != NULL) {
			TNode* i;
			for(i = graph->adl[elem]; i->next != NULL; i = i->next) {
				if (val[i->v] == 0) {
					enqueue(stack, i->v);
					val[i->v] = -1;
				}
			}

			if (val[i->v] == 0) {
				enqueue(stack, i->v);
				val[i->v] = -1;
			}
		}
	}
	
	free(val);
	free(stack);

	return list;
}