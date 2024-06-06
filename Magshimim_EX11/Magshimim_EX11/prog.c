#include <stdio.h>

void printPerfectSquares(int n);

int main() 
{
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    getchar();

    printPerfectSquares(n);

    printf("Press Enter to exit...");
    
    getchar(); 
    return 0;
}

void printPerfectSquares(int n)//O(sqrt(n)) runtime complexities
{
    int i = 1;
    while (i * i <= n) 
    {
        printf("%d\n", i * i);
        i++;
    }
}