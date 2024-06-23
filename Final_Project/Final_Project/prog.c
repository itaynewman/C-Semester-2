#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

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
            printf(ANSI_COLOR_RED "Invalid input. Please enter a number.\n" ANSI_COLOR_RESET);
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice) {
        case 0:
            printf(ANSI_COLOR_GREEN "Exiting the program.\n" ANSI_COLOR_RESET);
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
            printf(ANSI_COLOR_RED "Invalid choice. Please try again.\n" ANSI_COLOR_RESET);
        }
    }

    return 0;
}

void printMenu() {
    printf(ANSI_COLOR_CYAN "\n========== GIF Maker Menu ==========\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "0. Exit\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "1. Add a new frame\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "2. Remove a frame\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "3. Change the position of a frame\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "4. Change the duration of a frame\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "5. Change the duration of all frames\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "6. Display all frames\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "7. Play the GIF\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "====================================\n" ANSI_COLOR_RESET);
}

void addFrame(FrameNode** frameList) {
    Frame newFrame;

    printf("Enter the path of the image: ");
    fgets(newFrame.path, sizeof(newFrame.path), stdin);
    newFrame.path[strcspn(newFrame.path, "\n")] = '\0'; // Remove newline if present

    printf("Enter the duration (in milliseconds): ");
    scanf("%d", &newFrame.duration);
    clearInputBuffer();
    printf("Enter the name of the frame: ");
    fgets(newFrame.name, sizeof(newFrame.name), stdin);
    newFrame.name[strcspn(newFrame.name, "\n")] = '\0'; // Remove newline if present

    // Check if frame name already exists
    if (findFrame(*frameList, newFrame.name)) {
        printf(ANSI_COLOR_RED "Frame with this name already exists. Please choose a different name.\n" ANSI_COLOR_RESET);
        return;
    }

    // Check if image file exists
    FILE* file = fopen(newFrame.path, "r");
    if (!file) {
        printf(ANSI_COLOR_RED "Image file does not exist. Please check the path and try again.\n" ANSI_COLOR_RESET);
        return;
    }
    fclose(file);

    insertFrame(frameList, newFrame);
    printf(ANSI_COLOR_GREEN "Frame added successfully.\n" ANSI_COLOR_RESET);
}

void removeFrame(FrameNode** frameList) {
    char name[20];
    printf("Enter the name of the frame to remove: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline if present

    if (deleteFrame(frameList, name)) {
        printf(ANSI_COLOR_GREEN "Frame removed successfully.\n" ANSI_COLOR_RESET);
    }
    else {
        printf(ANSI_COLOR_RED "Frame not found.\n" ANSI_COLOR_RESET);
    }
}

void changeFramePosition(FrameNode** frameList) {
    char name[20];
    int newPosition;
    printf("Enter the name of the frame to move: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline if present

    printf("Enter the new position: ");
    while (scanf("%d", &newPosition) != 1) {
        printf(ANSI_COLOR_RED "Invalid input. Please enter a valid position.\n" ANSI_COLOR_RESET);
        clearInputBuffer();
        printf("Enter the new position: ");
    }
    clearInputBuffer();

    changeFrameOrder(frameList, name, newPosition);
}

void changeFrameDuration(FrameNode** frameList) {
    char name[20];
    int newDuration;
    printf("Enter the name of the frame to change duration: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline if present

    printf("Enter the new duration (in milliseconds): ");
    while (scanf("%d", &newDuration) != 1) {
        printf(ANSI_COLOR_RED "Invalid input. Please enter a valid duration.\n" ANSI_COLOR_RESET);
        clearInputBuffer();
        printf("Enter the new duration (in milliseconds): ");
    }
    clearInputBuffer();

    changeFrameTime(*frameList, name, newDuration);
}

void changeAllDurations(FrameNode** frameList) {
    int newDuration;
    printf("Enter the new duration for all frames (in milliseconds): ");
    while (scanf("%d", &newDuration) != 1) {
        printf(ANSI_COLOR_RED "Invalid input. Please enter a valid duration.\n" ANSI_COLOR_RESET);
        clearInputBuffer();
        printf("Enter the new duration for all frames (in milliseconds): ");
    }
    clearInputBuffer();

    changeAllFrameTimes(*frameList, newDuration);
    printf(ANSI_COLOR_GREEN "All frame durations updated successfully.\n" ANSI_COLOR_RESET);
}

void printFrames(FrameNode* frameList) {
    printf(ANSI_COLOR_YELLOW "Frames in the GIF:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "Name\t\tPath\t\t\tDuration (ms)\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA "-------------------------------------------------------------\n" ANSI_COLOR_RESET);
    printFramesList(frameList);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
