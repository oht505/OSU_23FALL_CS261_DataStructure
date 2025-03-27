/*
 * This file contains two different versions of a function to compute the sum
 * of the digits of an integer n.  For example, the digit-sum of the number
 * 123 is 1 + 2 + 3 = 6.  One version of the function computes the sum
 * iteratively (using a loop).  You must implement the other to compute the
 * sum recursively.
 */

#include <stdio.h>

#define TEST_DATA_SIZE 8
const int test_data[TEST_DATA_SIZE] =
    { 123, 456, 1101, 31415, 98765, 5, 0, 1000000 };

/*
 * This function computes and returns the sum the digits of n.  It does so
 * iteratively (i.e. using a loop).
 */
int iterative_digit_sum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n = n / 10;
    }
    return sum;
}

/*
 * Implement this function so it *recursively* computes and returns the sum of
 * the digits in n.  In other words, this function should do the same thing as
 * iterative_digit_sum() above, but recursively instead of iteratively.
 */
int recursive_digit_sum(int n) {
    
    if (n == 0) {
        return 0;
    }

    return n%10 + recursive_digit_sum(n/10);
}

int main() {
    for (int i = 0; i < TEST_DATA_SIZE; i++) {
        printf("digit_sum(%7d) = ", test_data[i]);
        printf("\t%d (iterative)", iterative_digit_sum(test_data[i]));
        printf("\t\t%d (recursive)\n", recursive_digit_sum(test_data[i]));
    }

    return 0;
}
