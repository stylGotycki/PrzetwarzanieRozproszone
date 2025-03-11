// Filip Domaszk 197624 [7B] lab2
#include <stdio.h>
#include <stdlib.h>
#include "single_linked_list.h"


void print_list(list_t *list) {
    list_t *temp = list;
 
    while(temp->next != NULL) {
        temp = temp->next;
        printf("%d\t", temp->value);
    }
    printf("\n\n");
}


int main(int argc, char** argv) {
    int i = 10;
    list_t list;

    list_init(&list);
    
    while(i-->0)
        list_append(&list, i);        

    print_list(&list);   

    list_delete_first(&list);
    print_list(&list);
    list_delete_last(&list);
    print_list(&list);
    list_shift(&list, 1000);
    print_list(&list);
    list_insert_after(&list, 2000, 4);
    print_list(&list);
    list_insert_before(&list, 3000, 5);
    print_list(&list);
    
    int* array = list_to_array(&list);
    int size = list_count(&list);
    list_free(&list);

    for (int i = 0; i < size; i++) 
        printf("%d\t", array[i]);
    printf("\n\n");

    list_t* list2 = array_to_list(array, size);
    free(array);

    print_list(list2);
    list_free(list2);

    return 0;
}