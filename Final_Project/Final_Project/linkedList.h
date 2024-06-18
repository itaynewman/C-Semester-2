#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Frame {
    char path[256];   // Path to the image file
    int duration;     // Duration of display in milliseconds
    char name[20];    // Unique name for the frame
} Frame;

typedef struct FrameNode {
    Frame frame;
    struct FrameNode* next;
} FrameNode;

void insertFrame(FrameNode** head, Frame newFrame);
int deleteFrame(FrameNode** head, char* name);
FrameNode* findFrame(FrameNode* head, char* name);
void changeFrameOrder(FrameNode** head, char* name, int newPosition);
void changeFrameTime(FrameNode* head, char* name, int newDuration);
void changeAllFrameTimes(FrameNode* head, int newDuration);
void printFramesList(FrameNode* head);

#endif
