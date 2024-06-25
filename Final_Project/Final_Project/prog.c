#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"  // Assuming linkedList.h contains declarations related to linked list operations
#include "owieutil.h"  // Including the header with ANSI color codes
#include "view.h"

// Function prototypes
void printMainMenu();
void addFrame(FrameNode** frameList);
void removeFrame(FrameNode** frameList);
void changeFramePosition(FrameNode** frameList);
void changeFrameDuration(FrameNode** frameList);
void changeAllDurations(FrameNode** frameList);
void printFrames(FrameNode* frameList);
void clearInputBuffer();
void saveProject(FrameNode* frameList);
void loadProject(FrameNode** frameList);
void clearFrameList(FrameNode** frameList);

const char* options[] = 
{
        "0. Exit",
        "1. Add a new frame",
        "2. Remove a frame",
        "3. Change the position of a frame",
        "4. Change the duration of a frame",
        "5. Change the duration of all frames",
        "6. Display all frames",
        "7. Play the GIF"
};

int main()
{
    FrameNode* frameList = NULL; // Initialize linked list of frames
    int mainChoice;
    int projectChoice;
    int shouldExit = 0;

    printf(ANSIC_PURPLE_BRIGHT "Welcome to Magshimim Movie Maker!\n" ANSIC_RESET);
    printf(ANSIC_WHITE "What would you like to do?\n");
    printf(ANSIC_BLUE " [0] Create a new project\n");
    printf(ANSIC_BLUE " [1] Load existing project\n");
    printf(ANSIC_WHITE "Enter your choice: " ANSIC_RESET);

    if (scanf("%d", &mainChoice) != 1)
    {
        printf(ANSIC_RED_BRIGHT "Invalid input. Exiting...\n" ANSIC_RESET);
        return 1;
    }
    clearInputBuffer();

    switch (mainChoice)
    {
    case 0:
        printf(ANSIC_GREEN_BRIGHT "Working on a new project.\n" ANSIC_RESET);
        break;
    case 1:
        loadProject(&frameList);  // Load existing project
        break;
    default:
        printf(ANSIC_RED_BRIGHT "Invalid choice. Exiting...\n" ANSIC_RESET);
        return 1;
    }

    while (!shouldExit)
    {
        printf(ANSIC_COLOR_CYAN "\n========== GIF Maker Menu ==========\n" ANSIC_COLOR_RESET);
        npicker("info", "select an option:", options, 7);
        //printMenu();  // Print menu options
        printf(ANSIC_COLOR_CYAN "====================================\n" ANSIC_COLOR_RESET);
        if (scanf("%d", &projectChoice) != 1)
        {
            printf(ANSIC_RED_BRIGHT "Invalid input. Please enter a number.\n" ANSIC_RESET);
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (projectChoice)
        {
        case 0:
            printf(ANSIC_GREEN_BRIGHT "Exiting the program.\n" ANSIC_RESET);
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
        case 8:
            saveProject(frameList);
            break;
        default:
            printf(ANSIC_RED_BRIGHT "Invalid choice. Please try again.\n" ANSIC_RESET);
        }
    }

    // Clean up memory before exiting
    clearFrameList(&frameList);

    return 0;
}

// Function to print the main menu options
void printMainMenu()
{
    printf(ANSIC_WHITE "\nWhat would you like to do?\n");
    printf(ANSIC_BLUE " [0] Exit\n");
    printf(ANSIC_BLUE " [1] Add new Frame\n");
    printf(ANSIC_BLUE " [2] Remove a Frame\n");
    printf(ANSIC_BLUE " [3] Change frame index\n");
    printf(ANSIC_BLUE " [4] Change frame duration\n");
    printf(ANSIC_BLUE " [5] Change duration of all frames\n");
    printf(ANSIC_BLUE " [6] List frames\n");
    printf(ANSIC_BLUE " [7] Play movie!\n");
    printf(ANSIC_BLUE " [8] Save project\n" ANSIC_RESET);
}

// Function to add a new frame to the linked list
void addFrame(FrameNode** frameList)
{
    Frame newFrame;

    printf(ANSIC_WHITE "Enter the path of the image: " ANSIC_RESET);
    fgets(newFrame.path, sizeof(newFrame.path), stdin);
    newFrame.path[strcspn(newFrame.path, "\n")] = '\0'; // Remove newline if present

    printf(ANSIC_WHITE "Enter the duration (in milliseconds): " ANSIC_RESET);
    scanf("%d", &newFrame.duration);
    clearInputBuffer();
    printf(ANSIC_WHITE "Enter the name of the frame: " ANSIC_RESET);
    fgets(newFrame.name, sizeof(newFrame.name), stdin);
    newFrame.name[strcspn(newFrame.name, "\n")] = '\0'; // Remove newline if present

    // Check if frame name already exists
    if (findFrame(*frameList, newFrame.name))
    {
        printf(ANSIC_RED_BRIGHT "Frame with this name already exists. Please choose a different name.\n" ANSIC_RESET);
        return;
    }

    // Check if image file exists
    FILE* file = fopen(newFrame.path, "r");
    if (!file)
    {
        printf(ANSIC_RED_BRIGHT "Image file does not exist. Please check the path and try again.\n" ANSIC_RESET);
        return;
    }
    fclose(file);

    insertFrame(frameList, newFrame);  // Insert new frame into linked list
    printf(ANSIC_GREEN_BRIGHT "Frame added successfully.\n" ANSIC_RESET);
}

// Function to remove a frame from the linked list
void removeFrame(FrameNode** frameList)
{
    char name[20];
    printf(ANSIC_WHITE "Enter the name of the frame to remove: " ANSIC_RESET);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline if present

    if (deleteFrame(frameList, name))  // Attempt to delete frame by name
    {
        printf(ANSIC_GREEN_BRIGHT "Frame removed successfully.\n" ANSIC_RESET);
    }
    else
    {
        printf(ANSIC_RED_BRIGHT "Frame not found.\n" ANSIC_RESET);
    }
}

// Function to change the position of a frame in the linked list
void changeFramePosition(FrameNode** frameList)
{
    char name[20];
    int newPosition;
    printf(ANSIC_WHITE "Enter the name of the frame to move: " ANSIC_RESET);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline if present

    printf(ANSIC_WHITE "Enter the new position: " ANSIC_RESET);
    while (scanf("%d", &newPosition) != 1)
    {
        printf(ANSIC_RED_BRIGHT "Invalid input. Please enter a valid position.\n" ANSIC_RESET);
        clearInputBuffer();
        printf(ANSIC_WHITE "Enter the new position: " ANSIC_RESET);
    }
    clearInputBuffer();

    changeFrameOrder(frameList, name, newPosition);  // Change frame order in linked list
}

// Function to change the duration of a frame in the linked list
void changeFrameDuration(FrameNode** frameList)
{
    char name[20];
    int newDuration;
    printf(ANSIC_WHITE "Enter the name of the frame to change duration: " ANSIC_RESET);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline if present

    printf(ANSIC_WHITE "Enter the new duration (in milliseconds): " ANSIC_RESET);
    while (scanf("%d", &newDuration) != 1)
    {
        printf(ANSIC_RED_BRIGHT "Invalid input. Please enter a valid duration.\n" ANSIC_RESET);
        clearInputBuffer();
        printf(ANSIC_WHITE "Enter the new duration (in milliseconds): " ANSIC_RESET);
    }
    clearInputBuffer();

    changeFrameTime(*frameList, name, newDuration);  // Update frame duration in linked list
}

// Function to change the duration of all frames in the linked list
void changeAllDurations(FrameNode** frameList)
{
    int newDuration;
    printf(ANSIC_WHITE "Enter the new duration for all frames (in milliseconds): " ANSIC_RESET);
    while (scanf("%d", &newDuration) != 1)
    {
        printf(ANSIC_RED_BRIGHT "Invalid input. Please enter a valid duration.\n" ANSIC_RESET);
        clearInputBuffer();
        printf(ANSIC_WHITE "Enter the new duration for all frames (in milliseconds): " ANSIC_RESET);
    }
    clearInputBuffer();

    changeAllFrameTimes(*frameList, newDuration);  // Update all frame durations in linked list
    printf(ANSIC_GREEN_BRIGHT "All frame durations updated successfully.\n" ANSIC_RESET);
}

// Function to print all frames in the linked list
void printFrames(FrameNode* frameList)
{
    printf(ANSIC_COLOR_YELLOW "Frames in the GIF:\n" ANSIC_RESET);
    printf(ANSIC_COLOR_MAGENTA "Name\t\tPath\t\t\tDuration (ms)\n" ANSIC_RESET);
    printf(ANSIC_COLOR_MAGENTA "-------------------------------------------------------------\n" ANSIC_RESET);
    printFramesList(frameList);  // Call function to print frames from linked list
}

// Function to clear input buffer (discard extra characters after valid input)
void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to save the current project to a file
void saveProject(FrameNode* frameList)
{
    char filename[100];
    printf(ANSIC_WHITE "Enter the filename to save the project: " ANSIC_RESET);
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline if present

    FILE* file = fopen(filename, "w");
    if (!file)
    {
        printf(ANSIC_RED_BRIGHT "Error opening file for writing.\n" ANSIC_RESET);
        return;
    }

    FrameNode* current = frameList;
    while (current)
    {
        fprintf(file, "%s;%s;%d\n", current->frame.name, current->frame.path, current->frame.duration);
        current = current->next;
    }

    fclose(file);
    printf(ANSIC_GREEN_BRIGHT "Project saved successfully.\n" ANSIC_RESET);
}

// Function to load a project from a file
void loadProject(FrameNode** frameList)
{
    char filename[100];
    printf(ANSIC_WHITE "Enter the filename to load the project: " ANSIC_RESET);
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline if present

    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf(ANSIC_RED_BRIGHT "Error opening file for reading.\n" ANSIC_RESET);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        Frame newFrame;
        sscanf(line, "%[^;];%[^;];%d", newFrame.name, newFrame.path, &newFrame.duration);
        insertFrame(frameList, newFrame);
    }

    fclose(file);
    printf(ANSIC_GREEN_BRIGHT "Project loaded successfully.\n" ANSIC_RESET);
}

// Function to free all nodes in the linked list
void clearFrameList(FrameNode** frameList)
{
    FrameNode* current = *frameList;
    FrameNode* next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *frameList = NULL;
}