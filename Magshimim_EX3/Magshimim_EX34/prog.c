/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>

void decrypt(char* cipher, int n);
void reverse(char* str);

int main() {
    char text[51];  // Encrypted text
    int key;  // Key for decryption

    printf("Enter cypher to decrypt: ");
    scanf("%s", text);  // Input the encrypted text

    printf("Enter decryption key: ");
    scanf("%d", &key);  // Input the decryption key

    reverse(text);  // Reverse the input string
    decrypt(text, key);
    printf("Decrypted text: %s\n", text);  // Output the decrypted text
    getchar();
    getchar();
    return 0;
}

void reverse(char* str) {
    int length = strlen(str);
    char temp;
    for (int i = 0; i < length / 2; ++i) {
        temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

void decrypt(char* cipher, int n)
{
    while (*cipher)
    {
        *cipher = 'a' + ((*cipher - 'a' + n) % 26);
        ++cipher;
    }
}
