/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int performAddition(int argc, char* argv[]);
int performMultiplication(int argc, char* argv[]);
void printUsage();

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        printUsage();
        return 1;
    }
    else if (argc <= 3)
    {
        printf("ERROR! Insufficient arguments.\n");
        printUsage();
        return 1;
    }
    else if (strcmp(argv[1], "MUL") != 0 && strcmp(argv[1], "ADD") != 0)
    {
        printf("ERROR! Invalid command.\n");
        printUsage();
        return 1;
    }

    if (strcmp(argv[1], "ADD") == 0)
    {
        return performAddition(argc, argv);
    }
    else if (strcmp(argv[1], "MUL") == 0)
    {
        return performMultiplication(argc, argv);
    }

    return 0;
}

int performAddition(int argc, char* argv[])
{
    int result = 0;
    for (int i = 2; i < argc; i++)
    {
        result += atoi(argv[i]);
    }
    printf("Sum: %d\n", result);
    return 0;
}

int performMultiplication(int argc, char* argv[])
{
    int result = 1; // Initialize to 1 for multiplication
    for (int i = 2; i < argc; i++)
    {
        result *= atoi(argv[i]);
    }
    printf("Product: %d\n", result);
    return 0;
}

void printUsage()
{
    printf("Usage: [ADD | MUL] <number> … <number>\n");
}
