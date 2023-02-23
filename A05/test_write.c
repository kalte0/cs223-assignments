/*----------------------------------------------
 * Author: Renata Del Vecchio
 * Date: 2/22/2023
 * Description a small program which tests the functionality of the
 * "write_ppm" function in the "write_ppm" file. 
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

/*
* a function which prints the values of a 2d array of pixel structs
* @param pixels the 2d array of ppm_pixel structs
* @param w the width of the passed in 2d array 
* @param h the height of the passed in 2d array
*/
void printPixelArray(struct ppm_pixel* pixels, int w, int h) {
  if (pixels == NULL ) { // if the array passed in does not exist
    printf("given array is NULL, cannot print\n");
    return;
  }
  // for each pixel in the 2d array 
  for (int i = 0; i < w; i++ ) {
    for (int j = 0; j < w; j++ ) {
      struct ppm_pixel pixel = pixels[i*(w) + j]; // store the pixel
      // print the values of the pixel: 
      printf("(%d, %d, %d) ", pixel.red, pixel.green, pixel.blue);
    }
    printf("\n");
  }
}

int main(int argc, char** argv) {
  int w, h;
  // store the two files to be read/written as a test: 
  const char* fileToRead = "feep-raw.ppm"; 
  const char* fileToWrite = "test.ppm"; 
  // read from the given file: 
  struct ppm_pixel* pixels = read_ppm(fileToRead, &w, &h);
  printf("Testing file %s: %d %d\n", fileToRead, w, h); 
  // write that value to a different file: 
  write_ppm(fileToWrite, pixels, w, h);  
  // read what we've just written: 
  struct ppm_pixel* pixelsPostWrite = read_ppm(fileToWrite, &w, &h);
  // print out the values that we wrote: 
  printPixelArray(pixelsPostWrite, w, h); 
  free(pixels);
  free(pixelsPostWrite); 
  return 0;
}
