#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"
#include "stack.h"

#define MAX_STR_LEN 256

/*
 * This function prompts the user for input and stores a maximum of `n`
 * characters of the string they enter into `dest`.  Any trailing line ending
 * characters are removed from the input string.  Returns 1 if a string was
 * successfully read from the user or 0 otherwise.
 */
int get_user_str(char* dest, int n) {
    printf("\nEnter a string, and we'll check whether it's a palindrome (ctrl-d to quit):\n");
    if (fgets(dest, MAX_STR_LEN, stdin) != NULL) {
        /*
         * If a string was successfully read from the user, remove any trailing
         * line ending characters.  Here's some documentation on strcspn() to help
         * understand how this works:
         *
         * https://en.cppreference.com/w/c/string/byte/strcspn
         */
        dest[strcspn(dest, "\r\n")] = '\0';
        return 1;
    }
    else {
        return 0;
    }
}

int main(int argc, char const* argv[]) {
    char* in = malloc(MAX_STR_LEN * sizeof(char));
    struct stack* s;
    struct queue* q;

    while (get_user_str(in, MAX_STR_LEN)) {
        /*
         * Inside this loop body, you'll have an input string from the user in `in`.
         * You should use your stack and your queue to test whether that string is
         * a palindrome (i.e. a string that reads the same backward as forward, e.g.
         * "ABCBA" or "Madam, I'm Adam").  For each string input by the user,
         * print a message letting the user know whether or not their string is
         * is a palindrome.
         *
         * When you test whether the user's string is a palindrome, you should
         * ignore any non-letter characters (e.g. spaces, numbers, punctuation,
         * etc.), and you should ignore the case of letters (e.g. the characters
         * 'a' and 'A' should be considered as equal).  The C functions isalpha()
         * and tolower() from ctype.h might help with this.
         */
        int flag = 0;

        s = stack_create();
        q = queue_create();

        for (int i = 0; i < strlen(in); i++) {
            if (isalpha(in[i]) != 0) {
                stack_push(s, &in[i]);
                queue_enqueue(q, &in[i]);
            }
            else {
                continue;
            }
        }

        while (!stack_isempty(s) && !queue_isempty(q)) {
            int* popped = stack_pop(s);
            int* dequeued = queue_dequeue(q);

            char popl = tolower((unsigned char)*popped);
            char deql = tolower((unsigned char)*dequeued);

            if (popl != deql) {
                printf("Your String is not plaindrome!\n");
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            printf("Your String is palindrome!\n");
        }

        stack_free(s);
        queue_free(q);

    }

    free(in);
    return 0;
}