#include "gui.h"
#include "list.h"
#include <stdio.h>
#include <string.h>

int main() {

    LinkedList *list = ListCreate();
    // int a = 1;
    // int b = 2;
    // int c = 3;
    // int d = 4;
    // int e = 5;
    
    // ListAdd(list, &a);
    // ListAdd(list, &b);
    // ListAdd(list, &c);
    // ListAdd(list, &d);
    // ListAdd(list, &e);
    // ListPrint(list);
    // printf("\n\n");

    // ListSwap(list, 1, 3);
    // ListPrint(list);

    InitGUI();
    while (!WindowShouldClose()){
        UpdateGUI();
    }
    CloseWindow();
    return 0;
}

