#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

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

void changeFrameTime(FrameNode* head, char* name, int newDuration) {
    FrameNode* frameNode = findFrame(head, name);
    if (frameNode != NULL) {
        frameNode->frame.duration = newDuration;
    }
    else {
        printf("Frame not found\n");
    }
}

void changeAllFrameTimes(FrameNode* head, int newDuration) {
    FrameNode* temp = head;

    while (temp != NULL) {
        temp->frame.duration = newDuration;
        temp = temp->next;
    }
}

void printFramesList(FrameNode* head) {
    FrameNode* temp = head;

    while (temp != NULL) {
        printf("Name: %s\n", temp->frame.name);
        printf("Path: %s\n", temp->frame.path);
        printf("Duration: %d ms\n\n", temp->frame.duration);
        temp = temp->next;
    }
}
