/*----------------------------------------------
 * Author: Renata Del Vecchio
 * Date: 2/21/2023
 * Description a file which implements and tests the read_ppm
 * function in "read_ppm.c"
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

/* 
* a function which prints a given array of ppm_pixel structs. 
* @param pixels the 2d array of ppm_pixel structs to be printed. 
* @param w the width of the 2d array to be printed. 
* @param h the height of the 2d array to be printed. 
*/
void printPixelArray(struct ppm_pixel* pixels, int w, int h) { 
  if (pixels == NULL ) { // if the array pointer is null:  
    printf("given array is NULL, cannot print\n"); 
    return; 
  }
  // for each value in the 2d array. 
  for (int i = 0; i < w; i++ ) { 
    for (int j = 0; j < w; j++ ) { 
      struct ppm_pixel pixel = pixels[i*(w) + j]; // store the pixel
      // print the color values of the pixel: 
      printf("(%d, %d, %d) ", pixel.red, pixel.green, pixel.blue); 
    }
    printf("\n"); // go the next line between each row of the 2d array,
  }
}

int main() {
  int w, h;
  const char* fileToRead = "feep-raw.ppm";// store the name of the file to read. 
  struct ppm_pixel* pixels = read_ppm(fileToRead, &w, &h); // read the file
  printf("Testing file %s: %d %d\n", fileToRead, w, h); 
  printPixelArray(pixels, w, h); // print the read in 2d array:
  free(pixels);
  return 0;
}


