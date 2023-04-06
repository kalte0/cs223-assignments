/*------------------------------------------------
* Author: Renata Del Vecchio
* Date: 3/29/2023
* Description: Creates a mandelbrot set image by dividing the work into 4 threads.
------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
  
struct valData { 
  int* valsToSearch; 
  int thisThreadNum; 
  int numThreads;  
  int indexFound; 
  int valToFind;
  int numVals;
};

void* findVal(void* dataStruct) {
  struct valData *data = (struct valData*) dataStruct;
  int startIndex = data->thisThreadNum * (data-> numVals/data->numThreads); 
  int endIndex = startIndex + (data -> numVals / data-> numThreads);
  //printf("Thread %d searching from %d to %d\n", data ->thisThreadNum, 
   //      startIndex, endIndex);
  for (int i = startIndex; i < endIndex; i ++ ) { 
    if (data->valsToSearch[i] == data->valToFind) { 
      data->indexFound = i; 
      //printf("found at index %d\n", i); 
      break;
    } 
  }
  return NULL; 
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("usage: %s <NumThreads>\n", argv[0]);
    exit(0);
  }
  // read in the binary data:
  int numVals;
  FILE* fp = fopen("data.bin", "rb");
  fread(&numVals, sizeof(int), 1, fp); // read how many values there will be
  int* values = malloc(sizeof(int) * numVals);// malloc an array of that size.
  fread(values, sizeof(int), numVals, fp); // then read it: 
  fclose(fp);// close file when done

  printf("Enter a value to search: ");
  int valToFind;
  scanf("%d", &valToFind);

  // create the given number of threads to do the work: 

  int found = 0; 
  for (int i = 0; i < atoi(argv[1]); i ++ ) { 
    pthread_t thisThread; 
    struct valData data; // make a struct to store all the information.
    data.valsToSearch = values; 
    data.numThreads = atoi(argv[1]); 
    data.indexFound = -1; 
    data.valToFind = valToFind;
    data.numVals = numVals; 
    data.thisThreadNum = i; 
    pthread_create(&thisThread, NULL, findVal, &data); // getting warning that this is an implicit declaration, but isn't this linked in with the pthread library? 
    pthread_join(thisThread, NULL);
    if ( data.indexFound != -1) { // if they found it:
      printf("Thread %d found %d at index %d\n", i, valToFind, data.indexFound); 
      found = data.indexFound;  
    }
  }
  if (found == 0) { // if was never found:
    printf("Not found!\n");  
  } 
  free(values);
  return 0;
}
