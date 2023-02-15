/*----------------------------------------------
 * Author: Renata Del Vecchio
 * Date: February 15th, 2023
 * Description A program which accesses a .csv file, stores songs
 * in a linked list, and on user prompt, shows the most
 * danceable song. 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
* song struct contains information about a single song.
*/
struct song { 
  char title[128]; 
  char artist[128]; 
  int minutes; 
  int seconds; 
  float danceability; 
  float energy; 
  float tempo; 
  float valence; 
};

/* 
* node struct contains information for a single node in a linked list of songs.
*/
struct node { 
  struct song val; 
  struct node* next;
};

/* 
* function inserts a node to the front of the given list with a given value. 
* 
* @param val the value to go into the new head node. 
* @param head of the linked list before prepend. 
* @return the new head for the linked list, a node with the given value. 
*/ 
struct node* insert_front(struct song val, struct node *head) { 
  struct node *n = malloc(sizeof(struct node)); // allocate space for new head
  if (n == NULL) { // if no space left to store. 
    printf("ERROR: Out of space!\n"); 
    exit(1); 
  }
  n -> val = val; // set the value of the new head.
  n -> next = head; // make th ehead point to the previous head of the list.
  return n;  
}

/* 
* prints the entire list from a given head node. 
* @param head the head node of the given list to print. 
*/ 
void printList(struct node *head) { 
  int numInList = 0; // index while moving through list: 
  for (struct node* n = head; n != NULL; n = n -> next) { // for each node in list: 
    if (n -> val.seconds < 10) { // if there's less than 10 seconds, print 0 before.   
      printf("%d) %-30s artist: %-30s duration: %d:0%d D: %.3f E: %.3f T: %.3f "
              "V: %.3f\n", numInList++, n -> val.title, n -> val.artist,
              n -> val.minutes, n -> val.seconds, n -> val.danceability,
              n -> val.energy, n -> val.tempo, n -> val.valence);
    }
    else { // else, print without a 0 before the seconds. 
      printf("%d) %-30s artist: %-30s duration: %d:%d D: %.3f E: %.3f T: %.3f "
              "V: %.3f\n", numInList++, n -> val.title, n -> val.artist,
              n -> val.minutes, n -> val.seconds, n -> val.danceability,
              n -> val.energy, n -> val.tempo, n -> val.valence);
    }
  }
  printf("\nDataset contains %d songs\n\n", numInList); 
  printf("================\n"); 
}

/* 
* Given a particularly formatted string, splits the string into sections and 
* returns a song object containing information from the string. 
* @param line the particularly formatted string to be read. 
* @return a song struct containing the information from the given line. 
*/ 
struct song generateSongFromLine(char* line) { 
    struct song newSong; // define a struct to fill with information
    strcpy(newSong.title, strtok(line, ",")); // store title
    strcpy(newSong.artist, strtok(NULL, ",")); // store artist name
    int totalSeconds = atoi(strtok(NULL, ","))/1000; // store total seconds
    newSong.minutes = totalSeconds/60; // store number of minutes
    newSong.seconds = totalSeconds%60; // store numbers of seconds
    newSong.danceability = atof(strtok(NULL, ",")); // store danceability
    newSong.energy = atof(strtok(NULL, ",")); // store energy 
    newSong.tempo = atof(strtok(NULL, ",")); // store tempo. 
    newSong.valence = atof(strtok(NULL, ",")); // store valence. 
    return newSong;  
}

/* 
* reads "songlist.csv" and creates a linked list of song structs stored on the
* heap. 
* @return the pointer to the head node of the linked list. 
*/ 
struct node *generateSongList() { 
  FILE *fp = NULL; // make a pointer to store the new file. 
  fp = fopen("songlist.csv", "r"); // open the file to be read. 
  char buffer[128]; // create an empty buffer to store each read line. 
  fgets(buffer, 128, fp); // read and discard the first line (template line)
  fgets(buffer, 128, fp); // read the first line
  // create first item in list with information from buffer: 
  struct node *head = insert_front(generateSongFromLine(buffer), NULL); 
  while (fgets(buffer, 128, fp) != NULL) { // while there are lines to read: 
    // insert information from the line at the start of the list: 
    head = insert_front(generateSongFromLine(buffer), head);
  }
  fclose(fp); // close the file once done. 
  return head; 
}

/* 
* Safely frees an entire linked list starting from a given node. 
* @param head a pointer to the head node of the linked list to be freed. 
*/
void freeList(struct node *head) { 
  struct node* nextHead;
  while (head != NULL) { 
    nextHead = head -> next; // save the next node. 
    free(head); // free what *was* the head. 
    head = nextHead; // 
  }
}
 
/* 
* Finds, prints, and safely removes the most danceable song from a linked list
* of songs. 
* @param head the pointer to the head node of the linked list. 
* @return a pointer to the head node of the linked list. 
*/
struct node* removeMostDanceable(struct node* head) { 
  if (head == NULL) { // if given an empty list: 
    return NULL; // do nothing. 
  }
  // find the most danceable song:
  int indexOfMostDanceable = 0; // assume first item in list is most danceable.  
  float highestDanceability = head -> val.danceability;
  //thisNode keeps track of which node in the linked list we're looking at: 
  struct node* thisNode = head -> next; // compare with next item in list: 
  int thisNodeIndex = 1; // keep track of what index in the linked list we're at.
  while (thisNode != NULL) { // while not at end of the list. 
    if (thisNode -> val.danceability > highestDanceability) { 
      // if thisNode is the most danceable one we've seen so far, store it: 
      indexOfMostDanceable = thisNodeIndex; // store what index it was at. 
      highestDanceability = thisNode -> val.danceability; // store how danceable.
    }
    thisNode = thisNode -> next; // look at the next node in the linked list. 
    thisNodeIndex++; // keep track of what index in the list we're at.
  }
  // remove and print the most danceable song: 
  struct node* toRemove; // store which node to remove from the list.
  struct node* headToReturn; // store which node is the head of the list
  if (indexOfMostDanceable == 0) { // if the most danceable is first in list:  
    headToReturn = head -> next; // return the next node in list as the head. 
    toRemove = head; // set the original head to be removed. 
  } 
  else { // if the item to remove is NOT the first: 
    thisNode = head;
    for (int i = 0; i < indexOfMostDanceable - 1; i ++ ) { // move through list
      thisNode = thisNode -> next; // reach node directly BEFORE one to remove. 
    }
    // on the node before the one to remove (thisNode): 
    toRemove = thisNode -> next; // store the node to be removed
    thisNode -> next = toRemove -> next; // make it so list points normally
    headToReturn = head; // the head hasn't changed, return the previous head. 
  }  
  printf("---------------------------------------- Most danceable ---------------"
  "---------------------\n");
  if (toRemove -> val.seconds < 10) { // if < 10 seconds, print 0 before the seconds
    printf("%-30s artist: %-30s duration: %d:0%d D: %.3f E: %.3f T: %.3f "
            "V: %.3f\n", toRemove -> val.title, toRemove -> val.artist,
            toRemove -> val.minutes, toRemove -> val.seconds, toRemove -> val.danceability,
            toRemove -> val.energy, toRemove -> val.tempo, toRemove -> val.valence);
  }
  else { // else, print without a 0 before the seconds. 
    printf("%-30s artist: %-30s duration: %d:%d D: %.3f E: %.3f T: %.3f "
            "V: %.3f\n", toRemove -> val.title, toRemove -> val.artist,
            toRemove -> val.minutes, toRemove -> val.seconds, toRemove -> val.danceability,
            toRemove -> val.energy, toRemove -> val.tempo, toRemove -> val.valence);
  }
  printf("-----------------------------------------------------------------------"
  "---------------------\n\n"); 
  free(toRemove); // remove the most danceable node. 
  return headToReturn; // return the new head
}

int main() {
  struct node* head = generateSongList(); // generate + store new linked list
  printList(head);

  char response[16];
  while (1) {
    printf("Press 'd' to show the most danceable song (any other key to quit): ");
    scanf("%s", response); //read user input.
    if (strcmp(response, "d") == 0) { // if they say "d": 
      head = removeMostDanceable(head); 
      printList(head); 
    }
    else { // if they give any other input, exit loop: 
      break;
    }
  }
  freeList(head); 
  return 0;
}
