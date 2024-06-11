/*********************************
* Class: MAGSHIMIM C2             *
* Week:                           *
* Name:                           *
* Credits:                        *
**********************************/

#include <stdio.h>

// The function prints all the numbers divisible by b in the range (a, b)
// The runtime complexity of the function is O(a / b)

void function(int a, int b);

int main() {
    int a, b;

    printf("Enter value for a: ");
    scanf("%d", &a);
    getchar();  // Wait for user input

    printf("Enter value for b: ");
    scanf("%d", &b);
    getchar();  // Wait for user input

    function(a, b);

    printf("Press Enter to exit...");
    getchar();  // Wait for user input before exiting

    return 0;
}

void function(int a, int b) {
    for (int i = b; i <= a; i += b) {
        printf("%d ", i);
    }
    printf("\n");
}
