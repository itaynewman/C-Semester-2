/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copyTextFile(const char* source, const char* destination);
void copyBinaryFile(const char* source, const char* destination);

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <textCopy/binaryCopy> <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    const char* copyType = argv[1];
    const char* sourceFile = argv[2];
    const char* destinationFile = argv[3];

    FILE* sourceFp = fopen(sourceFile, "r");
    if (sourceFp == NULL) {
        printf("Error: Source file does not exist.\n");
        return 1;
    }
    fclose(sourceFp);

    FILE* destFp = fopen(destinationFile, "r");
    if (destFp != NULL) {
        fclose(destFp);
        printf("Destination file exists. Do you want to overwrite it? (yes/no): ");
        char response[4];
        fgets(response, 4, stdin);
        if (strncmp(response, "yes", 3) != 0) {
            printf("Copy operation cancelled.\n");
            return 0;
        }
    }

    if (strcmp(copyType, "textCopy") == 0) {
        copyTextFile(sourceFile, destinationFile);
    }
    else if (strcmp(copyType, "binaryCopy") == 0) {
        copyBinaryFile(sourceFile, destinationFile);
    }
    else {
        printf("Error: Invalid copy type. Use 'textCopy' or 'binaryCopy'.\n");
        return 1;
    }

    printf("File copied successfully.\n");
    return 0;
}

void copyTextFile(const char* source, const char* destination) {
    FILE* src = fopen(source, "r");
    FILE* dst = fopen(destination, "w");

    if (src == NULL || dst == NULL) {
        printf("Error: Unable to open source or destination file.\n");
        if (src != NULL) fclose(src);
        if (dst != NULL) fclose(dst);
        return;
    }

    int ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);
}

void copyBinaryFile(const char* source, const char* destination) {
    FILE* src = fopen(source, "rb");
    FILE* dst = fopen(destination, "wb");

    if (src == NULL || dst == NULL) {
        printf("Error: Unable to open source or destination file.\n");
        if (src != NULL) fclose(src);
        if (dst != NULL) fclose(dst);
        return;
    }

    fseek(src, 0, SEEK_END);
    long fileSize = ftell(src);
    fseek(src, 0, SEEK_SET);

    char* buffer = (char*)malloc(fileSize);
    if (buffer == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(src);
        fclose(dst);
        return;
    }

    fread(buffer, 1, fileSize, src);
    fwrite(buffer, 1, fileSize, dst);

    free(buffer);
    fclose(src);
    fclose(dst);

    getchar();
}
