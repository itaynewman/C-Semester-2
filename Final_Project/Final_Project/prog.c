#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

void printMenu();
void addFrame(FrameNode** frameList);
void removeFrame(FrameNode** frameList);
void changeFramePosition(FrameNode** frameList);
void changeFrameDuration(FrameNode** frameList);
void changeAllDurations(FrameNode** frameList);
void printFrames(FrameNode* frameList);

/**
 * The main function that drives the program.
 */
int main() {
    FrameNode* frameList = NULL;
    int choice;
    int shouldExit = 0;

    while (!shouldExit) {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("Exiting the program.\n");
            shouldExit = 1;
            break;
        case 1:
            addFrame(&frameList);
            break;
        case 2:
            removeFrame(&frameList);
            break;
        case 3:
            changeFramePosition(&frameList);
            break;
        case 4:
            changeFrameDuration(&frameList);
            break;
        case 5:
            changeAllDurations(&frameList);
            break;
        case 6:
            printFrames(frameList);
            break;
        case 7:
            play(frameList);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

/**
 * Prints the main menu options.
 */
void printMenu() {
    printf("GIF Maker Menu:\n");
    printf("0. Exit\n");
    printf("1. Add a new frame\n");
    printf("2. Remove a frame\n");
    printf("3. Change the position of a frame\n");
    printf("4. Change the duration of a frame\n");
    printf("5. Change the duration of all frames\n");
    printf("6. Display all frames\n");
    printf("7. Play the GIF\n");
}

/**
 * Adds a new frame to the linked list.
 */
void addFrame(FrameNode** frameList) {
    Frame newFrame;

    printf("Enter the path of the image: ");
    scanf("%s", newFrame.path);
    printf("Enter the duration (in milliseconds): ");
    scanf("%d", &newFrame.duration);
    printf("Enter the name of the frame: ");
    scanf("%s", newFrame.name);

    // Check if frame name already exists
    if (findFrame(*frameList, newFrame.name)) {
        printf("Frame with this name already exists. Please choose a different name.\n");
        return;
    }

    // Check if image file exists
    FILE* file = fopen(newFrame.path, "r");
    if (!file) {
        printf("Image file does not exist. Please check the path and try again.\n");
        return;
    }
    fclose(file);

    insertFrame(frameList, newFrame);
    printf("Frame added successfully.\n");
}

/**
 * Removes a frame from the linked list.
 */
void removeFrame(FrameNode** frameList) {
    char name[20];
    printf("Enter the name of the frame to remove: ");
    scanf("%s", name);

    if (deleteFrame(frameList, name)) {
        printf("Frame removed successfully.\n");
    }
    else {
        printf("Frame not found.\n");
    }
}

/**
 * Changes the position of a frame in the linked list.
 */
void changeFramePosition(FrameNode** frameList) {
    char name[20];
    int newPosition;
    printf("Enter the name of the frame to move: ");
    scanf("%s", name);
    printf("Enter the new position: ");
    scanf("%d", &newPosition);

    changeFrameOrder(frameList, name, newPosition);
}

/**
 * Changes the duration of a specific frame in the linked list.
 */
void changeFrameDuration(FrameNode** frameList) {
    char name[20];
    int newDuration;
    printf("Enter the name of the frame to change duration: ");
    scanf("%s", name);
    printf("Enter the new duration (in milliseconds): ");
    scanf("%d", &newDuration);

    changeFrameTime(*frameList, name, newDuration);
}

/**
 * Changes the duration of all frames in the linked list.
 */
void changeAllDurations(FrameNode** frameList) {
    int newDuration;
    printf("Enter the new duration for all frames (in milliseconds): ");
    scanf("%d", &newDuration);

    changeAllFrameTimes(*frameList, newDuration);
    printf("All frame durations updated successfully.\n");
}

/**
 * Prints all frames in the linked list.
 */
void printFrames(FrameNode* frameList) {
    printf("Frames in the GIF:\n");
    printFramesList(frameList);
}

/**
 * Placeholder function to play the GIF.
 */

