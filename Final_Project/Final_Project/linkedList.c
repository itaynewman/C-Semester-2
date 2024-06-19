#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

/**
 * Inserts a new frame at the end of the linked list.
 */
void insertFrame(FrameNode** head, Frame newFrame) {
    FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
    if (!newNode) {
        printf("Memory allocation error\n");
        return;
    }
    newNode->frame = newFrame;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    }
    else {
        FrameNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

/**
 * Deletes a frame from the linked list by its name.
 * Returns 1 if successful, 0 if the frame was not found.
 */
int deleteFrame(FrameNode** head, char* name) {
    FrameNode* temp = *head, * prev = NULL;

    while (temp != NULL && strcmp(temp->frame.name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return 0;
    }

    if (prev == NULL) {
        *head = temp->next;
    }
    else {
        prev->next = temp->next;
    }

    free(temp);
    return 1;
}

/**
 * Finds a frame in the linked list by its name.
 * Returns a pointer to the frame node if found, NULL otherwise.
 */
FrameNode* findFrame(FrameNode* head, char* name) {
    FrameNode* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->frame.name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;
}

/**
 * Changes the order of a frame in the linked list.
 */
void changeFrameOrder(FrameNode** head, char* name, int newPosition) {
    if (newPosition <= 0) {
        printf("Invalid position\n");
        return;
    }

    FrameNode* frameNode = findFrame(*head, name);
    if (frameNode == NULL) {
        printf("Frame not found\n");
        return;
    }

    Frame frame = frameNode->frame;
    deleteFrame(head, name);

    FrameNode* temp = *head, * prev = NULL;
    int count = 1;

    while (temp != NULL && count < newPosition) {
        prev = temp;
        temp = temp->next;
        count++;
    }

    FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
    if (!newNode) {
        printf("Memory allocation error\n");
        return;
    }
    newNode->frame = frame;
    newNode->next = temp;

    if (prev == NULL) {
        *head = newNode;
    }
    else {
        prev->next = newNode;
    }

    printf("Frame position updated successfully.\n");
}

/**
 * Changes the duration of a specific frame.
 */
void changeFrameTime(FrameNode* head, char* name, int newDuration) {
    FrameNode* frameNode = findFrame(head, name);
    if (frameNode != NULL) {
        frameNode->frame.duration = newDuration;
    }
    else {
        printf("Frame not found\n");
    }
}

/**
 * Changes the duration of all frames in the linked list.
 */
void changeAllFrameTimes(FrameNode* head, int newDuration) {
    FrameNode* temp = head;

    while (temp != NULL) {
        temp->frame.duration = newDuration;
        temp = temp->next;
    }
}

/**
 * Prints the details of all frames in the linked list.
 */
void printFramesList(FrameNode* head) {
    FrameNode* temp = head;

    while (temp != NULL) {
        printf("Name: %s\n", temp->frame.name);
        printf("Path: %s\n", temp->frame.path);
        printf("Duration: %d ms\n\n", temp->frame.duration);
        temp = temp->next;
    }
}
