/*----------------------------------------------
 * Author: Renata Del Vecchio 
 * Date: 4/12/2023
 * Description: Creates a buddhabrot set image by splitting the task of filling the
 * pixels into 4 child processes.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include "read_ppm.h"
#include "write_ppm.h"

int maxCount = 0; 
pthread_mutex_t mutex; 
pthread_barrier_t barrier; 

/*
* a structure which stores data to be passed into each thread.
*/
struct data {
  int thisThreadNum; // which thread is this? 
  int maxIterations;
  int numProcesses;
  int size;
  float xmin;
  float xmax;
  float ymin;
  float ymax;
  struct ppm_pixel* pallet;
  struct ppm_pixel* pixels;
  struct ppm_pixel black; // a pixel just storing the color black
  int* membership; 
  int* counts; 
};

/*
* A function that fills a section of the pixel array with the mandelbrot set. 
* @param givenThreadData
* @return NULL; 
*/
void* fillPixels (void* givenThreadData) {
  struct data* threadData = (struct data*) givenThreadData; // cast thread into a form we can read: 
  // decide where to start writing for each thread: 
  int rowStart = 0;
  int colStart = 0;
  if ( threadData -> thisThreadNum == 2 || threadData -> thisThreadNum  == 3) {
    rowStart = 0.5* threadData->size;
  }
  if ( threadData -> thisThreadNum == 1 || threadData -> thisThreadNum == 3) {
    colStart = 0.5* threadData->size;
  }
  float xfrac, yfrac, x0, y0, x, y, xtmp;
  int iter; // number of iterations
  int rStart = rowStart;
  int rEnd = rStart + (threadData -> size / sqrt(threadData -> numProcesses));
  int cStart = colStart;
  int cEnd = cStart + (threadData -> size / sqrt(threadData -> numProcesses));
  printf("Thread %d) sub-image block: cols (%d, %d) to rows (%d, %d)\n",
                  threadData -> thisThreadNum,
                  cStart, cEnd, rStart, rEnd);

  // determine set membership: 
  for (int r = rStart; r < rEnd; r++ ) { // for each row:
    for (int c = cStart; c < cEnd; c++) { // for each column:
      xfrac = r / (float)(threadData -> size);
      yfrac = c / (float)(threadData -> size);
      x0 = threadData -> xmin + xfrac * (threadData -> xmax - threadData -> xmin);
      y0 = threadData -> ymin + yfrac * (threadData -> ymax - threadData -> ymin);
      x = 0;
      y = 0;
      iter = 0;
      while (iter < threadData -> maxIterations && x*x + y*y < 2*4) {
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
      }
      if (iter < threadData -> maxIterations) { // escaped
        // write with a color corresponding to how many iterations it took to escape.
        /*threadData -> pixels[c*(threadData -> size) + r] =
                      threadData -> pallet[iter];*/
        threadData -> membership[c*(threadData -> size) + r] = 0; // not a member. 
      }
      else { // if didn't escape (in the mandelbrot set.) 
        /*threadData -> pixels[c*(threadData -> size) + r] =
                      threadData -> black; // write with black.*/
        threadData -> membership[c*(threadData -> size) + r] = 1; // is a member; 
      }
    } // end inner for loop for mandelbrot process.
  } // end outer for loop for mandelbrot process.
  
  // step 2: compute visited counts: 
  for (int r = rStart; r < rEnd; r++ ) { // for each row:
    for (int c = cStart; c < cEnd; c++) { // for each column:
      if (threadData -> membership[c*(threadData -> size) + r]) { // if member:
        continue; // do nothing
      }
      xfrac = r / (float)(threadData -> size);
      yfrac = c / (float)(threadData -> size);
      x0 = threadData -> xmin + xfrac * (threadData -> xmax - threadData -> xmin);
      y0 = threadData -> ymin + yfrac * (threadData -> ymax - threadData -> ymin);

      x = 0;
      y = 0;
      while (iter < threadData -> maxIterations && x*x + y*y < 2*4) {
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        
        int yrow = round(threadData -> size * (y - threadData -> ymin) 
                          / (threadData -> ymax - threadData -> ymin));
        int xcol = round(threadData -> size * (x - threadData -> xmin) 
                          / (threadData -> xmax - threadData -> xmin));        
        
        if (yrow < 0 || yrow >= threadData -> size) continue; // out of range. 
        if (xcol < 0 || xcol >= threadData -> size) continue; // out of range. 
        
        threadData -> counts [c*(threadData -> size) + r] ++;       
        //update max count:
        pthread_mutex_lock(&mutex); 
        if (threadData -> counts [c*(threadData -> size) + r] > maxCount) { 
          maxCount = threadData -> counts [ c*(threadData -> size) + r]; 
        }
        pthread_mutex_unlock(&mutex); 
      }
    }
  }
 
  printf("Should have gotten to this point! Thread %d is waiting now:", threadData -> thisThreadNum);  
  pthread_barrier_wait (&barrier); 
  // at this point, all three threads should have completed. 
  printf("Should have gotten to this point! Thread %d is done", threadData -> thisThreadNum);
   
  return NULL;
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);
  // todo: your work here
  // start timing: 
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);

  // create pixel pallet of colors:
  struct ppm_pixel* pallet = malloc(sizeof(struct ppm_pixel) * maxIterations);
  srand(time(0)); // use a semi-random seed so the colors are diff each time.
  for (int i = 0; i < maxIterations; i ++ ) { // generate each color randomly:
    pallet[i].red = rand() % 255;
    pallet[i].green = rand() % 255;
    pallet[i].blue = rand() % 255;
  }
  struct ppm_pixel black; // initialize a black color to use for numbers in the 
  black.red = 0;
  black.green = 0;
  black.blue = 0;

  // create a struct to store the final array of pixels to write to the image:
  struct ppm_pixel* pixels = malloc(sizeof(struct ppm_pixel) * size * size);
  int* membership = malloc(sizeof(int) * size * size); // 1 if pixel is member, else 0
  int* counts = malloc(sizeof(int) * size * size); 
  pthread_t threads[4];  
  pthread_mutex_init(&mutex, NULL); 
  pthread_barrier_init(&barrier, NULL, 4); 

  for (int i = 0; i < 4; i++ ) { // for each of the 4 quadrants of the image: 
    // initialize a struct to store information passed into the thread: 
    struct data threadData;
    threadData.thisThreadNum = i;
    threadData.numProcesses = numProcesses;
    threadData.maxIterations = maxIterations;
    threadData.size = size;
    threadData.pixels = pixels;
    threadData.black = black;
    threadData.pallet = pallet;
    threadData.xmin = xmin;
    threadData.xmax = xmax;
    threadData.ymin = ymin;
    threadData.ymax = ymax;
    threadData.membership = membership;
    threadData.counts = counts; 
    pthread_create(&threads[i], NULL, fillPixels, &threadData);
  } // end 4 quadrants for loop

  for (int i = 0; i < 4; i ++ ) { 
    pthread_join(threads[i], NULL);
  }
  
  pthread_mutex_destroy(&mutex); 
  // stop timing: 
  gettimeofday(&tend, NULL);
  char filename[100]; // make a big array to fill in with the filename. 
  strcpy(filename, "mandelbrot-");
  char buffer[sizeof(int) * 32 + 1]; // buffer to hold the number.
  sprintf(buffer, "%d", size); // place the size number into the buffer string.
  strcat(filename, buffer); // add to the filename.
  strcat(filename, "-");
  sprintf(buffer, "%ld", time(0)); // add the timestamp to buffer.
  strcat(filename, buffer); // add the timestamp to the filename.
  strcat(filename, ".ppm"); // add the file extension to the filename.

  // turn the time into a double that we can easily print: shows elapsed seconds:   
  double timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  write_ppm(filename, pixels, size, size); // write to file.
  printf("Computed mandelbrot set (%dx%d) in %f seconds\n", size, size, timer);
  printf("Writing file: %s\n", filename);
  free(pallet);
  free(pixels);
}

