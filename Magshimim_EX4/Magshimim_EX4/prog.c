/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int numOfDays = 0;
    float* arr = NULL;
    int i = 0;
    printf("enter number of days: \n");
    scanf("%d", &numOfDays);
    arr = (float*)malloc(numOfDays * sizeof(float));
    printf("enter the temp for each day:");
    for (i = 0; i < numOfDays; i++)
    {
        scanf("%f", &arr[i]);
    }
    for (i = 0; i < numOfDays; i++)
    {
        printf("%0.1f ", arr[i]);
    }
    return 0;
}
