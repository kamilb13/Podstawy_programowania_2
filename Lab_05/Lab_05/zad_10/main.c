#include <stdio.h>
#include <stdlib.h>

struct dll_node{
    int data;
    struct dll_node *prev, *next;
};

struct dll_node *create_node(int data){
    struct dll_node *new_node = malloc(sizeof(struct dll_node));
    if (new_node == NULL){
        printf("Blad\n");
    }

    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}

struct dll_node *insert_node(struct dll_node *front, int data){
    if (front == NULL){
        return create_node(data);
    }

    if (front->data > data){
        struct dll_node *new_node = create_node(data);
        new_node->next = front;
        front->prev = new_node;
        return new_node;
    }

    front->next = insert_node(front->next, data);
    front->next->prev = front;
    return front;
}

void print_list(struct dll_node *front) {
    if (front == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }

    printf("List elements:\n");
    for (; front != NULL; front = front->next) {
        printf("%d ", front->data);
    }
    printf("\n");
}

void removeL(struct dll_node *front) {
    if (front == NULL){
        return;
    }

    removeL(front->next);
    free(front);
}

int main() {
    struct dll_node *front = NULL;
    for(int i=1; i<=10; i++)
        front = insert_node(front, i);
    print_list(front);

    removeL(front);
    front = NULL;

    return 0;
}
