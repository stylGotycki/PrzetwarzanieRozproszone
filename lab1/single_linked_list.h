#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0


// Single linked list.
typedef struct list_t {
    int value;
    struct list_t *next;
} list_t;


void list_init(list_t *head);


// Appends single item at the end of the list.
void list_append(list_t* list, int value);


// Inserts single item after the certain position.
// Returns 0 on failure. 
int list_insert_after(list_t* list, int value, int index);


// Inserts single item before the certain position.
// Returns 0 on failure. 
int list_insert_before(list_t *list, int value, int index);


// Shifts single element at the front of the list.
void list_shift(list_t* list, int value);


// Removes last item from the list.
void list_delete_last(list_t *list);


// Removes first item from the list.
void list_delete_first(list_t *list);


// Removes single item at the certain position.
// Returns 0 on failure.
int list_remove(list_t *list, int index);


// Frees entire list.
void list_free(list_t *list);


// Counts all list's items.
int list_count(list_t *list);


// Converts array to list.
list_t* array_to_list(int *arr, int length);


// Converts list to array.
int* list_to_array(list_t *list);

#endif //SINGLE_LINKED_LIST_H