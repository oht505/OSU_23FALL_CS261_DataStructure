/*
 * This file contains two different versions of the factorial function (n!).
 * One of them computes the factorial iteratively (using a loop), and the
 * other computes the factorial recursively.
 */

#include <stdio.h>

/*
 * This function computes and returns the factorial of n.  It does so
 * iteratively, i.e. using a loop.
 */
int iterative_factorial(int n) {
    int f = 1;
    for (int i = 1; i <= n; i++) {
        f *= i;
    }
    return f;
}

/*
 * This function computes and returns the factorial of n.  It does so
 * recursively
 */
int recursive_factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * recursive_factorial(n - 1);
}

int main() {
    for (int i = 2; i <= 10; i+= 2) {
        printf("%d! = ", i);
        printf("\t%d (iterative)", iterative_factorial(i));
        printf("\t\t%d (recursive)\n", recursive_factorial(i));
    }

    return 0;
}
