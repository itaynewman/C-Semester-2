/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>

#define ARRAY_SIZE 5

void print_array(int* array);
int* create_array();

//i did succseed in printing the array but the output was also came with a random negative number
//it does that because after the program exits the function the deallocates the memory so the code prints that random number

int main()
{
    int* arr = create_array();
    print_array(arr);
    return 0;
}

void print_array(int* array)
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int* create_array()
{
    int array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = i + 1;
    }
    return array;
}
