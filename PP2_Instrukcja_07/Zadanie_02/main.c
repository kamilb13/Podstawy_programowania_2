#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

typedef int **matrix;

struct vertex
{
    int vertex_number;
    struct vertex *next;
};

struct vertices_array
{
    bool visited;
    struct vertex *neighbours;
} *adjacency_list;

typedef void (*algorithm_pointer)(struct vertices_array *, int);

struct vertices_array *convert(const matrix adjacency_matrix, int number_of_vertices)
{
    struct vertices_array *list = NULL;
    list = (struct vertices_array *)calloc(number_of_vertices, sizeof(struct vertices_array));
    if (list)
    {
        for (int i = 0; i < number_of_vertices; i++)
        {
            struct vertex **new_vertex = &list[i].neighbours;
            for (int j = 0; j < number_of_vertices; j++)
            {
                if (adjacency_matrix[i][j])
                {
                    *new_vertex = (struct vertex *)malloc(sizeof(struct vertex));
                    if (*new_vertex)
                    {
                        (*new_vertex)->vertex_number = j;
                        (*new_vertex)->next = NULL;
                        new_vertex = &(*new_vertex)->next;
                    }
                    else
                        fprintf(stderr, "Wyjatek przy tworzeniu wierzcholka %d.\n", j);
                }
            }
        }
    }
    return list;
}

void print_adjacency_list(struct vertices_array *adjacency_list, int number_of_vertices)
{
    for (int i = 0; i < number_of_vertices; i++)
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

void explore_all_vertices(struct vertices_array *adjacency_list, int start_vertex, algorithm_pointer algorithm, int number_of_vertices)
{
    if (start_vertex >= 0 && start_vertex < number_of_vertices)
    {
        algorithm(adjacency_list, start_vertex);
        for (int i = 0; i < number_of_vertices; i++)
            if (!adjacency_list[i].visited)
                algorithm(adjacency_list, i);
    }
    else
        puts("Zly numer wierzcholka poczatkowego.");
}

struct vertices_array *remove_adjacency_list(struct vertices_array *adjacency_list, int number_of_vertices)
{
    for (int i = 0; i < number_of_vertices; i++)
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
    int number_of_vertices;
    printf("Podaj liczbe wierzcholkow: ");
    scanf("%d", &number_of_vertices);

    matrix adjacency_matrix = (matrix)malloc(number_of_vertices * sizeof(int *));
    for (int i = 0; i < number_of_vertices; i++)
        adjacency_matrix[i] = (int *)malloc(number_of_vertices * sizeof(int));

    printf("Wprowadz macierz sasiedztwa %dx%d:\n", number_of_vertices, number_of_vertices);
    for (int i = 0; i < number_of_vertices; i++)
    {
        for (int j = 0; j < number_of_vertices; j++)
        {
            printf("podaj [%d] [%d] ", i, j);
            scanf("%d", &adjacency_matrix[i][j]);
        }
    }

    adjacency_list = convert(adjacency_matrix, number_of_vertices);
    if (adjacency_list)
    {
        print_adjacency_list(adjacency_list, number_of_vertices);
        puts("Prosze wskazac wierzcholek poczatkowy:");

        int start_vertex;
        scanf("%d", &start_vertex);
        printf("Wynik algorytmu DFS: ");
        explore_all_vertices(adjacency_list, start_vertex, dfs, number_of_vertices);
        puts("");
        for (int i = 0; i < number_of_vertices; i++)
            adjacency_list[i].visited = false;
        printf("Wynik algorytmu BFS: ");
        explore_all_vertices(adjacency_list, start_vertex, bfs, number_of_vertices);
        puts("");
        adjacency_list = remove_adjacency_list(adjacency_list, number_of_vertices);
    }

    for (int i = 0; i < number_of_vertices; i++)
        free(adjacency_matrix[i]);
    free(adjacency_matrix);

    return 0;
}
