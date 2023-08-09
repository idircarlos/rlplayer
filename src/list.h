#pragma once

#include <ctype.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct LinkedList LinkedList;

typedef void (*FuncEntryList) (void *elem);
typedef bool (*FuncCmpList) (void *elem1, void *elem2);

LinkedList *ListCreate();
void ListAdd(LinkedList *list, void *item);
void *ListGet(LinkedList *list, size_t index);
size_t ListSize(LinkedList *list);
bool ListContains(LinkedList *list, void *elem, FuncCmpList cmp_function);
bool ListIsEmpty(LinkedList *list);
void ListRemove(LinkedList *list, size_t index, FuncEntryList release_function);
void ListIter(LinkedList *list, FuncEntryList visit_entry);
void ListDestroy(LinkedList *list, FuncEntryList release_function);