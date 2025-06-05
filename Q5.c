#include <stdio.h>
#include <limits.h>

#define SIZE 7
#define INF 99999

// Edge structure
typedef struct {
    int src, dest, weight;
} Edge;

char cities[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};

// List of edges in the graph
Edge edges[] = {
    {0, 1, 6}, {1, 0, 6},
    {0, 6, 15}, {6, 0, 15},
    {1, 2, 11}, {2, 1, 11},
    {1, 3, 5}, {3, 1, 5},
    {2, 3, 17}, {3, 2, 17},
    {2, 5, 9}, {5, 2, 9},
    {2, 6, 25}, {6, 2, 25},
    {3, 4, 22}, {4, 3, 22},
    {4, 5, 10}, {5, 4, 10},
    {5, 6, 12}, {6, 5, 12}
};

int numEdges = sizeof(edges) / sizeof(edges[0]);

void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%c", cities[j]);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %c", cities[j]);
}

void bellmanFord(int src) {
    int dist[SIZE];
    int parent[SIZE];

    // Step 1: initialize distances
    for (int i = 0; i < SIZE; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    // Step 2: relax all edges |V| - 1 times
    for (int i = 1; i < SIZE; i++) {
        for (int j = 0; j < numEdges; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    // Step 3: check for negative-weight cycles
    for (int j = 0; j < numEdges; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Graph contains negative weight cycle.\n");
            return;
        }
    }

    // Print the result
    printf("Minimum cost paths from city A:\n");
    for (int i = 0; i < SIZE; i++) {
        if (i != src) {
            printf("To %c: ", cities[i]);
            if (dist[i] == INF) {
                printf("No path available\n");
            } else {
                printPath(parent, i);
                printf(" | Total Cost: %d\n", dist[i]);
            }
        }
    }
}

int main() {
    bellmanFord(0); // 0 corresponds to city A
    return 0;
}
