/*----------------------------------------------
 * Author: Renata Del Vecchio
 * Date: 2/22/2023
 * Description an implementation of a function which writes to a ppm file. 
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

/* 
* a function which writes the information of a 2d array of ppm_pixel structs
* to a ppm file, along with a proper header. 
* @param filename the name of the file to write to. 
* @param pixels the 2d array of ppm_pixel structs to write. 
* @param w the width of the passed in 2d array. 
* @param h the height of the passed in 2d array. 
*/
void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
  FILE *fp = fopen(filename, "wb");  
  fprintf(fp, "P6\n"); // write that it's a binary file. 
  fprintf(fp, "# Created by GIMP version 2.1 0.24 PNM plug-in\n"); // comment
  fprintf(fp, "%d %d\n", w, h); // write the size of the pixel 2d array
  fprintf(fp, "255\n"); // maximum color value. 
  fwrite(pixels, sizeof(struct ppm_pixel), w*h, fp); // write 2darray of pixels
  fclose(fp); // close file when done. 
}

/* 
* an alternate implementation of the write_ppm function, which has not been
* implemented. 
* @param pixels the 2d array of ppm_pixel structs to write. 
* @param w the width of the passed in 2d array. 
* @param h the height of the passed in 2d array. 
*/
void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {

}
