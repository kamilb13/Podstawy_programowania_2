#include"queue.h"
#include<stdlib.h>

void enqueue(struct fifo_pointers *queue, int vertex_number)
{
    struct fifo_node *new_node = (struct fifo_node *)malloc(sizeof(struct fifo_node));

    if(new_node){
        new_node->vertex_number = vertex_number;
        new_node->next = NULL;
        if(queue->head==NULL && queue->tail==NULL)
        queue->head = queue->tail = new_node;
        else {
            queue->tail->next = new_node;
            queue->tail = new_node;
        }
    }
}

int dequeue(struct fifo_pointers *queue)
{
    int vertex_number = -1;
    if(queue->head) {
        vertex_number = queue->head->vertex_number;
        struct fifo_node *temporary = queue->head->next;
        free(queue->head);
        queue->head = temporary;
        if(temporary==NULL)
        queue->tail = NULL;
    }
    return vertex_number;
}
