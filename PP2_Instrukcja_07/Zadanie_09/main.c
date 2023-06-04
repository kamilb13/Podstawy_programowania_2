#include <stdio.h>
#include <stdbool.h>

#define NUMBER_OF_VERTICES 5

typedef int matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES];

const matrix adjacency_matrix = {
    {0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 0, 1},
    {1, 1, 0, 1, 0}
};

void dfs(const matrix adjacency_matrix, bool visited[], int vertex)
{
    visited[vertex] = true;
    printf("%d ", vertex);

    for (int i = 0; i < NUMBER_OF_VERTICES; i++)
    {
        if (adjacency_matrix[vertex][i] && !visited[i])
        {
            dfs(adjacency_matrix, visited, i);
        }
    }
}

void dfsTraversal(const matrix adjacency_matrix, int start_vertex)
{
    bool visited[NUMBER_OF_VERTICES] = {false};

    printf("Przeszukiwanie DFS rozpoczynaj¹ce siê od wierzcho³ka %d: ", start_vertex);
    dfs(adjacency_matrix, visited, start_vertex);
    printf("\n");
}

int main(void)
{
    dfsTraversal(adjacency_matrix, 0);

    return 0;
}
