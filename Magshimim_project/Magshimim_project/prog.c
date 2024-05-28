/*********************************
* Class: MAGSHIMIM C2             *
* Week:                          *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dirent.h"

#define VIRUS_SIGNATURE_MAX_LENGTH 1000
#define MAX_RESULTS 10000

// Struct for storing scan results
typedef struct {
    char filePath[1024];
    char status[20];
    char location[20];
} ScanResult;

// Function declarations
int readVirusSignature(char* filePath, char* virusSignature);
int scanFileForVirus(char* filePath, char* virusSignature);
int quickScanFileForVirus(char* filePath, char* virusSignature, char* resultLocation);
void scanDirectory(char* directoryPath, char* virusSignature, bool quickScan, FILE* logFile, ScanResult* results, int* resultCount);
int compareResults(const void* a, const void* b);

int main(int argc, char* argv[])
{
    bool isQuickScan = false;
    if (argc != 3)
    {
        printf("Usage: %s <directory_path> <virus_signature_file>\n", argv[0]);
        return 1;
    }

    printf("Welcome to MAGSHIMIM VIRUS SCANNER\n\n");

    printf("Folder to scan: %s\n", argv[1]);
    printf("Virus signature file: %s\n\n", argv[2]);

    printf("Press 0 for a normal scan or any other key for a quick scan: \n");
    int scanChoice;
    if (scanf("%d", &scanChoice) != 1) {
        printf("Invalid input. Performing quick scan by default.\n");
        isQuickScan = true;
    }
    else {
        isQuickScan = (scanChoice != 0);
    }

    printf("Scanning began...\n");
    printf("This process may take several minutes...\n");

    char virusSignature[VIRUS_SIGNATURE_MAX_LENGTH];
    if (!readVirusSignature(argv[2], virusSignature))
    {
        return 1;
    }

    FILE* logFile = fopen("AntiVirusLog.txt", "w");
    if (logFile == NULL)
    {
        printf("Error creating log file\n");
        return 1;
    }

    // Write header to log file
    fprintf(logFile, "Anti-virus began! Welcome!\n\n");
    fprintf(logFile, "Folder to scan:\n%s\n", argv[1]);
    fprintf(logFile, "Virus signature file:\n%s\n\n", argv[2]);
    fprintf(logFile, "Scanning option:\n%s Scan\n\n", isQuickScan ? "Quick" : "Normal");
    fprintf(logFile, "Results:\n");

    // Allocate memory for results on the heap
    ScanResult* results = malloc(MAX_RESULTS * sizeof(ScanResult));

    // Check if memory allocation was successful
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(logFile);
        return 1;
    }

    int resultCount = 0;

    scanDirectory(argv[1], virusSignature, isQuickScan, logFile, results, &resultCount);

    // Sort results alphabetically by file path
    qsort(results, resultCount, sizeof(ScanResult), compareResults);

    // Print and log sorted results
    for (int i = 0; i < resultCount; i++) {
        if (isQuickScan && strcmp(results[i].status, "Infected!") == 0) {
            fprintf(logFile, "%s  %s (found in %s)\n", results[i].filePath, results[i].status, results[i].location);
            printf("%s  %s (found in %s)\n", results[i].filePath, results[i].status, results[i].location);
        }
        else {
            fprintf(logFile, "%s  %s\n", results[i].filePath, results[i].status);
            printf("%s  %s\n", results[i].filePath, results[i].status);
        }
    }

    fclose(logFile);
    free(results);

    printf("Scanning completed. Results saved to AntiVirusLog.txt\n");

    return 0;
}

// Function to read the virus signature from a file
// Input: filePath (path to the virus signature file), virusSignature (buffer to store the virus signature)
// Output: 1 if successful, 0 if there is an error
int readVirusSignature(char* filePath, char* virusSignature)
{
    FILE* file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Error opening virus signature file: %s\n", filePath);
        return 0;
    }

    if (fgets(virusSignature, VIRUS_SIGNATURE_MAX_LENGTH, file) == NULL)
    {
        printf("Error reading virus signature file: %s\n", filePath);
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

// Function to scan a file for a virus using the virus signature
// Input: filePath (path to the file to be scanned), virusSignature (the virus signature)
// Output: 1 if the file is infected, 0 if the file is clean
int scanFileForVirus(char* filePath, char* virusSignature) {
    FILE* file = fopen(filePath, "rb");
    if (file == NULL) {
        printf("Error opening file: %s\n", filePath);
        return 0; // Returning 0 to indicate a clean file due to error in opening
    }

    int keySize = strlen(virusSignature);
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (keySize > fileSize) {
        fclose(file);
        return 0; // Returning 0 to indicate a clean file because it's too small to contain the virus signature
    }

    char* vBuffer = (char*)malloc(keySize);
    if (vBuffer == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return 0; // Returning 0 to indicate a clean file due to memory allocation error
    }

    memcpy(vBuffer, virusSignature, keySize);
    char* buffer = (char*)malloc(keySize);
    if (buffer == NULL) {
        printf("Memory allocation failed for file buffer\n");
        free(vBuffer);
        fclose(file);
        return 0; // Returning 0 to indicate a clean file due to memory allocation error
    }

    int filePos = 0;
    int bytesRead = 0;
    while ((bytesRead = fread(buffer, 1, keySize, file)) == keySize) {
        if (memcmp(buffer, vBuffer, keySize) == 0) {
            free(buffer);
            free(vBuffer);
            fclose(file);
            return 1; // Returning 1 to indicate an infected file
        }
        filePos++;
        fseek(file, filePos, SEEK_SET);
    }

    free(buffer);
    free(vBuffer);
    fclose(file);
    return 0; // Returning 0 to indicate a clean file
}

// Function to quickly scan a file for a virus using the virus signature
// Input: filePath (path to the file to be scanned), virusSignature (the virus signature), resultLocation (buffer to store the location where the virus was found)
// Output: 1 if the file is infected, 0 if the file is clean
int quickScanFileForVirus(char* filePath, char* virusSignature, char* resultLocation)
{
    FILE* file = fopen(filePath, "rb");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filePath);
        return 0; // Returning 0 to indicate a clean file due to error in opening
    }

    int keySize = strlen(virusSignature);
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (keySize > fileSize) {
        fclose(file);
        return 0; // Returning 0 to indicate a clean file because it's too small to contain the virus signature
    }

    int scanLength = fileSize / 5;
    char* buffer = (char*)malloc(keySize + 1);

    if (!buffer)
    {
        fclose(file);
        printf("Memory allocation error\n");
        return 0; // Returning 0 to indicate a clean file due to memory allocation error
    }

    // Scan first 20%
    for (int i = 0; i < scanLength; i++)
    {
        fread(buffer, 1, keySize, file);
        buffer[keySize] = '\0';
        if (strstr(buffer, virusSignature) != NULL)
        {
            strcpy(resultLocation, "first 20%");
            free(buffer);
            fclose(file);
            return 1; // Returning 1 to indicate an infected file found in the first 20%
        }
        fseek(file, 1 - keySize, SEEK_CUR); // Move back to re-read with overlap
    }

    // Scan last 20%
    fseek(file, -scanLength, SEEK_END);
    for (int i = 0; i < scanLength; i++)
    {
        fread(buffer, 1, keySize, file);
        buffer[keySize] = '\0';
        if (strstr(buffer, virusSignature) != NULL)
        {
            strcpy(resultLocation, "last 20%");
            free(buffer);
            fclose(file);
            return 1; // Returning 1 to indicate an infected file found in the last 20%
        }
        fseek(file, 1 - keySize, SEEK_CUR); // Move back to re-read with overlap
    }

    free(buffer);
    fclose(file);
    return 0; // Returning 0 to indicate a clean file
}

// Function to scan a directory for viruses
// Input: directoryPath (path to the directory to be scanned), virusSignature (the virus signature), quickScan (boolean indicating whether to perform a quick scan), logFile (file pointer to the log file), results (array to store the scan results), resultCount (pointer to an integer to store the count of results)
// Output: None (results are stored in the results array and resultCount is updated)
void scanDirectory(char* directoryPath, char* virusSignature, bool quickScan, FILE* logFile, ScanResult* results, int* resultCount)
{
    DIR* dir;
    struct dirent* entry;

    dir = opendir(directoryPath);
    if (dir == NULL)
    {
        printf("Error opening directory: %s\n", directoryPath);
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, entry->d_name);

        if (entry->d_type == DT_REG) {
            int infected;
            char resultLocation[20] = "";
            if (quickScan)
            {
                infected = quickScanFileForVirus(filePath, virusSignature, resultLocation);
            }
            else
            {
                infected = scanFileForVirus(filePath, virusSignature);
            }

            if (infected)
            {
                strcpy(results[*resultCount].filePath, filePath);
                strcpy(results[*resultCount].status, "Infected!");
                if (quickScan)
                {
                    strcpy(results[*resultCount].location, resultLocation);
                }
                else
                {
                    results[*resultCount].location[0] = '\0';
                }
                (*resultCount)++;
            }
            else
            {
                strcpy(results[*resultCount].filePath, filePath);
                strcpy(results[*resultCount].status, "Clean");
                results[*resultCount].location[0] = '\0';
                (*resultCount)++;
            }
        }
    }

    closedir(dir);
}

// Function to compare two scan results for sorting
// Input: a (pointer to the first ScanResult), b (pointer to the second ScanResult)
// Output: Negative value if a < b, 0 if a == b, positive value if a > b
int compareResults(const void* a, const void* b) {
    ScanResult* resultA = (ScanResult*)a;
    ScanResult* resultB = (ScanResult*)b;
    return strcmp(resultA->filePath, resultB->filePath);
}
