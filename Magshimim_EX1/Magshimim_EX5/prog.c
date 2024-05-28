/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>

int main(void)
{

	int arr[] = { 1, 2, 3, 4 };
	int i = 0;
	int sum = 0;
	for (i = 0; i < 4; i++)
	{
		if (arr[i] % 2 == 0)
		{
			sum += arr[i];
		}
	}
	getchar();
	return 0;
}