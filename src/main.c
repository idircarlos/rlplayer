#include "gui.h"
#include "list.h"
#include <stdio.h>

void printInt(void *e) {
    char *a = (char*)(e);
    printf("%s\n", a);
}

int main() {
    InitGUI();
    LinkedList *list = ListCreate();
    char *a = "hola";
    char *b = "que";
    char *c = "tal";
    ListAdd(list, (void*)a);
    ListAdd(list, (void*)b);
    ListAdd(list, (void*)c);
    ListRemove(list, 0);
    ListIter(list, printInt);
    while (!WindowShouldClose()){
        UpdateGUI();
    }
    CloseWindow();
    return 0;
}

