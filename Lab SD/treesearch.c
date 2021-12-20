/*
*	Created by Nan Mihai on 24.03.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Tree parent, Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->parent = parent;
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
void init(Tree *root, Tree parent, Item value) {
	*root = malloc(sizeof(TreeNode));
	(*root)->parent = parent;
	(*root)->value = value;
	(*root)->left = NULL;
	(*root)->right = NULL;
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insertHelper(Tree root, Tree parent, Item value) {
	if (root == NULL)
		return createTree(parent, value);
	if (root->value == value) {
		printf("Valoarea există!\n");
		return root;
	}
	if (value < root->value)
		root->left = insertHelper(root->left, root, value);
	else
		root->right = insertHelper(root->right, root, value);
	return root;
}

Tree insert(Tree root, Item value) {
	return insertHelper(root, NULL, value);
}

/*
*	Funcție care returnează adâncimea maximă a arborelui
*/
int height(Tree root) {
	if (!root)
		return 0;
	int lDepth, rDepth;
	lDepth = height(root->left);
	rDepth = height(root->right);
	if (lDepth > rDepth)
		return lDepth + 1;
	else
		return rDepth + 1;
}

/*
*	Funcție care verifică dacă o valoare există sau nu în arbore
*		- 1 dacă value există în arbore
*		- 0 dacă value nu există în arbore
*/
int contains(Tree tree, Item value) {
	if(tree->value==value){
		return 1;
	} else if(tree->value>value){
		if(tree->left==NULL)return 0;
		return contains(tree->left,value);
	} else {
		if(tree->right==NULL)return 0;
		return contains(tree->right,value);
	}
	return -1;
}

/*
*	Funcție care determină elementul minim dintr-un arbore binar de căutare
*		- -1 pentru arbore vid
*/
Item minimum(Tree tree) {
	if(tree->left!=NULL){
		return minimum(tree->left);
	} else {
		return tree->value;
	}
	return -1;
}

/*
*	Funcție care determină elementul maxim dintr-un arbore binar de căutare
*		- -1 pentru arbore vid
*/
Item maximum(Tree tree) {
	if(tree->right!=NULL){
		return maximum(tree->right);
	} else {
		return tree->value;
	}
	return -1;
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void freeTree(Tree *root) {
	if (*root == NULL)
		return;
	freeTree(&((*root)->left));
	freeTree(&((*root)->right));
	free(*root);
	*root = NULL;
}

/*
*	Funcție care șterge un nod cu o anumită valoare din arbore
*/
Tree delete(Tree root, Item value) {
	Tree temp=(Tree)malloc(sizeof(TreeNode));
	if(root==NULL)return root;
	if(root->value>value){
		root->left=delete(root->left,value);
	} else if(root->value<value){
		root->right=delete(root->right,value);
	} else{
		if(root->left!=NULL && root->right!=NULL){
			temp->value=minimum(root->right);
			root->value=temp->value;
			root->right=delete(root->right,temp->value);
		}else{
			temp=root;
			if(root->left!=NULL){
				root=root->left;
			} else{
				root=root->right;
			}
			free(temp);
		}
	}
	return root;
}

/*
*	Funcție care determină cel mai apropiat strămoș comun pentru
* două noduri având cheile value1 și value2
*/
Item lowestCommonAncestor(Tree root, Item value1, Item value2) {
	if(root==NULL)return 0;
	if((root->value>value1 && root->value<value2) || (root->value<value1 && root->value>value2)){
		return root->value;
	} else if(root->value<value1 && root->value<value2){
		return lowestCommonAncestor(root->right,value1,value2);
	} else{
		return lowestCommonAncestor(root->left,value1,value2);
	}
	return -1;
}

Tree minimumtree(Tree tree) {
	if(tree==NULL)return NULL;
	if(tree->left!=NULL){
		return minimumtree(tree->left);
	} else {
		return tree;	}
	return tree;
}

Tree successor(Tree root, Item value) {
	if(root->value==value){
		if(root->right!=NULL){
			return minimumtree(root->right);
		} else if(root->parent->left==root){
			return root->parent;
		} else {
			Tree current=root;
			Tree parent=root->parent;
			while(parent!=NULL && parent->value<value){
				current=parent;
				parent=parent->parent;
			}
			return parent;
		}
	}else{
		if(root->value<value){
			return successor(root->right,value);
		} else{
			return successor(root->left,value);
		}
	}
}

Tree maximumtree(Tree tree) {
	if(tree==NULL)return NULL;
	if(tree->right!=NULL){
		return maximumtree(tree->right);
	} else {
		return tree;	}
	return tree;
}

Tree predecessor(Tree root, Item value) {
	if(root->value==value){
		if(root->left!=NULL){
			return maximumtree(root->left);
		} else if(root->parent->right==root){
			return root->parent;
		} else {
			Tree current=root;
			Tree parent=root->parent;
			while(parent!=NULL && parent->value>value){
				current=parent;
				parent=parent->parent;
			}
			return parent;
		}
	}else{
		if(root->value<value){
			return predecessor(root->right,value);
		} else{
			return predecessor(root->left,value);
		}
	}
}
