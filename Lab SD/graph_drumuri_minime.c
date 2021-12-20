#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//#include "heap.h"
#include "MinHeap.h"

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}


void dijkstra(TGraphL G, int s)
{	
	int* val = (int*)malloc(sizeof(int) * G.nn);
	int* dad = (int*)malloc(sizeof(int) * G.nn);
    APriQueue h = makeQueue(G.nn);

    int i;
    for(i = 0; i < G.nn; i++) {
    	val[i] = INT_MAX;
    	dad[i] = -1;
    }

    ItemType s_type;
    s_type.content = s;
    s_type.prior = 0;
    val[s] = 0;
    dad[s] = 0;
    insert(h, s_type);

    ItemType min;
    while(h->size != 0) {
    	min = removeMin(h);

    	ATNode p = G.adl[min.content];
    	while(p != NULL) {
    		if (val[p->v] > val[min.content] + p->c) {
    			val[p->v] = val[min.content] + p->c;
    			dad[p->v] = min.content;

    			s_type.content = p->v;
    			s_type.prior = val[p->v];
    			insert(h, s_type);
    		}

    		p = p->next;
    	}
    }

    printf("\nDijkstra(nod | valoarea | tata):\n");
    for(i = 0; i < G.nn; i++) {
    	printf("%d %d %d\n", i, val[i], dad[i]);
    }
}

void Prim(TGraphL G)
{
    int* val = (int*)malloc(sizeof(int) * G.nn);
	int* dad = (int*)malloc(sizeof(int) * G.nn);
	int* color = (int*)malloc(sizeof(int) * G.nn);

    APriQueue h = makeQueue(G.nn);

    int i;
    for(i = 0; i < G.nn; i++) {
    	val[i] = INT_MAX;
    	dad[i] = -1;
    	color[i] = 0;
    }

    ItemType s_type;
    s_type.content = 0;
    s_type.prior = 0;
    val[0] = 0;
    dad[0] = 0;
    insert(h, s_type);

    ItemType min;
    while(h->size != 0) {
    	min = removeMin(h);

    	ATNode p = G.adl[min.content];
    	while(p != NULL) {
    		if (color[p->v] == 0 && p->c < val[p->v]) {
    			val[p->v] = p->c;
    			dad[p->v] = min.content;

    			s_type.content = p->v;
    			s_type.prior = val[p->v];
    			insert(h, s_type);
    		}

    		p = p->next;
    	}

    	color[min.content] = 1;
    }

    printf("\nPrim(nod | valoare | tata | culoare):\n");
    for(i = 0; i < G.nn; i++) {
    	printf("%d %d %d %d\n", i, val[i], dad[i], color[i]);
    }
}


int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    printf("%d : ", i);
    for(t = G.adl[i]; t != NULL; t = t->next)
    printf("%d ",t->v);
    printf("\n");
	}
	dijkstra(G,0);
	Prim(G);

	return 0;
}
