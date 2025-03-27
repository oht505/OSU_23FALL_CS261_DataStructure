/*
 * This file contains two different versions of a function to compute the sum
 * of all integers between 1 and n, i.e. 1 + 2 + 3 + ... + n.  One of them
 * computes the sum iteratively (using a loop).  You must implement the other
 * to compute the sum recursively.
 */

#include <stdio.h>

/*
 * This function computes and returns the sum of all integers between 1 and n.
 * It does so iteratively (i.e. using a loop).
 */
int iterative_sum(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

/*
 * Implement this function so it *recursively* computes and returns the sum of
 * all integers between 1 and n.  In other words, this function should do the
 * same thing as iterative_sum() above, but recursively instead of iteratively.
 */
int recursive_sum(int n) {
    return 0;
}

int main() {
    for (int i = 2; i <= 20; i+= 2) {
        printf("sum from 1 to %d = ", i);
        printf("\t%d (iterative)", iterative_sum(i));
        printf("\t\t%d (recursive)\n", recursive_sum(i));
    }

    return 0;
}
