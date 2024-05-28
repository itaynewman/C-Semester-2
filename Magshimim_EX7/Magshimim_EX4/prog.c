/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_LEN 100

char csv[MAX_ROWS][MAX_COLS][MAX_LEN];
int rowCount = 0;
int colCount = 0;

void loadCSV(const char* filename);
void saveCSV(const char* filename);
void searchTerm(const char* term);
void changeValue(int row, int col, const char* newValue);
void copyValue(int srcRow, int srcCol, int destRow, int destCol);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <csv_file>\n", argv[0]);
        return 1;
    }

    loadCSV(argv[1]);

    int choice;
    while (1) {
        printf("Please enter your choice:\n");
        printf("1 - Search a term in the document.\n");
        printf("2 - change a value in a specific place.\n");
        printf("3 - copy a value from one place to another\n");
        printf("4 - Exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            char term[MAX_LEN];
            printf("Enter string to search: ");
            scanf("%s", term);
            searchTerm(term);
        }
        else if (choice == 2) {
            int row, col;
            char newValue[MAX_LEN];
            printf("Enter row number: ");
            scanf("%d", &row);
            printf("Enter column number: ");
            scanf("%d", &col);
            printf("Enter new value: ");
            scanf("%s", newValue);
            changeValue(row - 1, col - 1, newValue);
        }
        else if (choice == 3) {
            int srcRow, srcCol, destRow, destCol;
            printf("Enter source row: ");
            scanf("%d", &srcRow);
            printf("Enter source column: ");
            scanf("%d", &srcCol);
            printf("Enter destination row: ");
            scanf("%d", &destRow);
            printf("Enter destination column: ");
            scanf("%d", &destCol);
            copyValue(srcRow - 1, srcCol - 1, destRow - 1, destCol - 1);
        }
        else if (choice == 4) {
            saveCSV(argv[1]);
            printf("Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    getchar();
    return 0;
}

void loadCSV(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file %s\n", filename);
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        int col = 0;
        while (token) {
            strcpy(csv[rowCount][col], token);
            token = strtok(NULL, ",");
            col++;
        }
        rowCount++;
        if (col > colCount) colCount = col;
    }

    fclose(file);
}

void saveCSV(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Could not open file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            fprintf(file, "%s", csv[i][j]);
            if (j < colCount - 1) fprintf(file, ",");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void searchTerm(const char* term) {
    int count = 0;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            if (strstr(csv[i][j], term)) {
                count++;
            }
        }
    }
    printf("Value appears %d times\n", count);
}

void changeValue(int row, int col, const char* newValue) {
    if (row >= rowCount || col >= colCount) {
        printf("Invalid row or column\n");
        return;
    }
    strcpy(csv[row][col], newValue);
    printf("A change was made in row %d\n", row + 1);
}

void copyValue(int srcRow, int srcCol, int destRow, int destCol) {
    if (srcRow >= rowCount || srcCol >= colCount || destRow >= rowCount || destCol >= colCount) {
        printf("Invalid row or column\n");
        return;
    }
    strcpy(csv[destRow][destCol], csv[srcRow][srcCol]);
    printf("Change was made successfully\n");
}
