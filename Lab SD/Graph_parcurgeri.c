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
	list->list = (ATNode*)malloc(sizeof(ATNode) * numberOfNodes);
	list->nn = numberOfNodes;

	int i;
	for(i = 0; i < numberOfNodes; i++) {
		// list->list[i] = (ATNode)malloc(sizeof(TNode));
		list->list[i] = NULL;
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

	if(graph->list[v1] == NULL) {
		graph->list[v1] = newnode;
		graph->list[v1]->next = NULL;
	} else {
		newnode->next = graph->list[v1];
		graph->list[v1] = newnode;
	}

	TNode* newnode2 = malloc(sizeof(TNode));
	newnode2->v = v1;

	if(graph->list[v2] == NULL) {
		graph->list[v2] = newnode2;
		graph->list[v2]->next = NULL;
	} else{
		newnode2->next = graph->list[v2];
		graph->list[v2] = newnode2;
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
	TNode* p = graph->list[v1];

	if (p != NULL) {
		if (p->v == v2) {
			graph->list[v1] = graph->list[v1]->next;
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

	p = graph->list[v2];

	if (p != NULL) {
		if (p->v == v1) {
			graph->list[v2] = graph->list[v2]->next;
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
		TNode* p = graph->list[i];

		if (p != NULL) {
			while(p->next != NULL) {
				TNode* temp = p;
				p = p->next;
				free(temp);
			}

			free(p);
		}
	}

	free(graph->list);
	free(graph);
}

????? dfsIterativeGM(Graph* graph, int s){
	Stack* stack = createStack();
	int* val = calloc(sizeof(int), graph->nr_nodes);

	push(stack, s);
	while(!isStackEmpty(stack)) {
		int elem = top(stack);
		pop(stack);
		val[elem] = 1;

		int i;
		for(i = G->list[s]; i->next != NULL; i = i->next) {
			if (val[i->v] == 0) {
				push(stack, i->v);
				val[i->v] = -1;
			}
		}
	}
	
	free(stack);
	free(val);

	return ?????
}

void dfsRecursive(Graph* G,int* visited, int s){
	visited[s] = 1;

	int i;
	for(i = 0; i < G->nr_nodes; i++) {
		if (visited[i] == 0 && G->Ma[s][i] == 1) {
			dfsRecGMHelper(G, visited, i);
		}
	}
}

????? functie(Graph* G, int s){
	int* val = calloc(sizeof(int), G->nr_nodes);

	dfsRecursive(G, val, s);

	free(val);

	return ????
}

void dfsRecursive(Graph* G, int* visited, int s){
	visited[s] = 1;

	if (G->list[s] != NULL) {
		TNode* i;
		for(i = G->list[s]; i->next != NULL; i = i->next) {
			if (visited[i->v] == 0) {
				dfsRecursiver(G, visited, i->v);
			}
		}

		if (visited[i->v] == 0) {
			dfsRecursive(G, visited, i->v);
		}
	}
}

???? functie(Graph* G, int s){
	int* val = calloc(sizeof(int), G->nr_nodes);

	dfsRecursive(G, val, list, s);

	free(val);

	return ????
}

???? bfs(Graph* graph, int s){
	Queue* queue = createQueue();
	int* val = calloc(sizeof(int), graph->nr_nodes);

	enqueue(stack, s);
	while(!isQueueEmpty(stack)) {
		int elem = front(stack);
		dequeue(stack);
		val[elem] = 1;

		if (graph->list[elem] != NULL) {
			TNode* i;
			for(i = graph->list[elem]; i->next != NULL; i = i->next) {
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

	return ????
}

???? compconexe(Graph* graph, int s){
	int* val = calloc(sizeof(int), graph->nr_nodes);
	int i;
	for(i = G->list[s]; i->next != NULL; i = i->next) {
		if (val[i->v] == 0) {
			parcurgere(i->v);

			//prelucrare comp conexa;
		}
	}
}

???? parcugere_arb_binar_adancime(TNode root) {
	TStack s; TNode p;
	if(root == NULL) return;
	s = createStack();
	s = push(s,tree);
	while(!isStackEmpty(s)){
		s = pop(s, &p);
		//fac ceva cu elementul o verificare ceva(val este p->elem)
		if(p->rt!=NULL) s = push(s, p->rt);
		if(p->lt!=NULL) s = push(s, p->lt);
	}
}

???? parcugere_arb_binar_latime(TNode root) {
	TQueue q; TNode p;
	if(root == NULL) return;
	q = createQueue();
	q = enqueue(q,tree);
	while(!isStackEmpty(s)){
		q = dequeue(q, &p);
		//fac ceva cu elementul o verificare ceva(val este p->elem)
		if(p->rt!=NULL) q = enqueue(q, p->rt);
		if(p->lt!=NULL) q = enqueue(q, p->lt);
	}
}