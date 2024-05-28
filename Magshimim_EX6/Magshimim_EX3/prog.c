/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>

int main(void)
{
    int arr2d[3][3] = { {1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    int* arr = (int*)arr2d;
    int i = 0;
    for (i = 0; i < 9; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
    int arr1[] = { 11, 12 };
    int arr2[] = { 13, 14, 15, 16 };
    int arr3[] = { 17, 18, 19 };
    int* pArr[3] = { arr1, arr2, arr3 };
    int* pArr1d = (int*)pArr;
    for (i = 0; i < 9; i++)
    {
        printf("%d ", pArr1d[i]);
    }
    getchar();
}