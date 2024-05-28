/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Function prototypes
char** allocateMemoryForNames(int num_friends);
void acceptNames(char** names, int num_friends);
void sortNames(char** names, int num_friends);
void printNames(char** names, int num_friends);
void freeMemory(char** names, int num_friends);

int main() {
    int num_friends;
    char** names;

    // Accepting the number of friends
    printf("Enter the number of friends: ");
    scanf("%d", &num_friends);

    // Allocate memory for names
    names = allocateMemoryForNames(num_friends);
    if (names == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Accepting the names of friends
    acceptNames(names, num_friends);

    // Sorting names alphabetically
    sortNames(names, num_friends);

    // Printing names in alphabetical order
    printNames(names, num_friends);

    // Freeing dynamically allocated memory
    freeMemory(names, num_friends);

    getchar();
    getchar();

    return 0;
}

// Function to allocate memory for names
char** allocateMemoryForNames(int num_friends) {
    char** names = (char**)malloc(num_friends * sizeof(char*));
    if (names == NULL) {
        return NULL;
    }

    for (int i = 0; i < num_friends; i++) {
        names[i] = (char*)malloc(MAX_NAME_LENGTH * sizeof(char));
        if (names[i] == NULL) {
            return NULL;
        }
    }

    return names;
}

// Function to accept names of friends
void acceptNames(char** names, int num_friends) {
    printf("Enter the names of friends:\n");
    for (int i = 0; i < num_friends; i++) {
        printf("Friend %d: ", i + 1);
        scanf("%s", names[i]);
    }
}

// Function to sort names alphabetically
void sortNames(char** names, int num_friends) {
    for (int i = 0; i < num_friends - 1; i++) {
        for (int j = i + 1; j < num_friends; j++) {
            if (strcmp(names[i], names[j]) > 0) {
                char* temp = names[i];
                names[i] = names[j];
                names[j] = temp;
            }
        }
    }
}

// Function to print names in alphabetical order
void printNames(char** names, int num_friends) {
    printf("Names of friends in alphabetical order:\n");
    for (int i = 0; i < num_friends; i++) {
        printf("%s\n", names[i]);
    }
}

// Function to free dynamically allocated memory
void freeMemory(char** names, int num_friends) {
    for (int i = 0; i < num_friends; i++) {
        free(names[i]);
    }
    free(names);
}

