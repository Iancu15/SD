#ifndef _TREE_H_
#define _TREE_H_
/*
*	Created by Nan Mihai on 17.03.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 5 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/

#include <stdio.h>
#include <stdlib.h>

/*
*	Reprezentarea unui arbore binar prezentată în curs (R1)
*/
typedef int Item;

typedef struct node {
    Item value;
    struct node *left;
    struct node *right;
} TreeNode, *TTree;

void init(TTree *root, Item value);
TTree insert(TTree root, Item value);
void printPostorder(TTree root);
void printPreorder(TTree root);
void printInorder(TTree root);
void freeTree(TTree *root);
int size(TTree root);
int maxDepth(TTree root);
void mirror(TTree root);
int sameTree(TTree root1, TTree root2);
#endif
