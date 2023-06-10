# include <stdio.h>
# include <stdlib.h>

struct dll_node
{
    int data ;
    struct dll_node *prev, * next;
};

 struct dll_node * create_list ( int data )
 {
     struct dll_node * front = ( struct dll_node *)malloc ( sizeof ( struct dll_node ) ) ;
     if ( NULL != front )
     {
         front -> data = data ;
         front -> prev = front -> next = NULL ;
     }
     return front ;
 }

 struct dll_node * insert_front ( struct dll_node *front, struct dll_node * new_node )
 {
     new_node -> next = front ;
     front -> prev = new_node ;
     return new_node ;
 }

 struct dll_node * find_spot ( struct dll_node *front , int data )
 {
     struct dll_node * prev = NULL ;
     while (( NULL != front ) && (front -> data > data ) )
     {
        prev = front ;
        front = front -> next ;
     }

     return prev ;
 }

 void insert_after ( struct dll_node *node , struct dll_node * new_node )
 {
     new_node -> prev = node ;
     new_node -> next = node -> next ;
     node ->next -> prev = new_node ;
     node -> next = new_node ;
 }

 void insert_back ( struct dll_node *back , struct dll_node * new_node )
 {
     back -> next = new_node ;
     new_node -> prev = back ;
 }

 struct dll_node * insert_node ( struct dll_node *front , int data )
 {
     if ( NULL == front )
        return NULL ;

     struct dll_node * new_node = ( struct dll_node *)
     malloc ( sizeof ( struct dll_node ) ) ;
     if ( NULL != new_node )
     {
         new_node -> data = data ;
         new_node -> prev = new_node -> next = NULL ;
         if (front -> data <= data )
            return insert_front (front , new_node ) ;
         else
         {
             struct dll_node * node = find_spot (front , data ) ;
             if ( NULL != node -> next )
                insert_after (node , new_node ) ;
             else
                insert_back (node , new_node ) ;
         }
     }
     return front ;
 }

 struct dll_node * delete_front ( struct dll_node * front )
 {
     struct dll_node * next = front -> next ;
     if ( NULL != next )
        next -> prev = NULL ;
     free ( front ) ;
     return next ;
 }

 struct dll_node * find_node ( struct dll_node *front , int data )
 {
     while (( NULL != front ) && (front -> data != data ) )
        front = front -> next ;
     return front ;
 }


 void delete_within ( struct dll_node * node )
 {
    node ->next -> prev = node -> prev ;
    node ->prev -> next = node -> next ;
    free ( node ) ;
 }

 void delete_back ( struct dll_node * back )
 {
     back ->prev -> next = NULL ;
     free ( back ) ;
 }

 struct dll_node * delete_node ( struct dll_node *front , int data )
 {
     if ( NULL == front )
        return NULL ;

     if (front -> data == data )
        return delete_front ( front ) ;

     struct dll_node * node = find_node (front , data ) ;
         if ( NULL != node )
         {
             if ( NULL != node -> next )
                delete_within ( node ) ;
             else
             delete_back ( node ) ;
         }
    return front ;
 }

 void print_list ( struct dll_node * front )
 {
     for (; NULL != front ; front = front -> next )
        printf ("%d ", front -> data ) ;
     printf ("\n") ;
 }

 void print_list_backwards ( struct dll_node * front )
 {
     if ( NULL != front )
     {
         for (; NULL != front -> next ; front = front -> next ) ;
         for (; NULL != front ; front = front -> prev )
         printf ("%d ", front -> data ) ;
     }
     printf ("\n") ;
 }

 void remove_list ( struct dll_node ** front )
 {
     while ( NULL != * front )
     {
         struct dll_node * next = (* front ) ->next ;
         free (* front ) ;
         * front = next ;
     }

 }

 int main ()
 {
     struct dll_node * front = create_list (1) ;
     int i;

     for (i=2; i <20; i++)
        front = insert_node (front , i) ;
     printf (" List elements :\n") ;
     print_list ( front ) ;
     printf (" List elements printed backwards :\n") ;
     print_list_backwards ( front ) ;

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
