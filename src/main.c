#include "gui.h"
#include "list.h"
#include <stdio.h>
#include <string.h>

void printInt(void *e) {
    char *a = (char*)(e);
    printf("%s\n", a);
}

int main() {
    InitGUI();
    while (!WindowShouldClose()){
        UpdateGUI();
    }
    CloseWindow();
    return 0;
}

