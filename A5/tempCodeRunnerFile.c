#include <stdio.h>

#define V 4
#define INF 99999

void printSolution(int dist[][V], int parent[][V]) {
    printf("The following matrix shows the shortest distances and parent vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\t\t");
        for (int j = 0; j < V; j++) {
            printf("%d ", parent[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(int dist[][V]) {
    int parent[V][V];

    // Initialise parent matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            parent[i][j] = i;

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }

    // Check for negative cycles. If the diagonal elements of the distance matrix become negative after the 
    //algorithm runs, then there is a negative cycle in the graph
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("Graph contains negative cycle.\n");
            return;
        }
    }

    // Print the shortest distance matrix and parent matrix
    printSolution(dist, parent);
}

int main() {
    int graph[V][V] = {{0, 5, INF, 10},
                       {INF, 0, 3, INF},
                       {INF, INF, 0, 1},
                       {INF, INF, INF, 0}};

    floydWarshall(graph);
    return 0;
}
