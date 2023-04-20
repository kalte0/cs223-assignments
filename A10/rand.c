/* --------------
* name: Renata Del Vecchio
* date: 4/29/2023
* description: utilities for generating random sizes of memory.
------------------*/ 

#include <stdlib.h>
#include <math.h>

#define MAX 4000
#define MIN 8 

/*
* returns a size that mirrors the request patterns of real data for malloc
* @return int a size of information to malloc. 
*/
int request() { 
  double k = log(((double) MAX) / MIN); 
  double r = ((double)( rand() % (int)(k*10000))) / 10000; 
  int size = (int) ((double) MAX / exp(r)); 
  return size; 
}

/* 
* returns a random value in the range min - max. 
* @param min the minimum value in the range of random values. 
* @param max the maximum value in the range of random values. 
* @return a random value in the range min - max. 
*/
int randRange(int min, int max) {
  int size = (int) (rand() % (max-min) + min);
  return size;
}

/*
* returns a random value in the range min - max with an exponential distribution.  
* @param min the minimum value in the range of random values to be selected. 
* @param max the maximum value in the range of random values to be selected. 
* @return int a random value in ther ange min - max
*/
int randExp(int min, int max) {
  double k = log(((double) max)/min);
  double r = ((double) (rand() % (int)(k*10000))) / 10000;
  int size = (int) ((double) max / exp(r));
  return size;
}
