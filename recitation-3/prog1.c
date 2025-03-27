#include <stdlib.h>

int multiply_by_2(int* p) {
  *p = *p * 2;
  return *p;
}

int main() {
  int n = 10, x = 16, y = 32, z = 64;
  int* p1 = &x;
  int* a = malloc(n * sizeof(int));
  int* p2;

  for (int i = 0; i < n; i++) {
    a[i] = i;
  }

  p2 = a + (n / 2);
  *p2 = 0;

  z = multiply_by_2(&x);
  y = multiply_by_2(p1);
  free(a);
}
