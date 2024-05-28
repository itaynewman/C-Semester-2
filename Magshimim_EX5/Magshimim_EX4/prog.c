/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#define _CRTDBG_MAP_ALLOC

int validateInput(int min, int max);
void printDistribution(int* responses, int numRespondents);

int main() {

    int numRespondents;
    printf("Enter the number of respondents: ");
    scanf("%d", &numRespondents);

    int* responses = (int*)malloc(numRespondents * sizeof(int));
    if (responses == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter responses for %d respondents (1-5):\n", numRespondents);
    for (int i = 0; i < numRespondents; i++) {
        responses[i] = validateInput(1, 5);
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1 - Calculate average\n");
        printf("2 - Change a response\n");
        printf("3 - Add respondents\n");
        printf("4 - Print response distribution\n");
        printf("5 - Exit\n");
        choice = validateInput(1, 5);

        switch (choice) {
        case 1:
        {
            float sum = 0;
            for (int i = 0; i < numRespondents; i++) {
                sum += responses[i];
            }
            printf("Average response: %.2f\n", sum / numRespondents);
        }
        break;
        case 2:
        {
            printf("Enter the index of the response to change (1-%d): ", numRespondents);
            int index = validateInput(1, numRespondents) - 1;
            printf("Enter the new response (1-5): ");
            responses[index] = validateInput(1, 5);
        }
        break;
        case 3:
        {
            int additionalRespondents;
            printf("Enter the number of additional respondents: ");
            scanf("%d", &additionalRespondents);

            responses = (int*)realloc(responses, (numRespondents + additionalRespondents) * sizeof(int));
            if (responses == NULL) {
                printf("Memory reallocation failed\n");
                return 1;
            }

            printf("Enter responses for %d additional respondents (1-5):\n", additionalRespondents);
            for (int i = numRespondents; i < numRespondents + additionalRespondents; i++) {
                responses[i] = validateInput(1, 5);
            }
            numRespondents += additionalRespondents;
        }
        break;
        case 4:
            printDistribution(responses, numRespondents);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    free(responses);

    printf("leaks: %d", _CrtDumpMemoryLeaks());

    return 0;
}

int validateInput(int min, int max) {
    int num;
    do {
        printf("Enter a number between %d and %d: ", min, max);
        scanf("%d", &num);
    } while (num < min || num > max);
    return num;
}

void printDistribution(int* responses, int numRespondents) {
    printf("Response distribution:\n");
    for (int i = 1; i <= 5; i++) {
        int count = 0;
        for (int j = 0; j < numRespondents; j++) {
            if (responses[j] == i) {
                count++;
            }
        }
        printf("%d - %d\n", i, count);
    }
}
