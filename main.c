#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PlaylistNode.h"

PlaylistNode* gHead = NULL;
PlaylistNode* gTail = NULL;

void PrintMenu(char playlistTitle[]) {
   printf("%s PLAYLIST MENU\n", playlistTitle);
   printf("a - Add song\n");
   printf("r - Remove song\n");
   printf("c - Change position of song\n");
   printf("s - Output songs by specific artist\n");
   printf("t - Output total time of playlist (in seconds)\n");
   printf("o - Output full playlist\n");
   printf("q - Quit\n\n");
}

void ExecuteMenu(char option, char playlistTitle[], PlaylistNode* headNode) {
   //Step 6
   if(option=='o')
   {
      printf("%s - OUTPUT FULL PLAYLIST\n", playlistTitle);
      if(gHead==NULL)
      {
         printf("Playlist is empty\n\n");
         return;
      }
      PlaylistNode* current = gHead;
      int num = 1;
      while(current!=NULL)
      {
         printf("%d.\n", num);
         PrintPlaylistNode(current);
         printf("\n");

         current = GetNextPlaylistNode(current);
         num++;
      }
   }

   if(option=='a')
   {
      char idInit[50];
      char songNameInit[50];
      char artistNameInit[50];
      int songLengthInit;

      printf("ADD SONG\n");
      printf("Enter song's unique ID:\n");
      scanf(" %[^\n]", idInit);

      printf("Enter song's name:\n");
      scanf(" %[^\n]", songNameInit);

      printf("Enter artist's name:\n");
      scanf(" %[^\n]", artistNameInit);

      printf("Enter song's length (in seconds):\n");
      scanf("%d", &songLengthInit);
      printf("\n");

      PlaylistNode* newNode = (PlaylistNode*)malloc(sizeof(PlaylistNode));
      CreatePlaylistNode(newNode, idInit, songNameInit, artistNameInit, songLengthInit, NULL);

      if(gHead==NULL)
      {
         gHead = newNode;
         gTail = newNode;
      }
      else 
      {
         InsertPlaylistNodeAfter(gTail, newNode);
         gTail = newNode;
      }
   }

   if(option=='r')
   {
      char idToRemove[50];
      printf("REMOVE SONG\n");
      printf("Enter song's unique ID:\n");
      scanf(" %[^\n]", idToRemove);

      PlaylistNode* curr = gHead;
      PlaylistNode* prev = NULL;
      while(curr!=NULL && strcmp(curr->uniqueID, idToRemove)!=0)
      {
         prev = curr;
         curr = GetNextPlaylistNode(curr);
      }

      if (curr == NULL) 
      {
         return;
      }

      printf("\"%s\" removed.\n\n", curr->songName);

      if(prev==NULL)
      {
         gHead = GetNextPlaylistNode(curr);
         if(curr==gTail)
         {
            gTail=NULL;
         }
      }
      else if(curr==gTail)
      {
         gTail = prev;
         SetNextPlaylistNode(prev, NULL);
      }
      else
      {
         SetNextPlaylistNode(prev, GetNextPlaylistNode(curr));
      }
      free(curr);
   }

   if (option == 'c') 
   {
      printf("CHANGE POSITION OF SONG\n");

      if (gHead == NULL) return;  

      int curPos, newPos;
      printf("Enter song's current position:\n");
      scanf("%d", &curPos);
      printf("Enter new position for song:\n");
      scanf("%d", &newPos);

      int n = 0;
      for (PlaylistNode* t = gHead; t != NULL; t = GetNextPlaylistNode(t)) n++;

      if (curPos < 1) curPos = 1;
      if (curPos > n) curPos = n;
      if (newPos < 1) newPos = 1;
      if (newPos > n) newPos = n;

      PlaylistNode* prevCur = NULL;
      PlaylistNode* cur = gHead;
      for (int i = 1; i < curPos; ++i) 
      {
         prevCur = cur;
         cur = GetNextPlaylistNode(cur);
      }

      if (curPos == newPos) 
      {
         printf("\"%s\" moved to position %d\n\n", cur->songName, newPos);
         return;
      }

      
      if (prevCur == NULL) 
      {                  
         gHead = GetNextPlaylistNode(cur);
         if (cur == gTail) gTail = gHead;    
      } else 
      {
         SetNextPlaylistNode(prevCur, GetNextPlaylistNode(cur));
         if (cur == gTail) gTail = prevCur;  
      }

      
      int insertPos = newPos;
      if (curPos < newPos) insertPos--;

      
      if (insertPos == 1) 
      {
         SetNextPlaylistNode(cur, gHead);
         gHead = cur;
         if (gTail == NULL) gTail = cur;     
      } else 
      {
         PlaylistNode* prevDest = gHead;
         int loopLimit = (curPos < newPos) ? insertPos : (insertPos - 1);
         for (int i = 1; i < loopLimit; ++i) 
         {
            prevDest = GetNextPlaylistNode(prevDest);
         }
         InsertPlaylistNodeAfter(prevDest, cur);
         if (GetNextPlaylistNode(cur) == NULL) gTail = cur;
      }

      printf("\"%s\" moved to position %d\n\n", cur->songName, newPos);
   }

   if (option == 's') 
   {
      char artist[50];
      printf("OUTPUT SONGS BY SPECIFIC ARTIST\n");
      printf("Enter artist's name:\n");
      scanf(" %[^\n]", artist);

      PlaylistNode* current = gHead;
      int pos = 1;
      while (current != NULL) {
         if (strcmp(current->artistName, artist) == 0) {
            printf("%d.\n", pos);
            PrintPlaylistNode(current);
            printf("\n");
         }
         current = GetNextPlaylistNode(current);
         pos++;
      }
   }

   if (option == 't') 
   {
      printf("OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n");
      int totalTime = 0;
      PlaylistNode* current = gHead;
      while (current != NULL) {
         totalTime += current->songLength;
         current = GetNextPlaylistNode(current);
      }
      printf("Total time: %d seconds\n\n");
   }
}

int main(void) {
   char title[50];
   //Step 2
   printf("Enter playlist's title:\n");
   scanf(" %[^\n]", title);
   printf("\n");

   //Step 5
   char option;

   PrintMenu(title);
   printf("Choose an option:\n");
   scanf(" %c", &option);

   while(option!='q')
   {
      if (option == 'a' || option == 'r' || option == 'c' || option == 's' || option == 't' || option == 'o')
      {
         ExecuteMenu(option, title, gHead);
         PrintMenu(title);
         printf("Choose an option:\n");
         scanf(" %c", &option);
      }
      else
      {
         printf("Choose an option:\n");
         scanf(" %c", &option);
      }
   }      
   return 0;
}
