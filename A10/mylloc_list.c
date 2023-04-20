/*------------------------
* name: Renata Del Vecchio
* date: 4/29/2023
* message: A program which provides implements of malloc and free based
* on the reading. 
-------------------------*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

struct chunk { 
  int size; 
  int used;
  struct chunk *next;
};

struct chunk* flist = NULL;

/*
* Allocates a chunk of memory. 
* @param size the amount of memory to allocate.
* @return void* a pointer to the space in memory
*/
void *malloc (size_t size) { 
  if (size == 0) { 
    return NULL;
  }
  struct chunk *next = flist;
  struct chunk *prev = NULL;
 
  while (next != NULL) { // for each item in free list:
    if ( next -> size >= size) { // if found the one we want.
      if (prev != NULL) { // if it's not the first block:
        prev -> next = next -> next; 
      } else { // if it's the first block
        flist = next -> next; 
      }
      next -> used = size; 
      return (void*) (next +1); 
    } else { // if haven't found it, keep going.
      prev = next;
      next = next -> next; 
    }
  } // if reached this point, didn't find a chunk that fit: 
  void *memory = sbrk(size + sizeof(struct chunk)); 
  if ( memory == (void *) -1 ) { 
    return NULL;
  } else { 
    struct chunk *cnk = (struct chunk*) memory; 
    cnk -> used = size; 
    cnk -> size = size; 
    return (void *)(cnk +1); 
  }
}

/*
* free-- frees a block of allocated memory given. 
* @param memory a block of memory to be freed
*/
void free (void *memory) { 
  if (memory != NULL) { 
    // we're jumping back one chucnk position: 
    struct chunk *cnk = (struct chunk*)((struct chunk*) memory - 1);
    cnk -> next = flist;
    flist = cnk; 
  }
  return; 
}
