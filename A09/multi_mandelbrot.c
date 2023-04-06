/*----------------------------------------------
 * Author: Renata Del Vecchio 
 * Date: 3/29/2023
 * Description: Creates a mandelbrot set image by splitting the task of filling the
 * pixels into 4 child processes, utilizing shared memory. 
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
#include "read_ppm.h"
#include "write_ppm.h"

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
  int shmid = shmget(IPC_PRIVATE, sizeof(struct ppm_pixel) * size * size, 0644
     | IPC_CREAT); 
  if (shmid == -1) { 
    perror("Error cannot initialize shared memory\n"); 
    exit(1); 
  }
  struct ppm_pixel* pixels = shmat(shmid, NULL, 0); 
  for (int i = 0; i < 4; i++ ) { // for each of the 4 quadrants of the image: 
    int rowStart, colStart = 0; 
    if ( i == 2 || i == 3) { 
      rowStart = 0.5*size; 
    }
    if ( i == 1 || i == 3) { 
      colStart = 0.5*size; 
    } 
    int pid = fork(); 
    if (pid == 0) { // if child: 
      float xfrac, yfrac, x0, y0, x, y, xtmp;
      int iter; // number of iterations
      for (int r = rowStart; r < rowStart + 0.5*size; r++ ) { // for each row:
        for (int c = colStart; c < colStart + 0.5*size; c++) { // for each column:
          xfrac = r / (float)(size);
          yfrac = c / (float)(size);
          x0 = xmin + xfrac * (xmax - xmin);
          y0 = ymin + yfrac * (ymax - ymin);
          x = 0;
          y = 0;
          iter = 0;
          while (iter < maxIterations && x*x + y*y < 4*4) {
            xtmp = x*x - y*y + x0;
            y = 2*x*y + y0;
            x = xtmp;
            iter++;
          }
          if (iter < maxIterations) { // escaped
            // write with a color corresponding to how many iterations it took to escape.
            pixels[c*size + r] = pallet[iter];
          }
          else { // if didn't escape (in the mandelbrot set.) 
            pixels[c*size + r] = black; // write with black.
          }
        } // end inner for loop for mandelbrot process.
      } // end outer for loop for mandelbrot process.
      exit(0); 
    }
  } // end 4 quadrants for loop
  
  for (int i = 0; i < 4; i++) {
    int status;
    int pid = wait(&status);
  }

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

  if (shmdt(pixels) == -1) {
    perror("Error: cannot detach from shared memory\n");
    exit(1);
  }

  if (shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("Error: cannot remove shared memory\n");
    exit(1);
  }   
}
