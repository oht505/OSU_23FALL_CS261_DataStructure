/*
 * This file contains two different versions of a function to compute the n'th
 * number in the Fibonacci sequence.  One of them does this iteratively (using
 * a loop), and the other does so recursively.
 */

#include <stdio.h>

/*
 * This function computes and returns the n'th Fibonacci number.  It does so
 * iteratively, i.e. using a loop.
 */
int iterative_fibonacci(int n) {
    int f = 1, f1 = 0, f2 = 0;
    if (n == 0) {
        return 0;
    }
    for (int i = 1; i < n; i++) {
        f2 = f1;
        f1 = f;
        f = f1 + f2;
    }
    return f;
}

/*
 * This function computes and returns the n'th Fibonacci number.  It does so
 * recursively
 */
int recursive_fibonacci(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }
    return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
}

int main() {
    for (int i = 0; i <= 10; i++) {
        printf("F[%2d] =", i);
        printf("\t%d (iterative)", iterative_fibonacci(i));
        printf("\t%d (recursive)\n", recursive_fibonacci(i));
    }

    return 0;
}
