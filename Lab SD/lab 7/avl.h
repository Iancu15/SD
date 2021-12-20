#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct node {
	T value;
	int height;
	struct node *left, *right;
} *Tree;

Tree createTree(T);
int maximum(int, int);
int height(Tree);
int balancedFactor(Tree);
void updateHeight(Tree);
Tree leftRotation(Tree);
Tree rightRotation(Tree);
Tree insert(Tree, T);
Tree freeTree(Tree);
