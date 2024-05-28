#include <stdio.h>

#define ARRAY_SIZE 11

void printBeforeX(int* array, int size, int* pointer);

int main() {
    int arr[ARRAY_SIZE] = { 4, 8, 6, 2, 1, 3, 5, 7, 8, 9, 5 };

    printf("Please enter an offset to search in the array’s address domain: ");
    int offset;
    scanf("%d", &offset);

    printBeforeX(arr, ARRAY_SIZE, arr + offset);

    getchar();
    getchar();

    return 0;
}

void printBeforeX(int* array, int size, int* pointer) {
    if (pointer >= array && pointer < array + size) {
        printf("The array elements up to the index %d are: ", (int)(pointer - array));
        for (int* ptr = array; ptr < pointer; ptr++) {
            printf("%d ", *ptr);
        }
        printf("\n");
    }
    else {
        printf("Index %d is out of the array range\n", (int)(pointer - array));
    }
}
