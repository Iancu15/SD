#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

typedef struct OrderedSet {
  int* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet->size = 0;                        // initially, the set is empty
  newSet->capacity = initialCapacity;
  newSet->elements = (int*) malloc(initialCapacity * sizeof(int));

  return newSet;
}

int multiplu(int f, int l, int m){
	OrderedSet* set=createOrderedSet(l-f);
	int i, j=0;
	for(i=f; i<l; i++){
		if(i%m==0){
			set->size++;
			set->elements[j++];
		}
	}
}

int main(){
	
}