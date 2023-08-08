#include <ctype.h>
#include <stdbool.h>

typedef struct _node {
    void *data;
    struct _node *next;
} Node;

typedef struct _linked_list {
    Node *head;
    size_t size;
} LinkedList;

typedef void (*func_entry_list_t) (void *elem);

LinkedList *ListCreate();
void ListAdd(LinkedList *list, void *item);
size_t ListSize(LinkedList *list);
bool ListIsEmpty(LinkedList *list);
void ListRemove(LinkedList *list, size_t index);
void ListIter(LinkedList *list, func_entry_list_t visit_entry);