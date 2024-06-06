/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <math.h>

void print_perfect_squares(int n);

int main() 
{
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    getchar();

    print_perfect_squares(n);

    printf("Press Enter to exit...");
    getchar();

    return 0;
}


//description: This function prints all the perfect squares up to a given number.
//input: The number up to which perfect squares will be printed.
//output: Void
void print_perfect_squares(int n) 
{
    int i = 1;
    while (i * i <= n) 
    {
        printf("%d\n", i * i);
        i++;
    }
}