/*----------------------------------------------
 * Author: Renata Del Vecchio
 * Date: 2/28/2023
 * Description a function which reads in a bitmap and prints the image
 ---------------------------------------------*/
#include <stdio.h>

int main() {
  unsigned long img; // unsigned long to store the bitmap image into
  scanf(" %lx", &img); // read the image 
  printf("Image (unsigned long): %lx\n", img);
  for (int i = 63; i >= 0; i --) { 
    if ((img & (0x1ul << i)) >> i ) { // if the bit is 1: 
      printf("@ "); 
    }
    else { // else if 0 
      printf("  ");
    } 
    if (i % 8 == 0) { // If we're at the end of a line, go to next:
      printf("\n");
    }
  }
  printf("---------\n"); 
  
  return 0;
}
