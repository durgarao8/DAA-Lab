#include <stdio.h>

#define MAX 20
#define INF 1000000000


/* Find the unvisited vertex with minimum distance */
int findMinDistance(int dist[], int visited[], int n)
{
    int min = INF;
    int minIndex = -1;

    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}


/* Print the shortest path */
void printPath(int parent[], int destination)
{
    int path[MAX];
    int length = 0;
    int current = destination;

    /* Store path in reverse order */
    while (current != -1)
    {
        path[length] = current;
        length++;
        current = parent[current];
    }

    /* Print path in correct order */
    for (int i = length - 1; i >= 0; i--)
    {
        printf("%c", 'A' + path[i]);

        if (i != 0)
        {
            printf(" -> ");
        }
    }
}


/* Dijkstra's shortest path algorithm */
void dijkstra(int graph[MAX][MAX], int n, int source)
{
    int dist[MAX];
    int visited[MAX];
    int parent[MAX];

    /* Initialization */
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    /* Distance from source to itself is 0 */
    dist[source] = 0;


    /* Main Dijkstra loop */
    for (int count = 0; count < n - 1; count++)
    {
        /* Find nearest unvisited vertex */
        int u = findMinDistance(dist, visited, n);

        /* No more reachable vertices */
        if (u == -1)
        {
            break;
        }

        /* Mark vertex as visited */
        visited[u] = 1;


        /* Update distances of adjacent vertices */
        for (int v = 0; v < n; v++)
        {
            if (visited[v] == 0 &&
                graph[u][v] > 0 &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];

                /* Store previous vertex */
                parent[v] = u;
            }
        }
    }


    /* Display results */
    printf("\n");
    printf("===============================================\n");
    printf(" SHORTEST PATHS FROM VERTEX %c\n", 'A' + source);
    printf("===============================================\n");

    printf("\n%-15s %-15s %s\n",
           "Destination",
           "Distance",
           "Shortest Path");

    printf("-----------------------------------------------\n");


    for (int i = 0; i < n; i++)
    {
        printf("%-15c ", 'A' + i);

        if (dist[i] == INF)
        {
            printf("%-15s %s\n",
                   "INF",
                   "No route");
        }
        else
        {
            printf("%-15d ",
                   dist[i]);

            printPath(parent, i);

            printf("\n");
        }
    }
}


/* Main function */
int main(void)
{
    int graph[MAX][MAX];

    int n;
    int source;


    printf("===============================================\n");
    printf("       DIJKSTRA'S SHORTEST PATH ALGORITHM\n");
    printf("===============================================\n");


    /* Read number of vertices */
    printf("\nEnter number of vertices (maximum %d): ", MAX);
    scanf("%d", &n);


    /* Validate number of vertices */
    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of vertices.\n");
        return 1;
    }


    printf("\nVertices are named:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%c ", 'A' + i);
    }

    printf("\n");


    /* Read adjacency matrix */
    printf("\nEnter the adjacency matrix:\n");
    printf("Use 0 if there is no direct edge.\n");
    printf("Use positive values for edge weights.\n\n");


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);


            /* Dijkstra cannot handle negative weights */
            if (graph[i][j] < 0)
            {
                printf("\nError: Negative edge weights are not "
                       "allowed in Dijkstra's algorithm.\n");

                return 1;
            }
        }
    }


    /* Read source vertex */
    printf("\nEnter source vertex number ");
    printf("(A=0, B=1, C=2, ...): ");

    scanf("%d", &source);


    /* Validate source */
    if (source < 0 || source >= n)
    {
        printf("Invalid source vertex.\n");
        return 1;
    }


    /* Run Dijkstra */
    dijkstra(graph, n, source);


    return 0;
}