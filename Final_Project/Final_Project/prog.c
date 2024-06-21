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
void clearInputBuffer();

int main() {
    FrameNode* frameList = NULL;
    int choice;
    int shouldExit = 0;

    while (!shouldExit) {
        printMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

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

void printMenu() {
    printf("\n========== GIF Maker Menu ==========\n");
    printf("0. Exit\n");
    printf("1. Add a new frame\n");
    printf("2. Remove a frame\n");
    printf("3. Change the position of a frame\n");
    printf("4. Change the duration of a frame\n");
    printf("5. Change the duration of all frames\n");
    printf("6. Display all frames\n");
    printf("7. Play the GIF\n");
    printf("====================================\n");
}

void addFrame(FrameNode** frameList) {
    Frame newFrame;
    printf("Enter the path of the image: ");
    scanf("%s", newFrame.path);
    printf("Enter the duration (in milliseconds): ");
    if (scanf("%d", &newFrame.duration) != 1) {
        printf("Invalid input. Please enter a valid duration.\n");
        clearInputBuffer();
        return;
    }
    printf("Enter the name of the frame: ");
    scanf("%s", newFrame.name);

    if (findFrame(*frameList, newFrame.name)) {
        printf("Frame with this name already exists. Please choose a different name.\n");
        return;
    }

    FILE* file = fopen(newFrame.path, "r");
    if (!file) {
        printf("Image file does not exist. Please check the path and try again.\n");
        return;
    }
    fclose(file);

    insertFrame(frameList, newFrame);
    printf("Frame added successfully.\n");
}

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

void changeFramePosition(FrameNode** frameList) {
    char name[20];
    int newPosition;
    printf("Enter the name of the frame to move: ");
    scanf("%s", name);
    printf("Enter the new position: ");
    if (scanf("%d", &newPosition) != 1) {
        printf("Invalid input. Please enter a valid position.\n");
        clearInputBuffer();
        return;
    }

    changeFrameOrder(frameList, name, newPosition);
}

void changeFrameDuration(FrameNode** frameList) {
    char name[20];
    int newDuration;
    printf("Enter the name of the frame to change duration: ");
    scanf("%s", name);
    printf("Enter the new duration (in milliseconds): ");
    if (scanf("%d", &newDuration) != 1) {
        printf("Invalid input. Please enter a valid duration.\n");
        clearInputBuffer();
        return;
    }

    changeFrameTime(*frameList, name, newDuration);
}

void changeAllDurations(FrameNode** frameList) {
    int newDuration;
    printf("Enter the new duration for all frames (in milliseconds): ");
    if (scanf("%d", &newDuration) != 1) {
        printf("Invalid input. Please enter a valid duration.\n");
        clearInputBuffer();
        return;
    }

    changeAllFrameTimes(*frameList, newDuration);
    printf("All frame durations updated successfully.\n");
}

void printFrames(FrameNode* frameList) {
    printf("Frames in the GIF:\n");
    printf("Name\t\tPath\t\t\tDuration (ms)\n");
    printf("-------------------------------------------------------------\n");
    printFramesList(frameList);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
