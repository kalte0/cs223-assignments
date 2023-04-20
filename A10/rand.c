#include <stdlib.h>
#include <math.h>

#define MAX 4000
#define MIN 8 

int request() { 
  double k = log(((double) MAX) / MIN); 
  double r = ((double)( rand() % (int)(k*10000))) / 10000; 
  int size = (int) ((double) MAX / exp(r)); 
  return size; 
}

int randRange(int min, int max) {
  int size = (int) (rand() % (max-min) + min);
  return size;
}

int randExp(int min, int max) {
  double k = log(((double) max)/min);
  double r = ((double) (rand() % (int)(k*10000))) / 10000;
  int size = (int) ((double) max / exp(r));
  return size;
}
