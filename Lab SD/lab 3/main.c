/*
*	Created by Nan Mihai on 03.03.2020
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 3 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2019-2020, Seria CD
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "DoubleLinkedList.h"

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

void printare(List list){
	ListNode* p=list.first;
	while(p->next!=NULL){
		printf("%d\n",p->value);
		p=p->next;
	}
	printf("%d\n\n",p->value);
}
int check(List l, int *vector, int size) {
	if(l.first == NULL && size == 0) {
		return 1;
	} else {
		int i = 0;
		ListNode *iter = l.first;
		while(iter != NULL && i < size) {
			if(iter->value != vector[i++]) {
				return 0;
			}
			iter = iter->next;
		}
		if (i != size) {
			return 0;
		}
		iter = l.last;
		//printf("TEXT\n");
		while (iter != NULL && i > 0) {
			if (iter->value != vector[--i]) {
				return 0;
			}
			iter = iter->prev;
		}
		if(iter == NULL && i == 0) {
			//printf("TE\n");
			return 1;
		} else {
			return 0;
		}
	}
}

static char *test_problema1() {
	int *v, size;
	size = 1;
	v = (int*) malloc(size*sizeof(int));
	v[0] = 5;
	List l1;
	l1 = createList(5);
	drawList(l1, "prob1_test1");
	sd_assert("Problema1 - Test1 picat", check(l1, v, size));
	l1 = destroyList(l1);
	
	List l2 = createList(10);
	v[0] = 10;
	drawList(l2, "prob1_test2");
	sd_assert("Problema1 - Test2 picat", check(l2, v, size));
	l2 = destroyList(l2);
	free(v);
	return 0;
}

static char *test_problema2() {
	int *v, size;
	size = 1;
	v = (int*) malloc(size*sizeof(int));
	v[0] = 5;
	List l1;
	l1 = createList(5);
	drawList(l1, "prob2_test1");
	sd_assert("Problema2 - Test1 picat", !isEmpty(l1));
	l1 = destroyList(l1);
	
	List l2 = createList(10);
	v[0] = 10;
	drawList(l2, "prob2_test2");
	sd_assert("Problema2 - Test2 picat", !isEmpty(l2));
	l2 = destroyList(l2);
	free(v);
	
	List l3 = nill();
	sd_assert("Problema2 - Test3 picat", isEmpty(l3));
	drawList(l3, "prob2_test3");
	return 0;
}

static char *test_problema3() {
	int *v, size, i, count;
	size = 1;
	v = (int*) malloc(size * sizeof(int));
	v[0] = 5;
	List l1 = nill();
	l1 = insertAt(l1, 5, 0);
	drawList(l1, "prob3_test1");
	sd_assert("Problema3 - Test1 picat", check(l1, v, size));
	free(v);
	l1 = destroyList(l1);
	
	List l2 = nill();
	size = 5;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		//if(i!=0)printare(l2);
		l2 = insertAt(l2, v[i], i);
		//printf("%d\n",v[i]);
	}
	drawList(l2, "prob3_test2");
	sd_assert("Problema3 - Test2 picat", check(l2, v, size));
	free(v);
	l2 = destroyList(l2);

	List l3 = nill();
	size = 5;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		if (i > 0)
			l3 = insertAt(l3, v[i], i-1);
	}
	l3 = insertAt(l3, v[0], 0);
	drawList(l3, "prob3_test3");
	sd_assert("Problema3 - Test3 picat", check(l3, v, size));
	free(v);
	l3 = destroyList(l3);

	List l4 = nill();
	size = 5;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		if (i < size - 1)
			l4 = insertAt(l4, v[i], i);
	}
	l4 = insertAt(l4, v[size-1], size-1);
	drawList(l4, "prob3_test4");
	sd_assert("Problema3 - Test4 picat", check(l4, v, size));
	free(v);
	l4 = destroyList(l4);

	List l5 = nill();
	size = 15;
	count = 0;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		if (i != 10)
			l5 = insertAt(l5, v[i], count++);
	}
	l5 = insertAt(l5, v[10], 10);
	drawList(l5, "prob3_test5");
	sd_assert("Problema3 - Test5 picat", check(l5, v, size));
	free(v);
	l5 = destroyList(l5);

	return 0;
}

static char *test_problema4() {
	int *v, size, i, count;
	size = 1;
	v = (int*) malloc(size * sizeof(int));
	v[0] = 5;
	List l1 = nill();
	l1 = insertAt(l1, 5, 0);
	drawList(l1, "prob4_test1");
	sd_assert("Problema4 - Test1 picat", check(l1, v, size) && contains(l1, v[0]) && !contains(l1, v[0]-1));
	free(v);
	l1 = destroyList(l1);
	
	List l2 = nill();
	size = 5;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l2 = insertAt(l2, v[i], i);
	}
	drawList(l2, "prob4_test2");
	sd_assert("Problema4 - Test2 picat", check(l2, v, size) && contains(l2, v[size-1]) && !contains(l2, 100));
	free(v);
	l2 = destroyList(l2);

	List l3 = nill();
	size = 5;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l3 = insertAt(l3, v[i], i);
	}
	drawList(l3, "prob4_test3");
	sd_assert("Problema4 - Test3 picat", check(l3, v, size) && contains(l3, v[1]) && contains(l3, v[3]) && contains(l3, v[2]));
	free(v);
	l3 = destroyList(l3);

	return 0;
}

static char *test_problema5() {
	int *v, size, i, count;
	size = 1;
	v = (int*) malloc(size * sizeof(int));
	v[0] = 5;
	List l1 = nill();
	l1 = insertAt(l1, 5, 0);
	l1 = deleteOnce(l1, 5);
	drawList(l1, "prob5_test1");
	sd_assert("Problema5 - Test1 picat", isEmpty(l1));
	free(v);
	l1 = destroyList(l1);
	
	List l2 = nill();
	size = 5;
	v = (int*) malloc(size * sizeof(int));
	l2 = insertAt(l2, 10, 0);
	for (i = 0; i < size; i++) {
		v[i] = 2 * i;
		l2 = insertAt(l2, v[i], i);
	}
	l2 = deleteOnce(l2, 10);
	drawList(l2, "prob5_test2");
	sd_assert("Problema5 - Test2 picat", check(l2, v, size));
	free(v);
	l2 = destroyList(l2);

	List l3 = nill();
	size = 5;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = 3 * i;
		l3 = insertAt(l3, v[i], i);
	}
	l3 = insertAt(l3, 100, size);
	//printare(l3);
	l3 = deleteOnce(l3, 100);
	//printare(l3);
	drawList(l3, "prob5_test3");
	sd_assert("Problema5 - Test3 picat", check(l3, v, size));
	free(v);
	l3 = destroyList(l3);

	List l4 = nill();
	size = 10;
	v = (int*) malloc(size * sizeof(int));
	count = 0;
	for (i = 0; i < size; i++) {
		v[i] = 2 * i;
		l4 = insertAt(l4, v[i], count++);
		l4 = insertAt(l4, v[i]+1, count++);
	}
	for (i = 0; i < size; i++) {
		l4 = deleteOnce(l4, 2 * i + 1);
	}
	drawList(l4, "prob5_test4");
	sd_assert("Problema5 - Test4 picat", check(l4, v, size));
	free(v);
	l4 = destroyList(l4);

	return 0;
}

static char *test_problema6() {
	int *v, size, i, count;
	size = 1;
	v = (int*) malloc(size * sizeof(int));
	v[0] = 5;
	List l1 = nill();
	l1 = insertAt(l1, 5, 0);
	drawList(l1, "prob6_test1");
	sd_assert("Problema6 - Test1 picat", check(l1, v, size) && length(l1) == size);
	free(v);
	l1 = destroyList(l1);
	
	List l2 = nill();
	size = 5;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l2 = insertAt(l2, v[i], i);
	}
	drawList(l2, "prob6_test2");
	sd_assert("Problema6 - Test2 picat", check(l2, v, size) && length(l2) == size);
	free(v);
	l2 = destroyList(l2);

	List l3 = nill();
	size = 20;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l3 = insertAt(l3, v[i], i);
	}
	drawList(l3, "prob6_test3");
	sd_assert("Problema6 - Test3 picat", check(l3, v, size) && length(l3) == size);
	free(v);
	l3 = destroyList(l3);

	return 0;
}

static char *test_problema7() {
	int *v, size, i, count;
	size = 1;
	v = (int*) malloc(size * sizeof(int));
	v[0] = 5;
	List l1 = nill();
	l1 = insertAt(l1, 5, 0);
	drawList(l1, "prob7_test1");
	sd_assert("Problema7 - Test1 picat", isPalindrome(l1));
	free(v);
	l1 = destroyList(l1);
	
	List l2 = nill();
	size = 5;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = i;
		l2 = insertAt(l2, v[i], i);
	}
	drawList(l2, "prob7_test2");
	//printf("%d\n", isPalindrome(l2));
	sd_assert("Problema7 - Test2 picat", !isPalindrome(l2));
	free(v);
	l2 = destroyList(l2);

	List l3 = nill();
	size = 15;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l3 = insertAt(l3, v[i], i);
	}
	count = i;
	for (i = size - 1; i >= 0; i--) {
		l3 = insertAt(l3, v[i], count++);
	}
	drawList(l3, "prob7_test3");
	sd_assert("Problema7 - Test3 picat", isPalindrome(l3));
	free(v);
	l3 = destroyList(l3);

	List l4 = nill();
	size = 7;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l4 = insertAt(l4, v[i], i);
	}
	count = i;
	l4 = insertAt(l4, 22, count++);
	for (i = size - 1; i >= 0; i--) {
		l4 = insertAt(l4, v[i], count++);
	}
	drawList(l4, "prob7_test4");
	sd_assert("Problema7 - Test4 picat", isPalindrome(l4));
	free(v);
	l4 = destroyList(l4);

	List l5 = nill();
	size = 7;
	v = (int*) malloc(size * sizeof(int));
	for (i = 0; i < size; i++) {
		v[i] = rand() % 100;
		l5 = insertAt(l5, v[i], i);
	}
	count = i;
	l5 = insertAt(l5, 22, count++);
	l5 = insertAt(l5, 18, count++);
	for (i = size - 1; i >= 0; i--) {
		l5 = insertAt(l5, v[i], count++);
	}
	drawList(l5, "prob7_test5");
	sd_assert("Problema7 - Test5 picat", !isPalindrome(l5));
	free(v);
	l4 = destroyList(l4);

	return 0;
}

static char *all_tests() {
	sd_run_test(test_problema1, 1);
	sd_run_test(test_problema2, 1);
	sd_run_test(test_problema3, 3);
	sd_run_test(test_problema4, 1);
	sd_run_test(test_problema5, 3);
	sd_run_test(test_problema6, 1);
	sd_run_test(test_problema7, 3);
	return 0;
}

static char *selective_tests(int argc, char **argv) {
	int i;
	int viz[8] = {0};
	for (i = 1; i < argc; i++) {
		if (viz[atoi(argv[i])]) {
			continue;
		}
		if (!strcmp(argv[i], "1")) {
			viz[1] = 1;
			sd_run_test(test_problema1, 1);
		} else if (!strcmp(argv[i], "2")) {
			viz[2] = 1;
			sd_run_test(test_problema2, 1);
		} else if (!strcmp(argv[i], "3")) {
			viz[3] = 1;
			sd_run_test(test_problema3, 3);
		} else if (!strcmp(argv[i], "4")) {
			viz[4] = 1;
			sd_run_test(test_problema4, 1);
		} else if (!strcmp(argv[i], "5")) {
			viz[5] = 1;
			sd_run_test(test_problema5, 3);
		} else if (!strcmp(argv[i], "6")) {
			viz[6] = 1;
			sd_run_test(test_problema6, 1);
		} else if (!strcmp(argv[i], "7")) {
			viz[7] = 1;
			sd_run_test(test_problema7, 3);
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
