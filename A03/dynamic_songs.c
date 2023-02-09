/*----------------------------------------------
 * Author: Renata Del Vecchio
 * Date: 2/8/2023
 * Description reads a csv file and prints songs included in that csv file. 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* song struct holds information about a single song.
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

int numSongs; // global variable keeps track of the number of songs in songList.

struct song* generateSongList() { 
  // Create a file object for the .csv file to read:
  FILE *fp = NULL;
  fp = fopen("songList.csv", "r"); 
  
  // read the first line and store the number of songs:
  char buffer[128]; 
  fgets(buffer, 128, fp);   
  numSongs = atoi(strtok(buffer, ",")); 

  struct song *songList = malloc(sizeof(struct song) * numSongs); 
  
  fgets(buffer, 128, fp); // read and discard the second line, a header. 
  for (int i = 0; i < numSongs; i ++ ) { // for each song to read: 
    fgets(buffer, 128, fp); // read the line
    struct song newSong; // make a song to store information into temporarily
    strcpy(newSong.title, strtok(buffer, ",")); // save the title
    strcpy(newSong.artist, strtok(NULL, ",")); // save the artist
    int totalSeconds = atoi(strtok(NULL, ","))/100; // store seconds.
    newSong.minutes = totalSeconds/60; // calculate minutes. 
    newSong.seconds = totalSeconds%60; // caluclate seconds to display.
    newSong.danceability = atof(strtok(NULL, ",")); // store danceability. 
    newSong.energy = atof(strtok(NULL, ",")); //store energy. 
    newSong.tempo = atof(strtok(NULL, ",")); // store tempo. 
    newSong.valence = atof(strtok(NULL, ",")); // store valence. 
    songList[i] = newSong; // add the newsong to the songsList. 
  } 
  fclose(fp); // close the file once done reading it. 
  return songList; 
}

/*
* A function which prints out the entire list of songs given.
*/ 
void printSongList(struct song* songList) { 
  // for all songs in the songList:
  for (int i = 0; i < numSongs; i ++ ) { 
    if (songList[i].minutes < 10) { // if there's less than 10 seconds, print 0 before. 
      printf("%d) %-30s artist: %-30s duration: %d:0%d D: %.3f E: %.3f T: %.3f V: %.3f\n",
              i, songList[i].title, songList[i].artist, songList[i].minutes, 
              songList[i].seconds, songList[i].danceability, songList[i].energy, 
              songList[i].tempo, songList[i].valence); 
    }
    else { // else, print without a 0 before the seconds. 
      printf("%d) %-30s artist: %-30s duration: %d:%d D: %.3f E: %.3f T: %.3f V: %.3f\n",
              i, songList[i].title, songList[i].artist , songList[i].minutes, 
              songList[i].seconds, songList[i].danceability, songList[i].energy, 
              songList[i].tempo, songList[i].valence); 
    }
  }
}

int main() {
  printf("%s", "Welcome to Ray's Radical Records (Spotify tracks):\n"); 
  struct song *songList = generateSongList(); 
  printSongList(songList);   
  free(songList);
  return 0;
}
