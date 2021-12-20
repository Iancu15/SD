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
#include <time.h>
#include <string.h>
#include "tree.h"

#define sd_assert(message, test) \
	do { \
		if (!(test)) \
			return message; \
	} while (0)

#define sd_run_test(test, score) \
	do { \
		char *message = test(); \
		tests_run++; \
		if (message) \
			return message; \
		else \
			total_score += score; \
	} while (0)

int tests_run = 0;
float total_score = 0;

int test1[] = {9, 7, 5, 9, 4, 10, 6, 8, -8, 12};
int test2[] = {11, 9, 7, 25, 12, 29, 27, 8, 5, 1, 35, 26};
int test3[] = {26, 50, 150, 35, 175, 155, 100, 95, 9, 15, 45, 40, 4, 47, 98, \
	97, 99, 90, 200, 50, 68, 35, 39, 37, 44, 43, 46};

int checkBST(TTree node) { 
	if (node == NULL) 
		return 1;
	if (node->left != NULL && node->left->value > node->value)
		return 0; 
	if (node->right != NULL && node->right->value < node->value) 
		return 0; 
	if (!checkBST(node->left) || !checkBST(node->right)) 
		return 0; 
	return 1; 
}

void bst_print_dot_aux(TTree node, FILE* stream) {
    static int nullcount = 0;

    if (node->left) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->left->value);
        bst_print_dot_aux(node->left, stream);
    }
    if (node->right) {
        fprintf(stream, "    %d -> %d;\n", node->value, node->right->value);
        bst_print_dot_aux(node->right, stream);
    }
}

void bst_print_dot(TTree tree, FILE* stream, int type) {
    fprintf(stream, "digraph BST {\n");
    if (type == 1)
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=green];\n");
    else
    	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=blue];\n");
    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %d;\n", tree->value);
    else
        bst_print_dot_aux(tree, stream);
    fprintf(stream, "}\n");
}

static char *test_insert() {
	TTree tree = NULL;
	FILE *f;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_tree1.png");
	sd_assert("Problema1 - Test1 insert picat", checkBST(tree) && tree != NULL);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_tree2.png");
	sd_assert("Problema1 - Test2 insert picat", checkBST(tree) && tree != NULL);
	freeTree(&tree);
	
	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 1);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_tree3.png");
	sd_assert("Problema1 - Test3 insert picat", checkBST(tree) && tree != NULL);
	freeTree(&tree);
	return 0;
}

static char *test_maxDepth() {
	TTree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	sd_assert("Problema1 - Test1 maxDepth picat", maxDepth(tree) == 4);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	sd_assert("Problema1 - Test2 maxDepth picat", maxDepth(tree) == 5);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	sd_assert("Problema1 - Test3 maxDepth picat", maxDepth(tree) == 6);
	freeTree(&tree);

	return 0;
}

static char *test_size() {
	TTree tree = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
	}
	sd_assert("Problema1 - Test1 size picat", size(tree) == test1[0]);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
	}
	sd_assert("Problema1 - Test2 size picat", size(tree) == test2[0]);
	freeTree(&tree);

	tree = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
	}
	sd_assert("Problema1 - Test3 size picat", size(tree) == test3[0] - 2);
	freeTree(&tree);

	return 0;
}

int areMirrorTrees(TTree root1, TTree root2) {
	if (root1 == NULL && root2 == NULL)
		return 1;
	if (root1 == NULL || root2 == NULL)
		return 0;
	if (root1->value != root2->value)
		return 0;
	int res1, res2;
	res1 = areMirrorTrees(root1->left, root2->right);
	res2 = areMirrorTrees(root1->right, root2->left);
	return res1 && res2;
}

static char *test_mirror() {
	TTree tree = NULL, result = NULL;
	int i;
	FILE *f;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
		result = insert(result, test1[i]);
	}
	mirror(tree);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 3);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_mirror1.png");
	sd_assert("Problema2 - Test1 mirror picat", areMirrorTrees(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
		result = insert(result, test2[i]);
	}
	mirror(tree);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 3);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_mirror2.png");
	sd_assert("Problema2 - Test2 mirror picat", areMirrorTrees(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
		result = insert(result, test3[i]);
	}
	mirror(tree);
	f = fopen("test.dot", "w");
	bst_print_dot(tree, f, 3);
	fclose(f);
	system("dot test.dot | neato -n -Tpng -o out_mirror3.png");
	sd_assert("Problema2 - Test3 mirror picat", areMirrorTrees(tree, result));
	freeTree(&tree);
	freeTree(&result);

	return 0;
}

static char *test_sameTree() {
	TTree tree = NULL, result = NULL;
	int i;

	for (i = 1; i <= test1[0]; i++) {
		tree = insert(tree, test1[i]);
		result = insert(result, test1[i]);
	}
	sd_assert("Problema3 - Test1 sameTree picat", sameTree(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test2[0]; i++) {
		tree = insert(tree, test2[i]);
		result = insert(result, test2[i]);
	}
	sd_assert("Problema3 - Test2 sameTree picat", sameTree(tree, result));
	freeTree(&tree);
	freeTree(&result);

	tree = NULL;
	result = NULL;
	for (i = 1; i <= test3[0]; i++) {
		tree = insert(tree, test3[i]);
		result = insert(result, test3[i]);
	}
	sd_assert("Problema3 - Test3 sameTree picat", sameTree(tree, result));
	freeTree(&tree);
	freeTree(&result);

	return 0;
}

static char *all_tests() {
	sd_run_test(test_insert, 3);
	sd_run_test(test_maxDepth, 1);
	sd_run_test(test_size, 1);
	sd_run_test(test_mirror, 1.5);
	sd_run_test(test_sameTree, 1.5);
	return 0;
}

static char *selective_tests(int argc, char **argv) {
	int i;
	int viz[6] = {0};
	for (i = 1; i < argc; i++) {
		if (viz[atoi(argv[i])]) {
			continue;
		}
		if (!strcmp(argv[i], "1")) {
			viz[1] = 1;
			sd_run_test(test_insert, 3);
		} else if (!strcmp(argv[i], "2")) {
			viz[2] = 1;
			sd_run_test(test_maxDepth, 1);
		} else if (!strcmp(argv[i], "3")) {
			viz[3] = 1;
			sd_run_test(test_size, 1);
		} else if (!strcmp(argv[i], "4")) {
			viz[4] = 1;
			sd_run_test(test_mirror, 1);
		} else if (!strcmp(argv[i], "5")) {
			viz[5] = 1;
			sd_run_test(test_sameTree, 1);
		}
	}
	return 0;
}

int main(int argc, char **argv) {
	srand(time(NULL));
	char *result;
	if (argc == 1) {
		result = all_tests();
		if (result != 0) {
			printf("%s\n", result);
		} else {
			printf("Toate testele au trecut! Felicitari!\n");
		}
	} else {
		result = selective_tests(argc, argv);
		if (result != 0) {
			printf("%s\n", result);
		} else {
			printf("Toate testele selectate au trecut!\n");
		}
	}
	printf("Punctajul obtinut este: %.2lf\n", total_score);
	printf("Teste rulate: %d\n", tests_run);
	return result != 0;
}
