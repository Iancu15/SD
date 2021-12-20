#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

/*
  OrderedSet represents a set with elements of type T stored in memory
  in an ordered fashion.
*/

typedef struct OrderedSet {
  T* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

// -----------------------------------------------------------------------------

/*
  Function that creates an OrderedSet with elements of type T with a given
  initial capacity.
*/

OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet->size = 0;                        // initially, the set is empty
  newSet->capacity = initialCapacity;
  newSet->elements = (T*) malloc(initialCapacity * sizeof(T));

  return newSet;
}

// -----------------------------------------------------------------------------

/*
  Function that checks if an element exists in a given set. As the
  elements of the set are ordered in memory, this function uses binary
  search.

  Function returns 1 if the given element exists in the set, and 0
  otherwise.
*/

int cautarebinara(T *v, int f, int l, T x){
  if(l>=f){
    int mid = f + (l-f)/2;
    if(v[mid]==x){
      return 1;
    } else if (v[mid]<x) {
      return cautarebinara(v, mid + 1, l, x);
    } else {
      return cautarebinara(v, f, mid - 1, x);
    }
  }
  return 0;
}

int contains(OrderedSet* set, const T element) {
  return cautarebinara(set->elements, 0, set->size-1, element); 
}

// -----------------------------------------------------------------------------

/*
  Function that adds a new element to a set. If the element was
  already in the set, nothing changes. Otherwise, the element is added
  to the set. In the end, the elements must be in ascending order.
*/

void realocare(OrderedSet* set){
  set->capacity *= 2;
  set->elements = realloc(set->elements, set->capacity*sizeof(T));
}

void add(OrderedSet* set, const T newElement) {
  if(set->size==0){
    set->size++;
    set->elements[0]=newElement;
  }
  else{
  if(contains(set, newElement)) return;
  if(set->size == set->capacity){
    realocare(set);
  }
  set->size++;
  int i;
  for(i=0; i<set->size-1; i++){
    if(set->elements[i]>newElement)break;
  }
  int j;
  for(j=set->size-1; j>=i; j--){
    set->elements[j+1]=set->elements[i];
  }
  set->elements[i]=newElement;
  }
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the union of
  the two
*/

void interclasare(*set, int j){
  char* nouset;
  int i=0;
  int m=(i+j)/2
  int x=i;
  int k=0;
  int y=m+1;
  while(x<=m && y<j){
    if(a[x]<a[y]){
      nouset->elements[k++]=set->elements[x++];
    } else {
      nouset->elements[k++]=set->elements[y++];
    }
  }
  while(x<=m){
    nouset->elements[k++]=set->elements[x++];
  }
  while(y<j){
    nouset->elements[k++]=set->elements[y++];
  }
  int l=0;
  for(k=0; k<j-i;k++){
    set->elements[l++]=nouset->elements[k];
  }
}

OrderedSet* unionOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  OrderedSet* set;
  set->capacity=s1->capacity+s2->capacity;
  set->size=s1->size+s2->size;
  set = createOrderedSet(set->capacity);
  int i;
  for(i=0; i<s1->size; i++){
    set->elements[i]=s1->elements[i];
  }
  int j;
  for(j=0;j<s2->size;j++){
    set->elements[i]=s2->elements[j];
  }
  interclasare(set, set->size);
  return set;
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the
  intersection of the two
*/

OrderedSet* intersectOrderedSets(OrderedSet* s1, OrderedSet* s2) {
  OrderedSet* set;
  set->capacity=s1->capacity+s2->capacity;
  set->size=s1->size+s2->size;
  set = createOrderedSet(set->capacity);
  int i;
  for(i=0; i<s1->size; i++){
    set->elements[i]=s1->elements[i];
  }
  int j;
  for(j=0;j<s2->size;j++){
    if(!contains(set,s2->elements[j])){
      set->elements[i]=s2->elements[j];
      i++;
      set->size--;
    }
  }
  interclasare(set, set->size);
  return set;
}

// -----------------------------------------------------------------------------

#endif
