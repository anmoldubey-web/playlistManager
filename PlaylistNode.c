#include <stdio.h>
#include <string.h>
#include "PlaylistNode.h"

void CreatePlaylistNode(PlaylistNode* thisNode, char idInit[], char songNameInit[], char artistNameInit[], int songLengthInit, PlaylistNode* nextLoc)
{
    strcpy(thisNode->uniqueID, idInit);
    strcpy(thisNode->songName, songNameInit);
    strcpy(thisNode->artistName, artistNameInit);
    thisNode->songLength = songLengthInit;
    thisNode->nextNodePtr = nextLoc;
}

void InsertPlaylistNodeAfter(PlaylistNode* thisNode, PlaylistNode* newNode)
{
    PlaylistNode* tempNext = NULL;
    tempNext = thisNode->nextNodePtr;
    thisNode->nextNodePtr = newNode;
    newNode->nextNodePtr = tempNext;
}

void SetNextPlaylistNode(PlaylistNode* thisNode, PlaylistNode* newNode)
{
    thisNode->nextNodePtr = newNode;
}

PlaylistNode* GetNextPlaylistNode(PlaylistNode* thisNode)
{
    return thisNode->nextNodePtr;
}

void PrintPlaylistNode(PlaylistNode* thisNode)
{
    printf("Unique ID: %s\n", thisNode->uniqueID);
    printf("Song Name: %s\n", thisNode->songName);
    printf("Artist Name: %s\n", thisNode->artistName);
    printf("Song Length (in seconds): %d\n", thisNode->songLength);
}
