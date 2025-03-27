#include <stdlib.h>

struct product {
  char* name;
  float price;
};

struct product* create_product(char* name, float price) {
  struct product* p = malloc(sizeof(struct product));
  p->name = malloc((1 + strlen(name)) * sizeof(char));
  strcpy(p->name, name);
  p->price = price;
  return p;
}

int main() {
  int i, n = 5;
  struct product** products = malloc(n * sizeof(struct product*));
  
  for (i = 0; i < n; i++) {
    products[i] = create_product("A product name", 32.99);
  }
  
  for (i = 0; i < n; i++) {
    free(products[i]);
  }
  free(products);
}
