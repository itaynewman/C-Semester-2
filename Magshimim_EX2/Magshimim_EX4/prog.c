#include <stdio.h>

void sort(float* num1, float* num2, float* num3);

int main(void)
{
    float num1 = 0, num2 = 0, num3 = 0;

    printf("Please enter num1, num2, num3: \n");
    scanf("%f %f %f", &num1, &num2, &num3);

    sort(&num1, &num2, &num3);

    printf("After sorting: num1 = %.2f num2 = %.2f num3 = %.2f\n", num1, num2, num3);

    getchar();
    getchar();
    return 0;
}

void sort(float* num1, float* num2, float* num3) {
    float temp = 0;

    if (*num1 > *num2) {
        temp = *num1;
        *num1 = *num2;
        *num2 = temp;
    }

    if (*num2 > *num3) {
        temp = *num2;
        *num2 = *num3;
        *num3 = temp;
    }

    if (*num1 > *num2) {
        temp = *num1;
        *num1 = *num2;
        *num2 = temp;
    }
}
