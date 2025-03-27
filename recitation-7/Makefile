CC=gcc --std=c99 -g

all: factorial fibonacci simple_sum digit_sum binary_search

factorial: factorial.c
	$(CC) factorial.c -o factorial

fibonacci: fibonacci.c
	$(CC) fibonacci.c -o fibonacci

simple_sum: simple_sum.c
	$(CC) simple_sum.c -o simple_sum

digit_sum: digit_sum.c
	$(CC) digit_sum.c -o digit_sum

binary_search: binary_search.c
	$(CC) binary_search.c -o binary_search

clean:
	rm -f *.o factorial fibonacci simple_sum digit_sum binary_search
	rm -rf *.dSYM
