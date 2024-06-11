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

Node* concatenate(Node* list1, Node* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    Node* temp = list1;

    // Traverse to the end of the first list
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Link the end of the first list to the start of the second list
    temp->next = list2;

    return list1;
}
