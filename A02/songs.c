/* 
* program which stores song information in a song struct, and
* allows the user to make changes to it. 
* 
* @author: Renata Del Vecchio
* @version: February 1, 2023
*/

#include <stdio.h>
#include <string.h>

/*
* song struct stores information about a song
*/
struct song { 
  int minutes;
  int seconds;
  float danceability; 
  char artist[32];  
  char title[32]; 
};

int songListLength = 3; // initialize size of songList array. Max # of songs.  
struct song songList[3]; // create an array of song structs  
int numSongs = 0; // actual number of songs in the list.

/* 
* prints out all songs in songList
*/
void printSongs() {
  printf("\n"); 
  // for all songs in songList: 
  for (int i = 0; i < numSongs; i ++) { 
    printf("%d) %-20s artist: %-20s", i, songList[i].title, songList[i].artist); 

    // if statement to format seconds:
    if (songList[i].seconds >= 10) { // if seconds value is 2 digits, print normally
      printf("duration: %d:%d  danceability: %.2f\n", songList[i].minutes, 
             songList[i].seconds, songList[i].danceability);
    }
    else { // else if the seconds value is 1 digit, print with a 0 before it. 
      printf("duration: %d:0%d  danceability: %.2f\n", songList[i].minutes, 
             songList[i].seconds, songList[i].danceability);
    }
  } 

  printf("\n=======================\n"); 
  
}

/* 
* adds a song to songList when given all attributes. 
*
* @param min integer minutes duration of song to be added. 
* @param sec integer seconds duration of song to be added.
* @param danc float danceability of song to be added. 
* @param art char* artist name of song to be added. 
* @param title char* title of song to be added. 
*/
void makeSong(int min, int sec, float danc, char* art, char* title) { 
  if (numSongs >= songListLength) { // if songList is full. 
    printf("You cannot add another song to the list!\n");   
    return;
  }
 
  // add attributes of song.
  struct song newSong; 
  newSong.minutes = min;
  newSong.seconds = sec; 
  newSong.danceability = danc;
  strcpy(newSong.artist, art); 
  strcpy(newSong.title, title);   
  
  songList[numSongs++] = newSong; // add song to songList.  
}

/*  
* main function prints and handles user input. 
*/
int main() {
  printf("Welcome to Ray's Song List!\n"); 

  //add three songs. 
  makeSong(2, 39, .20, "Katy Kirby", "Juniper"); 
  makeSong(3, 1, .60, "Modest Mouse", "Paper Thin Walls"); 
  makeSong(4, 13, .30, "Indigo Girls", "Galileo"); 

  printSongs(); // print the song list.  

  // begin user input: 
  printf("\nEnter a song id to edit [0, 1, 2]: ");
  int songNum = 0; 
  scanf("%d", &songNum); 
  if (songNum < 0 || songNum > 2) { 
    printf("Invalid choice!\n"); 
    return 0; 
  } 
 
  // user input step 2:  
  printf("Enter an attribute to edit [artist, title, duration, danceability]: "); 
  char attribute[32];
  scanf("%s", attribute); 
  if (strcmp(attribute, "artist") == 0) { // if user selects "artist"

    printf("Enter an artist: "); 
    char artistName[32];
    scanf(" %[^\n]%*c", artistName); 
    strcpy(songList[songNum].artist, artistName); 

  } else if (strcmp(attribute, "title") == 0) { // if user selects "title"

    printf("Enter a new song title: "); 
    char title[32];
    scanf(" %[^\n]%*c", title);
    strcpy(songList[songNum].title, title); 

  } else if (strcmp(attribute, "duration") == 0) { // if user selects "duration"

    printf("Enter a duration (minutes): "); 
    int readNum = 0; 
    scanf("%d", &readNum); 
    songList[songNum].minutes = readNum; 
    printf("Enter a duration (seconds): "); 
    scanf("%d", &readNum);  
    songList[songNum].seconds = readNum;   
  
  // if user selects "danceability"
  } else if (strcmp(attribute, "danceability") == 0) { 

    printf("Enter danceability: ");     
    float readFloat = 0;  
    scanf("%f", &readFloat);
    songList[songNum].danceability = readFloat; 
     
  } else { 

    //if user selected none: 
    printf("Please select select an attribute from the list.\n"); 
    return 0;

  } // end chain of if/else

  printSongs(); // print out changed songs at end. 

  return 0;
}
