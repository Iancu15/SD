/*
*	Created by Nan Mihai on 17.03.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 5 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
TTree createTree(Item value) {
	TTree root = malloc(sizeof(TreeNode));
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/*
*	Funcție care inițializează un nod de arbore
*		- îi alocă memorie
*		- îi setează câmpul valoare
*		- setează left și right să pointeze către NULL
*/
void init(TTree *root, Item value) {
	(*root)=(TTree)malloc(sizeof(TreeNode));
	(*root)->value=value;
	(*root)->left=NULL;
	(*root)->right=NULL;
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
TTree insert(TTree root, Item value) {
	if(root==NULL){
		root = createTree(value);
		return root;
	} else if(root->value==value){
		return root;
	} else{
		if(root->value>value){
			if(root->left==NULL){
				init(&root->left,value);
				return root;
			} else{
				root->left=insert(root->left,value);
				return root;
			}	
		} else {
			if(root->right==NULL){
				init(&root->right,value);
				return root;
			} else{
				root->right=insert(root->right,value);
				return root;
			}	
		}
	}
	return root;
}

/*
*	Funcție care afișează nodurile folosind parcurgere în postordine
*/
void printPostorder(TTree root) {
	if(root==NULL)return;
	printPostorder(root->left);
	printPostorder(root->right);
	printf("%d ",root->value);
}

/*
*	Funcție care afișează nodurile folosind parcurgere în preordine
*/
void printPreorder(TTree root) {
	if(root==NULL)return;
	printf("%d ",root->value);
	printPreorder(root->left);
	printPreorder(root->right);
}

/*
*	Funcție care afișează nodurile folosind parcurgere în inordine
*/
void printInorder(TTree root) {
	if(root==NULL)return;
	printInorder(root->left);
	printf("%d ", root->value);
	printInorder(root->right);
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void freeTree(TTree *root) {
	if((*root)==NULL)return;
	freeTree(&(*root)->left);
	freeTree(&(*root)->right);
	free(*root);
	*root=NULL;
}


/*
*	Funcție care determină numărul de noduri dintr-un arbore binar
*/
int size(TTree root) {
	if(root==NULL)return 0;
	return 1 + size(root->left) + size(root->right);
}

/*
*	Funcție care returnează adâncimea maximă a arborelui
*/
int maxDepth(TTree root) {
	if(root==NULL)return 0;
	if(root->left==NULL && root->right==NULL)return 1;
	
	if(maxDepth(root->left)>maxDepth(root->right)){
		return maxDepth(root->left)+1;
	} else{
		return maxDepth(root->right)+1;
	}
}

/*
*	Funcție care construiește oglinditul unui arbore binar
*/
void mirror(TTree root) {
	if(root==NULL)return;
	mirror(root->left);
	mirror(root->right);
	TTree aux=root->left;
	root->left=root->right;
	root->right=aux;
}

/*
*	Funcție care verifică dacă doi arbori binari sunt identici
*/
int sameTree(TTree root1, TTree root2) {
	if(root1==NULL && root2==NULL)return 1;
	else if(root1==NULL || root2==NULL)return 0;
	else{
		if(root1->value==root2->value){
			return sameTree(root1->left, root2->left)*sameTree(root1->right, root2->right);
		} else{
			return 0;
		}
	}
}
