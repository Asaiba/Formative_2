#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 7

// Adjacency matrix representing communication durations
int graph[SIZE][SIZE] = {
    {0, 6, 0, 0, 0, 0, 15},   // A
    {6, 0, 11, 5, 0, 0, 0},   // B
    {0, 11, 0, 17, 0, 9, 25}, // C
    {0, 5, 17, 0, 22, 0, 0},  // D
    {0, 0, 0, 22, 0, 10, 0},  // E
    {0, 0, 9, 0, 10, 0, 12},  // F
    {15, 0, 25, 0, 0, 12, 0}  // G
};

char employees[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

// BFS to find immediate contacts and longest interaction
void analyzeLeak(int suspectIndex) {
    printf("\nSuspected employee: %c\n", employees[suspectIndex]);
    printf("Direct communications:\n");

    int maxDuration = 0;
    int mostAtRisk = -1;

    for (int i = 0; i < SIZE; i++) {
        if (graph[suspectIndex][i] > 0) {
            printf("- %c (Duration: %d minutes)\n", employees[i], graph[suspectIndex][i]);
            if (graph[suspectIndex][i] > maxDuration) {
                maxDuration = graph[suspectIndex][i];
                mostAtRisk = i;
            }
        }
    }

    if (mostAtRisk != -1) {
        printf("The one who is Most at risk is: %c (Longest interaction: %d minutes)\n",
               employees[mostAtRisk], maxDuration);
    } else {
        printf("\nNo direct communications found for this employee.\n");
    }
}

int main() {
    char input;
    printf("Enter suspected employee (A-G): ");
    scanf(" %c", &input);

    // Convert character to index
    int suspectIndex = -1;
    for (int i = 0; i < SIZE; i++) {
        if (employees[i] == input) {
            suspectIndex = i;
            break;
        }
    }

    if (suspectIndex == -1) {
        printf("Invalid employee. Please enter A-G.\n");
        return 1;
    }

    analyzeLeak(suspectIndex);

    return 0;
}
