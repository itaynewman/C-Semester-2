/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>

void swap(int* num1, int* num2);

int main(void)
{
	float num1 = 0, num2 = 0;

	printf("Enter two numbers: \n");
	scanf("%f %f", &num1, &num2);

	swap(&num1, &num2);

	printf("swapped: %f %f", num1, num2);

	getchar();
	getchar();
	return 0;
}

void swap(int* num1, int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}