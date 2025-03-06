#include "single_linked_list.h"

void list_init(list_t *head) {
    head->next = NULL;
}

void list_append(list_t *list, int value) {
    list_t *new_el = (list_t*)malloc(sizeof(list_t));
    list_t *last = list;

    while(last->next != NULL) 
        last = last->next;
    
    last->next = new_el;
    
    new_el->next = NULL;
    new_el->value = value;
}


int list_insert_before(list_t *list, int value, int index) {
    int c = list_count(list);

    if (c <= index) return FAILURE;     // "<" also works, which is strange
                                        // but I decided that inserting at index out of 
                                        // "defined range" (e.g. for 5 element the indeces are [0-4])
                                        // is dumb
    
    list_t *temp = list;

    for (int i = 0; i < index-1; i++)
        temp = temp->next;

    list_t *new_el = (list_t*)malloc(sizeof(list_t));

    new_el->value = value;
    new_el->next = temp->next;

    temp->next = new_el;

    return SUCCESS;
}


int list_insert_after(list_t *list, int value, int index) {
    int c = list_count(list);

    if (c <= index) return FAILURE;     // "<" also works, which is strange
                                        // but I decided that inserting at index out of 
                                        // "defined range" (e.g. for 5 element the indeces are [0-4])
                                        // is dumb
    
    list_t *temp = list;

    for (int i = 0; i < index; i++)
        temp = temp->next;

    list_t *new_el = (list_t*)malloc(sizeof(list_t));

    new_el->value = value;
    new_el->next = temp->next;

    temp->next = new_el;

    return SUCCESS;
}


void list_shift(list_t *list, int value) {
    list_t *new_el = (list_t*)malloc(sizeof(list_t));

    new_el->value = value;

    if (list->next == NULL) {
        list->next = new_el;
        new_el->next = NULL;
    }
    else {
        new_el->next = list->next;
        list->next = new_el;
    }

    list = new_el;
}


void list_delete_last(list_t *list) {
    if (list->next == NULL)
        return;

    list_t *last = list;

    while(last->next->next != NULL) 
        last = last->next;

    last->next = NULL;
    free(last->next);
}


void list_delete_first(list_t *list) {
    if(list->next == NULL && list->next->next == NULL)
        return;

    list_t* first = list->next;

    list->next = first->next;
    free(first);
}


int list_remove(list_t *list, int index) {
    int c = list_count(list);

    if (c <= index) return FAILURE;
    
    list_t *temp = list;
    list_t *to_rm;

    for (int i = 0; i < index-1; i++) 
        temp = temp->next;

    to_rm = temp->next;
    
    temp->next = to_rm->next;

    // to_rm->next = NULL;
    free(to_rm);

    return SUCCESS;
}


void list_free(list_t *list) {
    while(list->next != NULL) list_delete_last(list);
}


int list_count(list_t *list) {
    int c = 0;
    list_t *temp = list;
    while (temp->next != NULL) {
        temp = temp->next;
        c++;
    }
    return c;
}


list_t *array_to_list(int *arr, int length) {
    if (!length) return NULL;
    
    list_t *head = (list_t*)malloc(sizeof(list_t));
    list_init(head);

    for (int i = 0; i < length; i++) 
        list_append(head, arr[i]);
    
    return head;
}


int *list_to_array(list_t *list) {
    int n = list_count(list);
    int *arr = (int*)malloc(n * sizeof(int));
    int i = 0;
    
    list_t *temp = list;
    
    while(temp->next != NULL) {
        temp = temp->next;
        arr[i++] = temp->value;
    }
    
    return arr;
}
