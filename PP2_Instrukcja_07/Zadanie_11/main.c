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

struct vertex
{
    int vertex_number;
    struct vertex *next;
};

struct vertices_array
{
    struct vertex *neighbours;
};

typedef void (*algorithm_pointer)(struct vertices_array *, int, bool *);

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

void dfs(struct vertices_array *adjacency_list, int vertex_number, bool *visited)
{
    printf("%3d", vertex_number);
    struct vertex *neighbour = adjacency_list[vertex_number].neighbours;
    while (neighbour)
    {
        if (!visited[neighbour->vertex_number])
        {
            visited[neighbour->vertex_number] = true;
            dfs(adjacency_list, neighbour->vertex_number, visited);
        }
        neighbour = neighbour->next;
    }
}

void bfs(struct vertices_array *adjacency_list, int vertex_number, bool *visited)
{
    struct fifo_pointers queue;
    queue.head = queue.tail = NULL;
    enqueue(&queue, vertex_number);
    while (queue.head)
    {
        vertex_number = dequeue(&queue);
        if (!visited[vertex_number])
        {
            printf("%3d", vertex_number);
            struct vertex *neighbour = adjacency_list[vertex_number].neighbours;
            while (neighbour)
            {
                enqueue(&queue, neighbour->vertex_number);
                visited[neighbour->vertex_number] = true;
                neighbour = neighbour->next;
            }
        }
    }
}

void explore_all_vertices(struct vertices_array *adjacency_list, int start_vertex, algorithm_pointer algorithm)
{
    if (start_vertex >= 0 && start_vertex < NUMBER_OF_VERTICES)
    {
        bool *visited = (bool *)calloc(NUMBER_OF_VERTICES, sizeof(bool));
        if (visited)
        {
            algorithm(adjacency_list, start_vertex, visited);
            for (int i = 0; i < NUMBER_OF_VERTICES; i++)
            {
                if (!visited[i])
                    algorithm(adjacency_list, i, visited);
            }
            free(visited);
        }
        else
            puts("B³¹d przy alokacji pamiêci.");
    }
    else
        puts("Z³y numer wierzcho³ka pocz¹tkowego.");
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
    struct vertices_array *adjacency_list = convert(adjacency_matrix);
    if (adjacency_list)
    {
        print_adjacency_list(adjacency_list);
        puts("Proszê wskazaæ wierzcho³ek pocz¹tkowy:");

        int start_vertex;
        scanf("%d", &start_vertex);
        printf("Wynik algorytmu DFS: ");
        explore_all_vertices(adjacency_list, start_vertex, dfs);
        puts("");
        printf("Wynik algorytmu BFS: ");
        explore_all_vertices(adjacency_list, start_vertex, bfs);
        puts("");
        adjacency_list = remove_adjacency_list(adjacency_list);
    }
    return 0;
}
