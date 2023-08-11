#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    void *data;
    struct Node *prev;
    struct Node *next;
};

struct LinkedList {
    Node *head;
    size_t size;
};

Node *ListGetNode(LinkedList *list, size_t index);
void NodePrint(Node *node);
void ListPrint(LinkedList *list);

Node *CreateNode(void *data, Node *prev, Node *next) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->prev = prev;
    node->next = next;
    return node;
}

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
    currentNode = CreateNode(item, NULL, NULL);

    if (previousNode == NULL) {
        list->head = currentNode;
    }
    else {
        currentNode->prev = previousNode;
        previousNode->next = currentNode;
    }
    list->size++;
}

Node *ListGetNode(LinkedList *list, size_t index) {
    Node *currentNode = list->head;
    for (size_t i = 0; i < index; i++) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

void *ListGet(LinkedList *list, size_t index) {
    Node *node = ListGetNode(list, index);
    if (!node) return NULL;
    return node->data;
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

void ListSwap(LinkedList *list, int index_i, int index_j) {
    if (index_i == index_j || index_i >= list->size || index_j >= list->size || index_i < 0 || index_j < 0) return;
    
    Node *node_i = ListGetNode(list, index_i);
    Node *node_j = ListGetNode(list, index_j);

    void *tmp = node_i->data;
    node_i->data = node_j->data;
    node_j->data = tmp;
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

void ListDestroy(LinkedList *list, FuncEntryList release_function) {
    for (size_t i = 0; i < ListSize(list); i++) {
        ListRemove(list, i, release_function);
    }
    free(list);
}

void NodePrint(Node *node) {
    printf("data = %d\n", *((int*)(node->data)));
    printf("this = %p\n", node);
    printf("prev = %p\n", node->prev);
    printf("next = %p\n", node->next);
    printf("\n");
}

void ListPrint(LinkedList *list) {
    Node *currentNode = list->head;
    while (currentNode != NULL) {
        NodePrint(currentNode);
        currentNode = currentNode->next;
    }
}