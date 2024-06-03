/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a person in the queue
typedef struct Person {
    char name[50];
    int age;
    struct Person* next;
} Person;

// Structure for the queue
typedef struct Queue {
    Person* head;
    Person* tail;
} Queue;

// Function declarations
Queue* createQueue();
void printLine(Queue* queue);
void addPerson(Queue* queue);
void removePerson(Queue* queue);
void addVIP(Queue* queue);
void searchInLine(Queue* queue);
void reverseLine(Queue* queue);

int main() {
    Queue* queue = createQueue();
    int choice;

    printf("Welcome to MagshiParty Line Management Software!\n");

    do {
        printf("\nPlease enter your choice from the following options:\n");
        printf("1 - Print line\n");
        printf("2 - Add person to line\n");
        printf("3 - Remove person from line\n");
        printf("4 - VIP guest\n");
        printf("5 - Search in line\n");
        printf("6 - Reverse line\n");
        printf("7 - Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printLine(queue);
            break;
        case 2:
            addPerson(queue);
            break;
        case 3:
            removePerson(queue);
            break;
        case 4:
            addVIP(queue);
            break;
        case 5:
            searchInLine(queue);
            break;
        case 6:
            reverseLine(queue);
            break;
        case 7:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid input, please try again.\n");
            break;
        }
    } while (choice != 7);

    // Freeing memory
    while (queue->head) {
        Person* temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }
    free(queue);
    return 0;
}

// Function definitions

// Function to create a new queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

// Function to print the line and its length
void printLine(Queue* queue) {
    if (queue->head == NULL) {
        printf("0 people in line:\n");
        return;
    }

    Person* current = queue->head;
    int length = 0;

    printf("People in line:\n");
    while (current) {
        printf("%s, age: %d\n", current->name, current->age);
        current = current->next;
        length++;
    }
    printf("Total: %d people in line\n", length);
}

// Function to add a person to the line
void addPerson(Queue* queue) {
    char name[50];
    int age;

    printf("Welcome guest!\n");
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter age: ");
    scanf("%d", &age);

    Person* newPerson = (Person*)malloc(sizeof(Person));
    strcpy(newPerson->name, name);
    newPerson->age = age;
    newPerson->next = NULL;

    if (queue->head == NULL) {
        queue->head = newPerson;
        queue->tail = newPerson;
    }
    else {
        queue->tail->next = newPerson;
        queue->tail = newPerson;
    }
}

// Function to remove a person from the line
void removePerson(Queue* queue) {
    if (queue->head == NULL) {
        printf("The line is empty.\n");
        return;
    }

    char name[50];
    printf("Enter name to remove: ");
    scanf("%s", name);

    Person* current = queue->head;
    Person* previous = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (previous == NULL) {
                queue->head = current->next;
                if (queue->head == NULL) {
                    queue->tail = NULL;
                }
            }
            else {
                previous->next = current->next;
                if (current == queue->tail) {
                    queue->tail = previous;
                }
            }
            free(current);
            printf("%s removed from line\n", name);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Person with the name %s was not found in the line.\n", name);
}

// Function to add a VIP to the front of the line
void addVIP(Queue* queue) {
    char name[50];
    int age;

    printf("VIP GUEST!\n");
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter age: ");
    scanf("%d", &age);

    Person* newPerson = (Person*)malloc(sizeof(Person));
    strcpy(newPerson->name, name);
    newPerson->age = age;
    newPerson->next = queue->head;
    queue->head = newPerson;
    if (queue->tail == NULL) {
        queue->tail = newPerson;
    }
}

// Function to search for a person in the line
void searchInLine(Queue* queue) {
    if (queue->head == NULL) {
        printf("The line is empty.\n");
        return;
    }

    char name[50];
    printf("Enter name to search: ");
    scanf("%s", name);

    Person* current = queue->head;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("%s found in line\n", name);
            return;
        }
        current = current->next;
    }
    printf("Person with the name %s was not found in the line.\n", name);
}

// Function to reverse the order of the line
void reverseLine(Queue* queue) {
    if (queue->head == NULL || queue->head == queue->tail) return;

    Person* prev = NULL;
    Person* current = queue->head;
    Person* next = NULL;

    queue->tail = queue->head;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    queue->head = prev;
}

