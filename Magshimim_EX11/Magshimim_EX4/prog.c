/*********************************
* Class: MAGSHIMIM C2             *
* Week:                           *
* Name:                           *
* Credits:                        *
**********************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function declarations
Node* createNode(int data);
void appendNode(Node** head, int data);
void printListFromNode(Node* head);
void freeList(Node* head);
Node* findKthFromEnd(Node* head, int k);

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
    printf("Choose a number k, and the k last values will be printed: ");
    scanf("%d", &k);

    printf("The list from that node to the end:\n");
    Node* kthFromEnd = findKthFromEnd(list, k);
    if (kthFromEnd != NULL) {
        printListFromNode(kthFromEnd);
    }
    else {
        printf("The list has fewer than %d elements.\n", k);
    }

    // Free memory
    freeList(list);

    getchar();
    getchar();

    return 0;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
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

void printListFromNode(Node* head) {
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

Node* findKthFromEnd(Node* head, int k) {
    Node* slow = head, * fast = head;

    // Move fast pointer k steps ahead
    for (int i = 0; i < k; i++) {
        if (fast == NULL) return NULL;  // If k is larger than the length of the list
        fast = fast->next;
    }

    // Move both pointers at the same speed until fast reaches the end
    while (fast != NULL) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

