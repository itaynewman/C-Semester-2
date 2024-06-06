#include <stdio.h>

void printPerfectSquares(int n);

int main() 
{
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    getchar();  // Wait for Enter after input

    printPerfectSquares(n);

    printf("Press Enter to exit...");
    getchar();  // Wait for Enter before exit

    return 0;
}

void printPerfectSquares(int n) 
{
    int i = 1;
    while (i * i <= n) 
    {
        printf("%d\n", i * i);
        i++;
    }
}