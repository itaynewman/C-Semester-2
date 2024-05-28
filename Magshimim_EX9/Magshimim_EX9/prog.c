/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <string.h>

int isPalindrome(char str[], int beg, int end);

int main(void)
{
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove the newline character at the end if there is one
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') 
    {
        str[len - 1] = '\0';
        len--; // Adjust length after removing newline
    }

    if (isPalindrome(str, 0, len - 1)) 
    {
        printf("Yes, Its a palindrome\n");
    }
    else 
    {
        printf("Not a Palindrome\n");
    }

    getchar();
    return 0;
}

int isPalindrome(char str[], int beg, int end)
{
    if (beg >= end) 
    {
        return 1; // Base case: If pointers have crossed, it's a palindrome
    }
    if (str[beg] != str[end]) 
    {
        return 0; // Base case: If characters at pointers don't match, it's not a palindrome
    }
    return isPalindrome(str, beg + 1, end - 1); // Recursive case: Move pointers inward
}
