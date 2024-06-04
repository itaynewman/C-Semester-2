#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Person structure
typedef struct Person
{
    char name[50];
    int age;
    struct Person* next;
} Person;

// Function declarations
void printQueue(Person* head);
void addPerson(Person** head, char* name, int age, char friends[][50], int friendsCount);
void removePerson(Person** head, char* name);
void addVIP(Person** head, char* name, int age);
int searchPerson(Person* head, char* name);
void reverseQueue(Person** head);

int main()
{
    Person* head = NULL;
    int choice;
    char name[50];
    int age;
    char friends[3][50];

    do
    {
        printf("\nWelcome to MagshiParty Line Management Software!\n");
        printf("Please enter your choice from the following options:\n");
        printf("1 - Print line\n");
        printf("2 - Add person to line\n");
        printf("3 - Remove person from line\n");
        printf("4 - VIP guest\n");
        printf("5 - Search in line\n");
        printf("6 - Reverse line\n");
        printf("7 - Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printQueue(head);
            break;
        case 2:
            printf("Welcome guest!\n");
            printf("Enter name: ");
            scanf("%s", name);
            printf("Enter age: ");
            scanf("%d", &age);
            for (int i = 0; i < 3; i++)
            {
                printf("Enter names of 3 friends:\n");
                printf("Friend %d: ", i + 1);
                scanf("%s", friends[i]);
            }
            addPerson(&head, name, age, friends, 3);
            break;
        case 3:
            printf("Enter name to remove:\n");
            scanf("%s", name);
            removePerson(&head, name);
            break;
        case 4:
            printf("VIP GUEST!\n");
            printf("Enter name: ");
            scanf("%s", name);
            printf("Enter age: ");
            scanf("%d", &age);
            addVIP(&head, name, age);
            break;
        case 5:
            printf("Enter name to search:\n");
            scanf("%s", name);
            if (searchPerson(head, name))
                printf("%s found in line\n", name);
            else
                printf("%s not in line\n", name);
            break;
        case 6:
            reverseQueue(&head);
            printf("Line reversed!\n");
            break;
        case 7:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid option. Try again.\n");
        }
    } while (choice != 7);

    return 0;
}

// Function definitions

// Print the queue and its length
void printQueue(Person* head)
{
    int length = 0;
    Person* current = head;
    if (current == NULL)
    {
        printf("0 people in line:\n");
    }
    else
    {
        while (current != NULL)
        {
            length++;
            current = current->next;
        }
        printf("%d people in line:\n", length);
        while (current != NULL)
        {
            printf("Name: %s, Age: %d\n", current->name, current->age);
        }
    }
}

// Add a person to the queue
void addPerson(Person** head, char* name, int age, char friends[][50], int friendsCount)
{
    Person* newPerson = (Person*)malloc(sizeof(Person));
    strcpy(newPerson->name, name);
    newPerson->age = age;
    newPerson->next = NULL;

    if (*head == NULL)
    {
        *head = newPerson;
        return;
    }

    Person* current = *head;
    Person* previous = NULL;

    while (current != NULL)
    {
        for (int i = 0; i < friendsCount; i++)
        {
            if (strcmp(friends[i], current->name) == 0)
            {
                newPerson->next = current->next;
                current->next = newPerson;
                return;
            }
        }
        previous = current;
        current = current->next;
    }

    previous->next = newPerson;
}

// Remove a person from the queue
void removePerson(Person** head, char* name)
{
    Person* current = *head;
    Person* previous = NULL;

    while (current != NULL && strcmp(current->name, name) != 0)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("%s not in line\n", name);
        return;
    }

    if (previous == NULL)
    {
        *head = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    free(current);
    printf("%s removed from line\n", name);
}

// Add a VIP to the queue
void addVIP(Person** head, char* name, int age)
{
    Person* newPerson = (Person*)malloc(sizeof(Person));
    strcpy(newPerson->name, name);
    newPerson->age = age;
    newPerson->next = *head;
    *head = newPerson;
}

// Search for a person in the queue
int searchPerson(Person* head, char* name)
{
    Person* current = head;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Reverse the queue
void reverseQueue(Person** head)
{
    Person* prev = NULL;
    Person* current = *head;
    Person* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;
}
