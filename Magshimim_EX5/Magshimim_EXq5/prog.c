/*********************************
* Class: MAGSHIMIM C2           *
* Week 4                        *
* HW solution                   *
**********************************/

#include <stdlib.h>
#include <stdio.h>

int* createArr(int len);

int main(void)
{
    int size = 0;
    int* pArr = NULL; // Initialize pArr to NULL for safety

    printf("Enter a number of cells: ");
    scanf("%d", &size); // Corrected: Added '&' before size to pass its address

    if (size <= 0) {
        printf("Invalid input. Size must be greater than 0.\n");
        return 1; // Return 1 to indicate an error
    }

    pArr = createArr(size);
    if (pArr == NULL) {
        printf("Memory allocation failed.\n");
        return 1; // Return 1 to indicate an error
    }

    printf("The array is at address %p: ", (void*)pArr);
    free(pArr); // Free the allocated memory

    return 0;
}

/*
Function creates an array
input: number of cells in the array
output: pointer to the new array
*/
int* createArr(int size)
{
    int* pArr = (int*)malloc(size * sizeof(int)); // Corrected: Allocate memory for 'size' integers

    if (pArr == NULL) {
        printf("Memory allocation failed.\n");
        return NULL; // Return NULL to indicate failure
    }

    for (int i = 0; i < size; i++)
    {
        printf("Please enter a number for index %d: ", i);
        scanf("%d", &pArr[i]); // Corrected: Read input into pArr[i]
    }

    return pArr;
}
