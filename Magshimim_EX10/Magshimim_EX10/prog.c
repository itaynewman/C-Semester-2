/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of the struct personNode
typedef struct personNode {
    char name[21]; // String for name with 20 characters + null terminator
    int age;
    struct personNode* next;
} personNode;

// Function declarations
personNode* createNode(char* name, int age);
void printList(personNode* head);
void freeList(personNode* head);
int listLength(personNode* head);
personNode* copyList(personNode* head);

int main() {
    int n;
    printf("Enter the length of the list: ");
    scanf("%d", &n);

    personNode* head = NULL;
    personNode* tail = NULL;

    for (int i = 0; i < n; i++) {
        char name[21];
        int age;
        printf("Enter name and age for person %d: ", i + 1);
        scanf("%s %d", name, &age);

        personNode* newNode = createNode(name, age);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Print the original list
    printf("\nOriginal List:\n");
    printList(head);

    // Print the length of the list
    printf("\nLength of the list: %d\n", listLength(head));

    // Create a copy of the list and print it
    personNode* copiedList = copyList(head);
    printf("\nCopied List:\n");
    printList(copiedList);

    // Free memory of both lists
    freeList(head);
    freeList(copiedList);

    return 0;
}

// Function definitions

// Function to create a new node
personNode* createNode(char* name, int age) {
    personNode* newNode = (personNode*)malloc(sizeof(personNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strncpy(newNode->name, name, 20);
    newNode->name[20] = '\0'; // Ensure the string is null-terminated
    newNode->age = age;
    newNode->next = NULL;
    return newNode;
}

// Function to print the content of the list
void printList(personNode* head) {
    personNode* current = head;
    while (current != NULL) {
        printf("Name: %s, Age: %d\n", current->name, current->age);
        current = current->next;
    }
}

// Function to free the memory of all nodes in the list
void freeList(personNode* head) {
    personNode* current = head;
    personNode* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

// Recursive function to compute the length of the list
int listLength(personNode* head) {
    if (head == NULL) {
        return 0;
    }
    return 1 + listLength(head->next);
}

// Function to copy a list
personNode* copyList(personNode* head) {
    if (head == NULL) {
        return NULL;
    }
    personNode* newHead = createNode(head->name, head->age);
    newHead->next = copyList(head->next);
    return newHead;
}

