#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList *ListCreate() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void ListAdd(LinkedList *list, void *item) {
    Node *currentNode = list->head;
    Node *previousNode = NULL;
    while (currentNode != NULL) {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    currentNode = (Node*)malloc(sizeof(Node));
    currentNode->data = item;
    currentNode->next = NULL;
    if (previousNode == NULL) {
        list->head = currentNode;
    }
    else {
        previousNode->next = currentNode;
    }
    list->size++;
}

size_t ListSize(LinkedList *list) {
    return list->size;
}

bool ListIsEmpty(LinkedList *list) {
    return list->size == 0;
}

void ListRemove(LinkedList *list, size_t index) {
    Node *currentNode = list->head;
    Node *previousNode = NULL;
    for (size_t i = 0; i < index; i++) {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    if (previousNode == NULL) {
        list->head = currentNode->next;
        free(currentNode);
        return;
    }
    previousNode->next = currentNode->next;
    free(currentNode);   
    list->size--;
}

void ListIter(LinkedList *list, func_entry_list_t visit_entry) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        visit_entry((void*)currentNode->data);
        currentNode = currentNode->next;
    }   
}