/*----------------------------------------------
 * Author: Renata Del Vecchio 
 * Date: 2/21/2023
 * Description implements a function which, given a filename and a width and 
 * height, creates a 2d array of pixel structs. 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"
#define SIZE 1024 // size of our buffer string for reading lines from document.

// Choose *one* to implement (do not remove the other one!)

/* 
* a function which reads a 2d array of pixels from a given ppm file
* @param filename the name of the binary file to read from. 
* @param w a pointer to the number of colums in the 2d array. 
* @param h a pointer to the number of rows in the 2d array. 
* @return a 2d array of ppm_pixel structs read from the file. 
*/ 
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *fp = NULL; 
  fp = fopen(filename, "rb");  
  if (fp == NULL) { // if could not open the given file: 
    printf("file could not be found"); 
    exit(0); 
  }
  char buffer[SIZE]; //
  fgets(buffer, SIZE, fp); // P6, says it's a binary file. 
  fgets(buffer, SIZE, fp); // Comment
  fgets(buffer, SIZE, fp); // width and height. 
  *w = atoi(strtok(buffer, " ")); // store width
  *h = atoi(strtok(buffer, " ")); // store height
  fgets(buffer, SIZE, fp); // maximum color value
  // create 2d array of pixel structs:
  struct ppm_pixel* pixels = malloc(sizeof(struct ppm_pixel) * (*w) * (*h));
  // read binary into the created array.  
  fread(pixels, sizeof(struct ppm_pixel), (*w) * (*h), fp);
  fclose(fp); // close file when done
  return pixels;
}

/*
* an alternate implementation of read_ppm which has not been implemented. 
* @param filename the name of the file that would be read if this was implemented
* @param w the number of columns in the array if this was to be implemented
* @param h the number of rows in the array if this was to be implemented. 
* @return a 2d array of ppm_pixel structs read from the file. 
*/
struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
  return NULL;
}


