#include <stdio.h>
#include <stdlib.h>
#include "view.h"
#include "linkedList.h"

int main() {
    FrameNode* frameList = NULL;
    int choice;

    while (1) {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("Exiting the program.\n");
            return 0;
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
