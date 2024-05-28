/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>

int createArray();

int main(void)
{

	print(createArray());
	getchar();
	return 0;
}


int createArray()
{
	int arr[100] = { 9 };
	return &arr;
}
