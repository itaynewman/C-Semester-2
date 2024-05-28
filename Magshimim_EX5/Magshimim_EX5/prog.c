#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int* dynamicMemory = (int*)malloc(sizeof(int) * n);

    free(dynamicMemory);

    printf("leaks: %d", _CrtDumpMemoryLeaks());

    return 0;
}
