#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    void *data;
    struct Node *next;
};

struct LinkedList {
    Node *head;
    size_t size;
    bool (*cmp_function) (void *elem1, void *elem2);
};

LinkedList *ListCreate(FuncCmpList cmp_function) {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    list->cmp_function = cmp_function;
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

void *ListGet(LinkedList *list, size_t index) {
    Node *currentNode = list->head;
    for (size_t i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode->data;
}

size_t ListSize(LinkedList *list) {
    return list->size;
}

bool ListContains(LinkedList *list, void *elem, FuncCmpList cmp_function) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        if (currentNode->data == elem || (cmp_function && cmp_function(currentNode->data, elem))) return true;
        currentNode = currentNode->next;
    }
    return false;
}

bool ListIsEmpty(LinkedList *list) {
    return list->size == 0;
}

void ListRemove(LinkedList *list, size_t index, FuncEntryList release_func) {
    Node *currentNode = list->head;
    Node *previousNode = NULL;
    for (size_t i = 0; i < index; i++) {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    if (previousNode == NULL) {
        list->head = currentNode->next;
    }
    else {
        previousNode->next = currentNode->next;
    }
    release_func(currentNode->data);
    free(currentNode);   
    list->size--;
}

void ListIter(LinkedList *list, FuncEntryList visit_entry) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        visit_entry((void*)currentNode->data);
        currentNode = currentNode->next;
    }   
}