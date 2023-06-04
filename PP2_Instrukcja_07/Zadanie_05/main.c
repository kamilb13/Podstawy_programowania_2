#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define NUMBER_OF_VERTICES 5

typedef uint8_t matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES];

void add_edge(matrix adjacency_matrix, int vertex1, int vertex2)
{
    adjacency_matrix[vertex1][vertex2] = 1;
    adjacency_matrix[vertex2][vertex1] = 1;
}

void remove_edge(matrix adjacency_matrix, int vertex1, int vertex2)
{
    adjacency_matrix[vertex1][vertex2] = 0;
    adjacency_matrix[vertex2][vertex1] = 0;
}

void print_adjacency_matrix(matrix adjacency_matrix)
{
    for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
        for (int j = 0; j < NUMBER_OF_VERTICES; j++) {
            printf("%d ", adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    matrix adjacency_matrix = {0};

    add_edge(adjacency_matrix, 0, 1);
    add_edge(adjacency_matrix, 0, 4);
    add_edge(adjacency_matrix, 1, 2);
    add_edge(adjacency_matrix, 1, 3);
    add_edge(adjacency_matrix, 1, 4);
    add_edge(adjacency_matrix, 2, 3);
    add_edge(adjacency_matrix, 3, 4);

    print_adjacency_matrix(adjacency_matrix);

    return 0;
}
