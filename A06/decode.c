/*----------------------------------------------
 * Author: Renata Del Vecchio
 * Date: 2/28/2023
 * Description a program which decodes a hidden message from a ppm file
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) { // if one command line argument is not given: 
    printf("usage: decode <file.ppm>\n");
    return 0;
  }
  int w, h; // will store the width and height of the pixel array to be read: 
  struct ppm_pixel* pixels = read_ppm(argv[1], &w, &h); // read the file
  printf("Reading %s with width %d and height %d\n", argv[1], w, h);  
  // max chars is num of r/g/b values/8 (can store a single bit in each char) 
  int maxChars = (w*h*3)/8; 
  printf("Max number of characters in the image: %d\n", maxChars); 
  unsigned char* pixelsBinary = (unsigned char*) pixels;
  char* message = malloc(sizeof(char) * maxChars); // store message to decode.
  for (int i = 0; i < maxChars; i ++) { 
    message[i] = 0; // fill everything in the message with 0:
  }
  for (int i = 0; i < (w*h*3)/8*8; i ++) {  // for each pixel
    // if the least significant digit of the pixel is 1: 
    if (pixelsBinary[i] & 0x1) { 
      // then write a 1 in that location to the message:
      message[i/8] = (0x1<<(7-(i%8)))|message[(int)(i/8)]; 
    }
    // if we've finished writing a character, and that character is null:  
    if (!(i+1)%8 && (message[i/8] == 0)) { 
      break; // exit from the for loop & stop reading.  
    }
  } 
  printf("%s\n", message);
  free(pixels); 
  free(message); 
  return 0;
}



