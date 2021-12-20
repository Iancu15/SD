#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>



typedef struct huff{
    char value;
    int left, right;
    int prior;
    int index;
} HuffmanNode;

// #define Item HuffmanNode

// Including below so `Item` is defined.
#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256]) {
	char *p;
	int i = 0;
	for (i = 0; i < 256; i++) {
		freqs[i] = 0;
	}

	for(p = text; *p != '\0'; p++) {
		freqs[(int)p[0]]++;
	}
}

HuffmanNode *makeTree(int freqs[256], int *size) {
	APriQueue h = makeQueue(256);

	int i, k = 0;
	for(i = 0; i < 256; i++) {
		if (freqs[i] != 0) {
			HuffmanNode x;
			x.value = (unsigned char)i;
			x.prior = freqs[i];
			x.index = k++;
			insert(h, x);
		}
	}

	if (h->size == 0) {
		return NULL;
	}

	int capacity = h->size;
	*size = 1;
	HuffmanNode* huffman = (HuffmanNode*)malloc(sizeof(HuffmanNode) * capacity);

	// transform din vector in varianta de arbore normala
	while (h->size != 1){
		if (*size + 3 >= capacity){
			capacity *= 2;
			huffman = realloc(huffman, capacity);
		}

		HuffmanNode nod_1 = removeMin(h);
		if (nod_1.value != 36) {
			huffman[++*size - 1] = nod_1;
		}

		HuffmanNode nod_2 = removeMin(h);
		if (nod_2.value != 36) {
			huffman[++*size - 1] = nod_2;
		}

		HuffmanNode nou_parinte;
		nou_parinte.prior = nod_1.prior + nod_2.prior;
		nou_parinte.left = nod_1.index;
		nou_parinte.right = nod_2.index;
		nou_parinte.value = 36;

		k++;
		nou_parinte.index = -k;

		insert(h, nou_parinte);
		huffman[++*size - 1] = nou_parinte;
	}

	freeQueue(h);

	return huffman;
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code) {
	if (index >= 0) {
		codes[index] = (char*)malloc(sizeof(char));
		codes[index] = code;
		return;
	}

	makeCodes(nodes[index].left, nodes, codes, strcat(code, "0"));
	makeCodes(nodes[index].right, nodes, codes, strcat(code, "1"));
}

int max(int a, int b){
	if (a > b)
		return a;

	return b;
}

int HuffmanHeight(int index, HuffmanNode *nodes, int height) {
	if (index >= 0) {
		return height;
	}

	int height_left = HuffmanHeight(nodes[index].left, nodes, ++height);
	int height_right = HuffmanHeight(nodes[index].right, nodes, ++height);

	return max(height_left, height_right);
}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
	if (!strcmp(text, ""))
		return "";

	char **codes = (char**)malloc(sizeof(char*) * numNodes);

	int height = HuffmanHeight(numNodes - 1, nodes, 0);
	char *code = malloc(sizeof(char) * height);

	char *codedtext = malloc(sizeof(char) * height * textSize);
	makeCodes(numNodes - 1, nodes, codes, code);

	char *p;
	int i;
	for(p = text; *p != '\0'; p++) {
		for (i = 0; i < numNodes; i++) {
			if (nodes[i].index >=0) {
				if (nodes[i].value == p[0]) {
					strcat(codedtext, codes[nodes[i].index]);
					break;
				}
			}
		}
	}

	// for(i = 0; i < numNodes; i++) {
	// 	if (codes[i] == NULL)
	// 		break;

	// 	free(codes[i]);
	// }
	// free(codes);

	return codedtext;
}

char unmakeCodes(int index, HuffmanNode *nodes, char *text, int *size) {
	if (index >= 0) {
		return nodes[index].value;
	}

	*size = *size + 1;

	if (text[0] == 0) {
		return unmakeCodes(nodes[index].left, nodes, ++text, size);
	} else {
		return unmakeCodes(nodes[index].right, nodes, ++text, size);
	}
}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
	if (!strcmp(text, ""))
		return "";

	int height = HuffmanHeight(numNodes - 1, nodes, 0);
	if (height == 0)
		return NULL;

	char *decodedtext = malloc(sizeof(char) * (textSize / height));
	int *size = malloc(sizeof(int));
	char* caracter = malloc(sizeof(char));

	int i;
	for (i = 0; i < textSize; i += *size) {
		*caracter = unmakeCodes(numNodes - 1, nodes, text, size);
		*size = 0;
		strcat(decodedtext, caracter);
	}

	// free(caracter);
	// free(size);

	return decodedtext;
}

#endif