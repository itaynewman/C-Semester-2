/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>

#define SIZE 8

void arrayInput(int* arr, int size);
void arrayEvenElements(int* arr, int size);

int main() {
	int arr[SIZE];

	arrayInput(arr, SIZE);

	arrayEvenElements(arr, SIZE);

	return 0;
}
void arrayInput(int* arr, int size)
{
	printf("Enter %d numbers: ", size);
	for (int i = 0; i < size; i++)
	{
		scanf("%d", arr + i);
	}
}

void arrayEvenElements(int* arr, int size)
{
	printf("The numbers in even indexes are: ");
	int* ptr = arr;
	for (int i = 0; i < size; i += 2)
	{
		printf("%d ", *(ptr + i));
	}
	printf("\n");
}
