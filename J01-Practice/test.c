#include <stdio.h>

struct Snack { 
  char name[32]; 
  int quantity; 
  float cost; 
};

int main() { 
  struct Snack s; 
  printf("%li", sizeof(struct Snack)); 
  return 0; 
}

