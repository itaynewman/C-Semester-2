/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function declarations
void rotateList(Node** head, int k);
void appendNode(Node** head, int data);
void printList(Node* head);
void freeList(Node* head);

int main() {
    Node* list = NULL;
    int n;

    printf("How many nodes in the list? ");
    scanf("%d", &n);

    printf("Enter numbers for each node:\n");
    for (int i = 0; i < n; i++) {
        int data;
        printf("Enter number: ");
        scanf("%d", &data);
        appendNode(&list, data);
    }

    int k;
    printf("Enter the value of k to rotate the list: ");
    scanf("%d", &k);

    printf("Original List: ");
    printList(list);

    rotateList(&list, k);

    printf("List after rotating by %d places: ", k);
    printList(list);

    // Free memory
    freeList(list);

    getchar();
    getchar();

    return 0;
}

void appendNode(Node** head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void rotateList(Node** head, int k) {
    if (*head == NULL || k == 0) return;

    // Find the length of the list
    int length = 0;
    Node* temp = *head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }

    // Adjust k to avoid unnecessary rotations
    k = k % length;
    if (k == 0) return;

    // Find the (k-1)-th node
    temp = *head;
    for (int i = 0; i < k - 1; i++) {
        temp = temp->next;
    }

    // New head is the k-th node
    Node* newHead = temp->next;

    // Traverse to the end of the list
    temp->next = NULL;
    temp = newHead;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = *head;

    // Update the head pointer
    *head = newHead;
}
