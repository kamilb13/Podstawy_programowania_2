#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

#define NUMBER_OF_VERTICES 5

typedef int matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES];

const matrix adjacency_matrix = {
    {0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 0, 1},
    {1, 1, 0, 1, 0}
};

void bfs(const matrix adjacency_matrix, bool visited[], int start_vertex)
{
    struct fifo_pointers queue;
    queue.head = queue.tail = NULL;

    enqueue(&queue, start_vertex);
    visited[start_vertex] = true;

    while (queue.head)
    {
        int vertex = dequeue(&queue);
        printf("%d ", vertex);

        for (int i = 0; i < NUMBER_OF_VERTICES; i++)
        {
            if (adjacency_matrix[vertex][i] && !visited[i])
            {
                enqueue(&queue, i);
                visited[i] = true;
            }
        }
    }
}

void bfsTraversal(const matrix adjacency_matrix, int start_vertex)
{
    bool visited[NUMBER_OF_VERTICES] = {false};

    printf("Przeszukiwanie BFS rozpoczynaj¹ce siê od wierzcho³ka %d: ", start_vertex);
    bfs(adjacency_matrix, visited, start_vertex);
    printf("\n");
}

int main(void)
{
    bfsTraversal(adjacency_matrix, 0);

    return 0;
}
