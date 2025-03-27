/*
 * In this file, you should implement an application that compares the
 * performance of a dynamic array and a linked list, as described in the
 * README. Don't forget to include your name and @oregonstate.edu email
 * address below.
 *
 * Name: Hyun Taek, Oh
 * Email: ohhyun@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "dynarray.h"
#include "list.h"


#define TEST_DATA_SIZE 1000000

/*
 * This function generates and an array of random integers of size n.
 */
int* generate_random_array(int n) {
  int* arr = malloc(n * sizeof(int));
  int i;

  for (i = 0; i < n; i++) {
    arr[i] = rand();
  }

  return arr;
}

int main(int argc, char const* argv[]) {
    int* test_data = generate_random_array(TEST_DATA_SIZE);
    clock_t dyn_start_t, dyn_single, dyn_end_t;
    clock_t list_start_t, list_single, list_end_t;
    double dyn_total_t, dyn_single_t, list_total_t, list_single_t;

    /*
     * You should write code here to insert the data in test_data into a
     * dynamic array using the dynamic array interface you implemented.  As
     * you're doing this, measure two things:
     *   1. The total amount of time it takes to insert all the data into the
     *      dynamic array.
     *   2. The maximum amount of time it takes to insert any single element into
     *      the dynamic array.
     * To help with this, you can use the C functions time() and difftime()
     * from time.h.  Don't forget to include time.h above!
     */
    struct dynarray* da = dynarray_create();

    dyn_start_t = clock();

    for (int i = 0; i < TEST_DATA_SIZE; i++) {
        dynarray_insert(da, &test_data[i]);
        if (i == 0) {
            dyn_single = clock();
            dyn_single_t = dyn_single - dyn_start_t;
            
        }
    }

    dyn_end_t = clock();
    dyn_total_t = dyn_end_t - dyn_start_t;

    printf("Dynarray Total time : %.2f\n", dyn_total_t);
    printf("Dynarray Single time : %.2f\n", dyn_single_t);
    dynarray_free(da);


    /*
    * You should write code here to insert the data in test_data into a
    * linked list using the linked list interface you implemented.  As
    * you're doing this, measure two things:
    *   1. The total amount of time it takes to insert all the data into the
    *      linked list.
    *   2. The maximum amount of time it takes to insert any single element into
    *      the linked list.
    * Again, you can use the C functions time() and difftime() from time.h to
    * help with this.
    *
    * How do the times associated with the dynamic array compare to the times
    * associated with the linked list?  How does this change if you modify the
    * value of TEST_DATA_SIZE above?
    */

    struct list* ll = list_create();

    list_start_t = clock();

    for (int i = 0; i < TEST_DATA_SIZE; i++) {
        list_insert(ll, &test_data[i]);
        if (i == 0) {
            list_single = clock(); 
            list_single_t = list_single - list_start_t;
        }
    }

   list_end_t = clock();
   list_total_t = list_end_t - list_start_t;

   printf("List Total time : %.2f\n", list_total_t);
   printf("List Single time : %.2f\n", list_single_t);
   list_free(ll);

  free(test_data);
  
  return 0;
    
}
