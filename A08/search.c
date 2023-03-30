/*----------------------------------------------
 * Author: Renata Del Vecchio 
 * Date: 3/29/2023
 * Description: Reads in a binary file, data.bin, and then splits the work 
 * of searching for a user-given number in an array between a parent and child process. 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int numVals;  
  FILE* fp = fopen("data.bin", "rb"); 
  fread(&numVals, sizeof(int), 1, fp); 
  int* values = malloc(sizeof(int) * numVals); 
  fread(values, sizeof(int), numVals, fp); 
  fclose(fp); 
  printf("Enter a value to search: "); 
  int valToFind;
  scanf("%d", &valToFind); 
 
  int pid = fork(); 
  if (pid) { // if parent: 
    char found = 0;  
    for (int i = 0; i < numVals/2; i++ ) { // for the first half of data:
      if (values[i] == valToFind) { 
        printf("Parent found %d at index %d\n", valToFind, i); 
        found = 1; // mark as found
      }
    }
    if (found == 0) { // if wasn't found:
      printf("Not found!\n"); 
    } 
  } else { // if child:
    char found = 0; 
    for (int i = numVals/2; i < numVals; i++ ) { // for the second half of data:
      if (values[i] == valToFind) { 
        printf("Child found %d at index %d\n", valToFind, i); 
        found = 1;  // mark as found.
      }
    }
    if (found == 0) { // if wasn't found:
      printf("Not found!\n"); 
    } 
  }
  free(values); 
  return 0;
}
