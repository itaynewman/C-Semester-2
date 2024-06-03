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
    struct Person* next;
} Person;

// Structure for the queue
typedef struct Queue {
    Person* head;
    Person* tail;
} Queue;

// Function declarations
Queue* createQueue();
void printQueue(Queue* queue);
void addPerson(Queue* queue, char* name, char friends[3][50]);
void removePerson(Queue* queue, char* name);
void addVIP(Queue* queue, char* name);
void searchPerson(Queue* queue, char* name);
void reverseQueue(Queue* queue);

int main() {
    Queue* queue = createQueue();
    int choice;
    char name[50];
    char friends[3][50];

    do {
        printf("\n1) Print the queue and its length\n");
        printf("2) Add a new person to the queue\n");
        printf("3) Remove a person from the queue\n");
        printf("4) VIP - Add a VIP to the front of the queue\n");
        printf("5) Search for a person in the queue\n");
        printf("6) Reverse the order of the queue\n");
        printf("7) Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printQueue(queue);
            break;
        case 2:
            printf("Enter name: ");
            scanf("%s", name);
            printf("Enter the names of 3 friends (if none, enter ''): ");
            for (int i = 0; i < 3; i++) {
                scanf("%s", friends[i]);
            }
            addPerson(queue, name, friends);
            break;
        case 3:
            printf("Enter name: ");
            scanf("%s", name);
            removePerson(queue, name);
            break;
        case 4:
            printf("Enter VIP name: ");
            scanf("%s", name);
            addVIP(queue, name);
            break;
        case 5:
            printf("Enter name to search: ");
            scanf("%s", name);
            searchPerson(queue, name);
            break;
        case 6:
            reverseQueue(queue);
            printf("Queue order has been reversed.\n");
            break;
        case 7:
            printf("Exiting.\n");
            break;
        default:
            printf("Invalid choice.\n");
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

// Function to print the queue and its length
void printQueue(Queue* queue) {
    if (queue->head == NULL) {
        printf("The queue is empty.\n");
        return;
    }
    Person* current = queue->head;
    int length = 0;
    while (current) {
        printf("%s -> ", current->name);
        current = current->next;
        length++;
    }
    printf("NULL\n");
    printf("Queue length: %d\n", length);
}

// Function to add a person to the queue
void addPerson(Queue* queue, char* name, char friends[3][50]) {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    strcpy(newPerson->name, name);
    newPerson->next = NULL;

    if (queue->head == NULL) {
        queue->head = newPerson;
        queue->tail = newPerson;
        return;
    }

    Person* current = queue->head;
    while (current) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(current->name, friends[i]) == 0) {
                newPerson->next = current->next;
                current->next = newPerson;
                if (current == queue->tail) {
                    queue->tail = newPerson;
                }
                return;
            }
        }
        current = current->next;
    }

    queue->tail->next = newPerson;
    queue->tail = newPerson;
}

// Function to remove a person from the queue
void removePerson(Queue* queue, char* name) {
    if (queue->head == NULL) {
        printf("The queue is empty.\n");
        return;
    }

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
            printf("%s has been removed from the queue.\n", name);
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Person with the name %s was not found in the queue.\n", name);
}

// Function to add a VIP to the front of the queue
void addVIP(Queue* queue, char* name) {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    strcpy(newPerson->name, name);
    newPerson->next = queue->head;
    queue->head = newPerson;
    if (queue->tail == NULL) {
        queue->tail = newPerson;
    }
}

// Function to search for a person in the queue
void searchPerson(Queue* queue, char* name) {
    Person* current = queue->head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("%s is in the queue.\n", name);
            return;
        }
        current = current->next;
    }
    printf("Person with the name %s was not found in the queue.\n", name);
}

// Function to reverse the order of the queue
void reverseQueue(Queue* queue) {
    if (queue->head == NULL) return;
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
