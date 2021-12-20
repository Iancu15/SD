#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void deleteKey(HashTable *hashTable, Key key);

void initHashTable(HashTable **h, long size, HashFunction f) {
	*h = (HashTable*)malloc(sizeof(HashTable));
	(*h)->elements = (Element**)malloc(sizeof(Element*) * size);
	(*h)->size = size;

	int i;
	for(i = 0; i < size; i++) {
		(*h)->elements[i] = NULL;
	}

	(*h)->hashFunction = f;
}

int exists(HashTable *hashTable, Key key) {
	int index = hashTable->hashFunction(key, hashTable->size);
	Element* p = hashTable->elements[index];

	while(p != NULL) {
  		if(!strcmp(p->key, key)) {
  			return 1;
  		}

  		p = p->next;
	}

	return 0;
}

Value get(HashTable *hashTable, Key key) {
	int index = hashTable->hashFunction(key, hashTable->size);
  	Element* p = hashTable->elements[index];

	while(p != NULL) {
  		if(!strcmp(p->key, key)) {
  			return p->value;
  		}

  		p = p->next;
  	}
  
  	return 0;
}

void put(HashTable *hashTable, Key key, Value value) {
   	Element* new_element = malloc(sizeof(Element));
   	new_element->value = value;
   	new_element->key = key;
   	new_element->next = NULL;

   	if(exists(hashTable, key)) {
   		new_element->value = get(hashTable, key);
   		new_element->value++;
   		deleteKey(hashTable, key);
   	}

   	int index = hashTable->hashFunction(key, hashTable->size);
   	new_element->next = hashTable->elements[index];
   	hashTable->elements[index] = new_element;
}

void deleteKey(HashTable *hashTable, Key key) {
	int index = hashTable->hashFunction(key, hashTable->size);
  	Element* p = hashTable->elements[index];
  	Element* prev = NULL;

	while(p != NULL) {
  		if(!strcmp(p->key, key)) {
  			if(prev == NULL) {
  				Element* temp = hashTable->elements[index];
  				hashTable->elements[index] = hashTable->elements[index]->next;
  				free(temp);
  			} else {
  				prev->next = prev->next->next;
  				free(p);
  			}

  			break;
  		}

  		prev = p;
  		p = p->next;
	}
}

void print(HashTable *hashTable) {
	int i;
	for(i = 0; i < hashTable->size; i++){
	  	Element* p = hashTable->elements[i];

	  	printf("%d\n", i);

		while(p != NULL) {
	  		printf(" %d %s\n", p->value, p->key);

	  		p = p->next;
	  	}

	  	printf("\n");
  	}
}

void freeHashTable(HashTable *hashTable) {
  	int i;
	for(i = 0; i < hashTable->size; i++){
	  	Element* p = hashTable->elements[i];

		while(p != NULL) {
	  		Element* temp = p;
	  		p = p->next;
	  		free(temp);
	  	}
  	}

  	free(hashTable->elements);
  	free(hashTable);
}


long hash1(Key word, long size) {
	int h = 0;

	int length = strlen(word) - 1;
	int i;
	for(i = 0; i < length; i++) {
		h = h * 17 + word[i];
	}

	// pentru cameleon imi iese iese indexul negativ
	int index = h%size;
	if (index >= 0) {
		return index;
	} else {
		return -index;
	}
}

int main(int argc, char* argv[]) {
  HashTable *hashTable, *hashTable2;
  FILE *f1, *f2;
  char word[256];
  long hashSize;
  int common = 0;

  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

  initHashTable(&hashTable, hashSize, &hash1);
  initHashTable(&hashTable2, hashSize, &hash1);

  	while (fscanf(f1, "%s", word) == 1) {
  		char* cuvant = strdup(word);
  		if (cuvant != NULL) {
  			put(hashTable, cuvant, 1);
  		}
  	}

  	while (fscanf(f2, "%s", word) == 1) {
  		char* cuvant = strdup(word);
  		if (cuvant != NULL) {
  		  	put(hashTable2, cuvant, 1);
  		}
  	}

  	int i;
	for(i = 0; i < hashTable->size; i++){
	  	Element* p = hashTable->elements[i];

		while(p != NULL) {
	  		if(exists(hashTable2, p->key)) {
	  			common += p->value;
	  		}

	  		p = p->next;
	  	}
  	}

  printf("Common words: %d\n", common);

  fclose(f1);
  fclose(f2);
  return 0;
}
