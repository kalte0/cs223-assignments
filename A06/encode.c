/*----------------------------------------------
 * Author: Renata Del Vecchio
 * Date: 3/1/2023
 * Description A program which reads a given ppm file, hides a user generated
 * message in the least significant digits of the colors of the image, and writes
 * the image with a message hidden in it into a new file with -encoded.ppm at the end
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) { // if one command line argument is not given: 
    printf("usage: encode <file.ppm>\n");
    return 0;
  }
  int w, h; 
  struct ppm_pixel* pixels = read_ppm(argv[1], &w, &h); 
  printf("Reading %s with width %d and height %d\n", argv[1], w, h); 
  int maxChars = w*h*3/8;
  // minus 1 because message must leave room for null character
  printf("Max number of characters in the image: %d\n", maxChars-1); 
  // read user inputted phrase: 
  printf("Enter a phrase: "); 
  char phrase[1024]; 
  scanf("%s", phrase); 
  // if the phrase is too long: 
  if (strlen(phrase) + 1 > maxChars) { 
    printf("Message is too large!\n"); // print an error message and exit. 
    return 0; 
  }
  // else: the phrase can fit: 
  unsigned char* pixelNumbers = (unsigned char*) pixels;
  for (int i = 0; i < strlen(phrase) * 8 + 8; i ++) { 
    if ((phrase[i/8] & 0x1<<(7-i%8)) >>(7-i%8)) { // if bit in phrase is 1
      pixelNumbers[i] = pixelNumbers[i]|0x1; // hide 1 in pixel
    }
    else { // if bit to hide is 0 
      pixelNumbers[i] = pixelNumbers[i]&0xFE; // hide 0 in pixel; 
    }
  }
  struct ppm_pixel* pixelsWithMessage = (struct ppm_pixel*) pixelNumbers;
  // make the file name of the place we'll write the image with hidden message: 
  char fileName[1024];  
  for (int i = 0; i < strlen(argv[1]) - 4; i ++ ) { 
    fileName[i] = argv[1][i]; //copy over everything but .ppm at the end. 
  } 
  fileName[strlen(argv[1]) -4] = '\0';
  printf("Writing file %s\n", strcat(fileName, "-encoded.ppm")); 
  write_ppm("feep-raw-encoded.ppm", pixelsWithMessage, 4, 4); 
  free(pixels); 
  return 0;
}
