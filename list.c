#include<stdlib.h>
#include "list.h"


node *create_node(char *name){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->name = name;
    new_node->next = NULL;
    return new_node;
}


void add(node **head, char*name){
    node *new_node = create_node(name);
    new_node->next = *head;
    *head = new_node;
}

void delete(node *head){
    node * temp = head;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Successfuly freed memory\n");
}