#include<stdio.h>
#include<stdbool.h>

#define NUMBER_OF_VERTICES 5

typedef int matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES];

const matrix adjacency_matrix_directed = {
    {0, 1, 0, 0, 1},
    {0, 0, 1, 1, 0},
    {0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0}
};

const matrix adjacency_matrix_undirected = {
    {0, 1, 0, 0, 1},
    {1, 0, 1, 1, 0},
    {0, 1, 0, 0, 1},
    {0, 1, 0, 0, 1},
    {1, 0, 1, 1, 0}
};

bool is_directed_graph(const matrix adjacency_matrix)
{
    for(int i = 0; i < NUMBER_OF_VERTICES; i++) {
        for(int j = 0; j < NUMBER_OF_VERTICES; j++) {
            if(adjacency_matrix[i][j] != adjacency_matrix[j][i]) {
                return true;
            }
        }
    }
    return false;
}

int main(void)
{
    bool is_directed = is_directed_graph(adjacency_matrix_directed);
    if(is_directed) {
        printf("Macierz s¹siedztwa opisuje graf skierowany.\n");
    } else {
        printf("Macierz s¹siedztwa opisuje graf nieskierowany.\n");
    }
    return 0;
}
