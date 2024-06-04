#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 50

// Define the Person structure
typedef struct Person {
    char name[NAME_LENGTH];
    struct Person* next;
} Person;

// Declare global head pointer
Person* head = NULL;

// Function declarations
void printQueue();
void addPerson();
void removePerson();
void addVIP();
void searchPerson();
void reverseQueue();
void handleMenu();

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Print the queue and its length\n");
        printf("2. Add a new person to the queue\n");
        printf("3. Remove a person from the queue\n");
        printf("4. Add a VIP to the queue\n");
        printf("5. Search for a person in the queue\n");
        printf("6. Reverse the queue\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printQueue();
            break;
        case 2:
            addPerson();
            break;
        case 3:
            removePerson();
            break;
        case 4:
            addVIP();
            break;
        case 5:
            searchPerson();
            break;
        case 6:
            reverseQueue();
            break;
        case 7:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

// Function definitions

void printQueue() {
    Person* temp = head;
    int count = 0;
    printf("Queue:\n");
    while (temp != NULL) {
        printf("%s -> ", temp->name);
        temp = temp->next;
        count++;
    }
    printf("NULL\n");
    printf("Queue length: %d\n", count);
}

void addPerson() {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    Person* temp = head;
    Person* prev = NULL;
    char friends[3][NAME_LENGTH];
    int added = 0;

    printf("Enter name: ");
    scanf("%s", newPerson->name);
    printf("Enter names of up to 3 friends (enter 'none' if no friends): ");
    for (int i = 0; i < 3; i++) {
        scanf("%s", friends[i]);
    }

    newPerson->next = NULL;

    if (head == NULL) {
        head = newPerson;
    }
    else {
        while (temp != NULL && !added) {
            for (int i = 0; i < 3; i++) {
                if (strcmp(friends[i], temp->name) == 0) {
                    newPerson->next = temp->next;
                    temp->next = newPerson;
                    added = 1;
                    break;
                }
            }
            prev = temp;
            temp = temp->next;
        }
        if (!added) {
            prev->next = newPerson;
        }
    }
}

void removePerson() {
    if (head == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    char name[NAME_LENGTH];
    printf("Enter the name of the person to remove: ");
    scanf("%s", name);

    Person* temp = head;
    Person* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL) {
                head = temp->next;
            }
            else {
                prev->next = temp->next;
            }
            free(temp);
            printf("%s has been removed from the queue.\n", name);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Person not found in the queue.\n");
}

void addVIP() {
    Person* newPerson = (Person*)malloc(sizeof(Person));

    printf("Enter name of VIP: ");
    scanf("%s", newPerson->name);

    newPerson->next = head;
    head = newPerson;
    printf("VIP %s has been added to the front of the queue.\n", newPerson->name);
}

void searchPerson() {
    if (head == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    char name[NAME_LENGTH];
    printf("Enter the name of the person to search: ");
    scanf("%s", name);

    Person* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Person %s is in the queue.\n", name);
            return;
        }
        temp = temp->next;
    }

    printf("Person not found in the queue.\n");
}

void reverseQueue() {
    Person* prev = NULL;
    Person* current = head;
    Person* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;

    printf("Queue has been reversed.\n");
}
