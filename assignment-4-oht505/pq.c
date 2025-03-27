/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: HyunTaek Oh
 * Email: ohhyun@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
  struct dynarray* da;
};
struct node{
  void* value;
  int p;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  if (pq){
      pq->da = dynarray_create();
      return pq;
  }else{
    printf("Fail to create pq \n");
  }
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  if (pq){
      dynarray_free(pq->da);
      free(pq);
  }else{
    printf("No pq to free \n");
  }
  return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if (pq){
    return dynarray_size(pq->da)==0;
  }else{
    printf("No pq to check isempty \n");
  }
}

// Helper function to percolate pq
void pq_BottomUp_percolation(struct pq* pq){

  struct node* curr;
  struct node* parent;
  struct node* temp;
  int curr_idx = dynarray_size(pq->da)-1;
  int parent_idx = (curr_idx-1)/2;

  while (curr_idx>0){
    curr = dynarray_get(pq->da, curr_idx);
    parent = dynarray_get(pq->da, parent_idx);

    if(curr->p < parent->p){
      temp = curr;
      dynarray_set(pq->da, curr_idx, parent);
      dynarray_set(pq->da, parent_idx, temp);
    }

    curr_idx = parent_idx;
    parent_idx = (curr_idx-1)/2;
  }
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  if (pq){
    struct node* node = malloc(sizeof(struct node));
    node->value = value;
    node->p = priority;

    dynarray_insert(pq->da, node);
    pq_BottomUp_percolation(pq);
    
  }else{
    printf("No pq to insert data \n");
  }
  return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  if (pq){
    struct node* node = dynarray_get(pq->da, 0);

    return node->value;
  }else{
    printf("No pq \n");
  }
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
  if (pq){
    struct node* node = dynarray_get(pq->da, 0);
    return node->p;
  }else{
    printf("No pq \n");
  }
}

// Helper function to percolate pq

void pq_TopDown_percolation(struct pq* pq){

  int curr_idx = 0;
  struct node* curr = dynarray_get(pq->da, curr_idx);
  struct node* temp;
  int size = dynarray_size(pq->da)-1;

  while (2*curr_idx+1 <size){
    int l_idx = 2*curr_idx + 1;
    struct node* lc = dynarray_get(pq->da, l_idx);

    int r_idx = 2*curr_idx + 2;
    struct node* rc = dynarray_get(pq->da, r_idx);

    if (r_idx > size){
      struct node* rc = NULL;
    } else{
      struct node* rc = dynarray_get(pq->da, r_idx);
    }

    int minIdx;
    struct node* minNode;

    if(rc){
      if(lc->p > rc->p){
        minIdx = r_idx;
        minNode = rc;
      }else{
        minIdx = l_idx;
        minNode = lc;
      }
    }else{
       minIdx = l_idx;
       minNode = lc;
    }

    if(curr->p > minNode->p){

      temp = curr;
      dynarray_set(pq->da, curr_idx, minNode);
      dynarray_set(pq->da, minIdx, temp);
      curr_idx = minIdx;
    }else{
      break;
    }
  }
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  if (pq){
    struct node* node = dynarray_get(pq->da, 0);
    void* value = node->value;
    dynarray_set(pq->da, 0, dynarray_get(pq->da, dynarray_size(pq->da)-1));
    pq_TopDown_percolation(pq);
    free(node);
    dynarray_remove(pq->da, dynarray_size(pq->da)-1);

    return value;
  }else{
    printf("No pq to remove \n");
  }
}
