#ifndef TREE_H_D
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct Link
  {
    Item  elem;
    struct Link *l;
    struct Link *r;
  } TreeNode;



void Init(TreeNode **t, Item x)
{
	*t = (TreeNode*)malloc(sizeof(TreeNode));
	(*t)->elem=x;
	(*t)->l=NULL;
	(*t)->r=NULL;
}

void Insert(TreeNode **t, Item x)
{
	if((*t)==NULL){
		Init(t,x);
		return;
	}
	if((*t)->elem>x){
		if((*t)->l!=NULL)Init(&((*t)->l->l), x);
		Init(&((*t)->l), x);
	} else{
		if((*t)->r!=NULL)Init(&((*t)->r->r), x);
		Init(&((*t)->r), x);
	}
}

void PrintPostorder(TreeNode *t)
{
	if(t==NULL)return;
	PrintPostorder(t->l);
	PrintPostorder(t->r);
	printf("%d ", t->elem);
}

void PrintPreorder(TreeNode *t)
{
	if(t==NULL)return;
	printf("%d ", t->elem);
	PrintPreorder(t->l);
	PrintPreorder(t->r);
}

void PrintInorder(TreeNode *t)
{
	if(t==NULL)return;
	PrintInorder(t->l);
	printf("%d ", t->elem);
	PrintInorder(t->r);
}

void Free(TreeNode **t)
{
	if((*t)==NULL)return;
	if((*t)->l!=NULL){
		Free(&((*t)->l));
	}
	if((*t)->r!=NULL){
		Free(&((*t)->r));
	}
	free((*t));
}

int Size(TreeNode* t)
{
	if(t==NULL)return 0;
	if(t->r==NULL && t->l==NULL){
		return Size(t->r)+Size(t->l)+1;
	}
}

int maxDepth(TreeNode *t)
{

}

#endif // LINKEDSTACK_H_INCLUDED
