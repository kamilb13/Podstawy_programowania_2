#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

#define NUMBER_OF_VERTICES 5

typedef int matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES];

struct vertex
{
    int vertex_number;
    struct vertex *next;
};

struct vertices_array
{
    bool visited;
    struct vertex *neighbours;
};

typedef void (*algorithm_pointer)(struct vertices_array *, int);

struct vertices_array *convert(const matrix adjacency_matrix)
{
    struct vertices_array *list = NULL;
    list = (struct vertices_array *)calloc(NUMBER_OF_VERTICES, sizeof(struct vertices_array));
    if (list)
    {
        for (int i = 0; i < NUMBER_OF_VERTICES; i++)
        {
            struct vertex **new_vertex = &list[i].neighbours;
            for (int j = 0; j < NUMBER_OF_VERTICES; j++)
            {
                if (adjacency_matrix[i][j])
                {
                    struct vertex *new_node = (struct vertex *)malloc(sizeof(struct vertex));
                    if (new_node)
                    {
                        new_node->vertex_number = j;
                        new_node->next = NULL;
                        *new_vertex = new_node;
                        new_vertex = &(*new_vertex)->next;
                    }
                    else
                        fprintf(stderr, "Wyjatek przy, tworzeniu wierzcholka %d.\n", j);
                }
            }
        }
    }
    return list;
}

void print_adjacency_list(struct vertices_array *adjacency_list)
{
    for (int i = 0; i < NUMBER_OF_VERTICES; i++)
    {
        printf("Wierzcholek %d ma sasiadow: ", i);
        struct vertex *neighbour = adjacency_list[i].neighbours;
        while (neighbour)
        {
            printf("%3d", neighbour->vertex_number);
            neighbour = neighbour->next;
        }
        puts("");
    }
}

void dfs(struct vertices_array *adjacency_list, int vertex_number)
{
    printf("%3d", vertex_number);
    struct vertex *neighbour = adjacency_list[vertex_number].neighbours;
    adjacency_list[vertex_number].visited = true;
    while (neighbour)
    {
        if (!adjacency_list[neighbour->vertex_number].visited)
            dfs(adjacency_list, neighbour->vertex_number);
        neighbour = neighbour->next;
    }
}

void bfs(struct vertices_array *adjacency_list, int vertex_number)
{
    struct fifo_pointers queue;
    queue.head = queue.tail = NULL;
    enqueue(&queue, vertex_number);
    while (queue.head)
    {
        vertex_number = dequeue(&queue);
        if (!adjacency_list[vertex_number].visited)
        {
            struct vertex *neighbour = adjacency_list[vertex_number].neighbours;
            while (neighbour)
            {
                enqueue(&queue, neighbour->vertex_number);
                neighbour = neighbour->next;
            }
            printf("%3d", vertex_number);
            adjacency_list[vertex_number].visited = true;
        }
    }
}

void explore_all_vertices(struct vertices_array *adjacency_list, int start_vertex, algorithm_pointer algorithm)
{
    if (start_vertex >= 0 && start_vertex < NUMBER_OF_VERTICES)
    {
        algorithm(adjacency_list, start_vertex);
        for (int i = 0; i < NUMBER_OF_VERTICES; i++)
            if (!adjacency_list[i].visited)
                algorithm(adjacency_list, i);
    }
    else
        puts("Zly numer wierzcholka poczatkowego.");
}

struct vertices_array *remove_adjacency_list(struct vertices_array *adjacency_list)
{
    for (int i = 0; i < NUMBER_OF_VERTICES; i++)
    {
        struct vertex *neighbour = adjacency_list[i].neighbours;
        while (neighbour)
        {
            struct vertex *temporary = neighbour->next;
            free(neighbour);
            neighbour = temporary;
        }
    }
    free(adjacency_list);
    return NULL;
}

int main(void)
{
    const matrix adjacency_matrix = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 0}};

    struct vertices_array *adjacency_list = convert(adjacency_matrix);
    if (adjacency_list)
    {
        print_adjacency_list(adjacency_list);
        puts("Prosze wskazac wierzcholek poczatkowy:");

        int start_vertex;
        scanf("%d", &start_vertex);
        printf("Wynik algorytmu DFS: ");
        explore_all_vertices(adjacency_list, start_vertex, dfs);
        puts("");
        for (int i = 0; i < NUMBER_OF_VERTICES; i++)
            adjacency_list[i].visited = false;
        printf("Wynik algorytmu BFS: ");
        explore_all_vertices(adjacency_list, start_vertex, bfs);
        puts("");
        adjacency_list = remove_adjacency_list(adjacency_list);
    }
    return 0;
}
