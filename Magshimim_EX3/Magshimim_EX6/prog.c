/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <string.h>

#define PASSWORD "maGshimim2017"
#define STR_LEN 16
#define FALSE 0
#define TRUE !FALSE

int main(void)
{
    int pass = FALSE;
    char buff[STR_LEN];

    printf("Enter the password: ");
    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = '\0'; // Remove newline character if present

    if (strcmp(buff, PASSWORD) == 0)
    {
        printf("Correct Password \n");
        pass = TRUE;
    }
    else
    {
        printf("Wrong Password \n");
    }

    if (pass)
    {
        printf("Access given to the secret files \n");
    }

    getchar();
    return 0;
}
