//Updated code containing parent array
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

#define V 9

int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[], int parent[])
{
    printf("Vertex \t\t Distance from Source \t\t Parent\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t\t %d \t\t\t %d\n", i, dist[i], parent[i]);
}

void dijkstra(int graph[V][V], int src)
{
    int dist[V];
    bool sptSet[V];
    int parent[V]; // Creating an array of size V to store the parent of each vertex

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1; // Initialize parent array with -1, incidcating that initally no vertex has a parent 
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; // This records the parent of vertex v as u when a shorter path to v is found through u
            }
        }
    }

    printSolution(dist, parent);
}

int main()
{
    int graph[V][V] = { {0, 4, 0, 0, 0, 0, 0, 8, 0},
                        {4, 0, 8, 0, 0, 0, 0, 11, 0},
                        {0, 8, 0, 7, 0, 4, 0, 0, 2},
                        {0, 0, 7, 0, 9, 14, 0, 0, 0},
                        {0, 0, 0, 9, 0, 10, 0, 0, 0},
                        {0, 0, 4, 14, 10, 0, 2, 0, 0},
                        {0, 0, 0, 0, 0, 2, 0, 1, 6},
                        {8, 11, 0, 0, 0, 0, 1, 0, 7},
                        {0, 0, 2, 0, 0, 0, 6, 7, 0} };

    dijkstra(graph, 0);

    return 0;
}

//This should also work for a directed graph, and we just have to correctly represent the edges and the weights
//In the adjacency matrix to reflect the directed nature of the graph. graph[u][v] represents the weight of the 
//edge from vertex u to vertex v.