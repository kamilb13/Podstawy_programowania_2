#ifndef GRAPHS_QUEUE_H
#define GRAPHS_QUEUE_H

struct fifo_node {
    int vertex_number;
    struct fifo_node *next;
};

struct fifo_pointers
{
    struct fifo_node *head, *tail;
};

void enqueue(struct fifo_pointers *, int);
int dequeue(struct fifo_pointers*);

#endif
