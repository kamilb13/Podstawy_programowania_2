# include <stdio.h>
# include <stdlib.h>
#include <stdbool.h>
struct sll_node
{
    int data ;
    struct sll_node * next ;
};

struct sll_node * create_list ( int data )
{
    struct sll_node * front = ( struct sll_node *)
    malloc ( sizeof ( struct sll_node ) ) ;
    if ( NULL != front )
    {
        front -> data = data ;
        front -> next = NULL ;
    }
    return front ;
}

struct sll_node * insert_front ( struct sll_node *front, struct sll_node * new_node )
{
    new_node -> next = front ;
    return new_node;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool sprawdz_warunek( struct sll_node *front , int data ){
    //puts("funkcja zadzialala");

    if(( NULL != front ) && ((front -> data != data ) || (front -> data > data )))
        return true;
    return false;
}

struct sll_node * find_spot ( struct sll_node *front , int data, bool (*f)())
{
    struct sll_node * prev = NULL;
    //while (( NULL != front ) && (front -> data > data ) )
    while( sprawdz_warunek(front, data) )
    {
        prev = front;
        front = front -> next;
    }
    return prev ;
}

struct sll_node * find_prev_node ( struct sll_node *front , int data )
{
    struct sll_node * prev = NULL ;
    while (( NULL != front ) && (front -> data != data ) )
    {
        prev = front ;
        front = front -> next ;
    }
    return prev ;
}


void insert_after ( struct sll_node *node , struct sll_node * new_node )
{
    new_node -> next = node -> next ;
    node -> next = new_node ;
}

void insert_back ( struct sll_node *back , struct sll_node * new_node )
{
    back -> next = new_node ;
}

struct sll_node * insert_node ( struct sll_node *front , int data )
{
    if ( NULL == front )
    return NULL ;

    struct sll_node * new_node = ( struct sll_node *)
    malloc ( sizeof ( struct sll_node ) ) ;
    if ( NULL != new_node )
    {
        new_node -> data = data ;
        new_node -> next = NULL ;
        if (front -> data <= data )
            return insert_front (front , new_node ) ;
        else
        {
            struct sll_node * node = find_spot(front , data , &sprawdz_warunek) ;
            if ( NULL != node -> next )
            insert_after (node , new_node ) ;
            else
            insert_back (node , new_node ) ;
        }
    }
    return front ;
}

struct sll_node * delete_front ( struct sll_node * front )
{
    struct sll_node * next = front -> next ;
    free ( front ) ;
    return next ;
}



void delete_after ( struct sll_node * node )
{

struct sll_node * next = node -> next ;
    if ( NULL != next )
    {
    node -> next = next -> next ;
     free ( next ) ;
     }
 }

 struct sll_node * delete_node ( struct sll_node *front , int data )
 {
     if ( NULL == front )
     return NULL ;

     if (front -> data == data )
     return delete_front ( front ) ;

     struct sll_node * prev = find_prev_node (front , data ) ;
     delete_after ( prev ) ;
     return front ;
 }

 void print_list ( struct sll_node * front )
 {
     for (; NULL != front ; front = front -> next )
        printf ("%d ", front -> data ) ;
     printf ("\n") ;
 }

 void remove_list ( struct sll_node ** front )
 {
     while ( NULL != * front )
     {
         struct sll_node * next = (* front ) ->next ;
         free (* front ) ;
         * front = next ;
     }
 }

 int main ()
 {
     struct sll_node * front = create_list (1) ;
     int i;

     for (i=2; i <10; i++)
        front = insert_node (front , i) ;
     printf (" List elements :\n") ;
     print_list ( front ) ;

     front = insert_node (front , 0) ;
     printf (" List elements after insertion of 0:\n") ;
     print_list ( front ) ;
     front = insert_node (front , 5) ;
     printf (" List elements after insertion of 5:\n") ;
     print_list ( front ) ;
     front = insert_node (front , 10) ;
     printf (" List elements after insertion of 10:\n") ;
     print_list ( front ) ;


     front = delete_node (front , 0) ;
     printf (" List elements after deletion of 0:\n") ;
     print_list ( front ) ;
     front = delete_node (front , 1) ;
     printf (" List elements after deletion of 1:\n") ;
     print_list ( front ) ;
     front = delete_node (front , 1) ;
     printf (" List elements after deletion of 1:\n") ;
     print_list ( front ) ;
     front = delete_node (front , 5) ;
     printf (" List elements after deletion of 5:\n") ;
     print_list ( front ) ;
     front = delete_node (front , 10) ;
     printf (" List elements after deletion of 10:\n") ;
     print_list ( front ) ;

     remove_list (& front ) ;
     return 0;
 }
