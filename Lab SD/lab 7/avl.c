#include "avl.h"

Tree createTree(T value) {
	Tree root = malloc(sizeof(struct node));
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	root->height = 1;
	return root;
}

int maximum(int a, int b) {
	return (a > b) ? a : b;
}

int height(Tree root) {
	if (root == NULL)
		return 0;
	return root->height;
}

int balancedFactor(Tree root) {
	if (root == NULL)
		return 0;
	return height(root->left) - height(root->right);
}

void updateHeight(Tree root) {
	root->height = maximum(height(root->left), height(root->right)) + 1;
}

Tree leftRotation(Tree x) {
	Tree newroot=x->right;
	x->right=x->right->left;
	newroot->left=x;
	updateHeight(x);
	updateHeight(newroot);
	return newroot;
}

Tree rightRotation(Tree x) {
	Tree newroot=x->left;
	x->left=x->left->right;
	newroot->right=x;
	updateHeight(x);
	updateHeight(newroot);
	return newroot;
}

Tree insert(Tree root, T value) {
	if(root==NULL)
		return createTree(value);
	if(root->value<value){
		root->right=insert(root->right,value);
	} else {
		root->left=insert(root->left,value);
	}

	updateHeight(root);
	int BF=balancedFactor(root);

	if(BF <= 1 && BF >= -1){
		return root;
	}
	if(root->value<value){

		if(BF < -1){
			if(root->right->value<value){
				return leftRotation(root);
			} else{
				root->right=rightRotation(root->right);
				return leftRotation(root);
			}
		}
	}else{

		if(BF > 1){
			if(root->left->value>value){
				return rightRotation(root);
			} else{
				root->left=leftRotation(root->left);
				return rightRotation(root);
			}
		}
	}

	printf("%d\n", root->value);
	return root;
}

Tree freeTree(Tree root) {
	if (root == NULL)
		return NULL;
	root->left = freeTree(root->left);
	root->right = freeTree(root->right);
	free(root);
	return NULL;
}

