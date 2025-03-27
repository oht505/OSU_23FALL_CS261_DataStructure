/*
 * This file contains two different versions of the binary search function.
 * One of them is the iterative version of binary search we talked about in
 * lecture.  You must implement a recursive version of binary search.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 32

/*
 * This function performs a binary search for a query value q in an array of
 * integers of size n and returns the array index where q is found or -1 if
 * the array does not contain q.  It operates iteratively (i.e. using a loop).
 */
int iterative_binary_search(int q, int* array, int n) {
    int mid, low = 0, high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (array[mid] == q) {
            return mid;
        } else if (array[mid] < q) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
  return -1;
}

/*
 * Implement this function so it *recursively* performs a binary search for
 * a query value q in an array of integers of size n.  Like the iterative
 * version above, this version should return the array index where q is found
 * or -1 if q is not in the array.
 *
 * Note: it is possible to implement the recursive version of binary search
 * using the signature of this function.  However, if you find it easier, feel
 * free to implement a recursive "helper" function with a different signature
 * and to simply call that recursive function from this one.
 */
int recursive_binary_search(int q, int* array, int n) {

    int low = 0, high = n - 1;

  return helper(q, array, low, high);
}
int helper(int q, int* array, int low, int high) {
    int mid, low = low, high = high;
    mid = (low + high) / 2;
    
    if (array[mid] == q) {
        return mid;
    }
    else if (array[mid] > q) {
        return helper(q, array, low, mid);
    }
    else {
        return helper(q, array, mid, high);
    }

    return -1;
}

/*
 * This is a comparison function used with qsort() to sort the array of
 * integers that's used to test the binary search functions.  You don't need
 * to edit this function.
 */
int cmp(const void * a, const void * b) {
   return *(int*)a - *(int*)b;
}

/*
 * This function prompts the user to input a number to search for.  It converts
 * the user's input to an integer and returns it.  Returns -1 if the user
 * wants to quit.  You don't need to edit this function.
 */
int get_q_from_user() {
    char input[MAX_INPUT_LEN];
    printf("\nEnter a number to search for in the array above (ctrl-d to quit): ");
    if (fgets(input, MAX_INPUT_LEN, stdin) != NULL) {
        return atoi(input);
    } else {
        return -1;
    }
}

int main() {
    int n = 16;
    int* array = malloc(n * sizeof(int));

    /*
     * Initialize the array with random numbers and sort it.
     */
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 100;
    }
    qsort(array, n, sizeof(int), cmp);

    printf("This is your array of numbers:\n  [");
    for (int i = 0; i < n - 1; i++) {
        printf(" %d,", array[i]);
    }
    printf(" %d ]\n", array[n-1]);

    /*
     * Continue to ask the user for numbers to search for in the array until
     * they no longer want to search for numbers.
     */
    int q = get_q_from_user();
    while (q != -1) {
        printf("-- Index of %4d:\t%d (iterative)\t%d (recursive)\n", q,
            iterative_binary_search(q, array, n),
            recursive_binary_search(q, array, n));
        q = get_q_from_user();
    }

    printf("\nBye!\n");
    free(array);
    return 0;
}
