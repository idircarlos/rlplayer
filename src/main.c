#include "gui.h"
#include "list.h"
#include <stdio.h>
#include <string.h>

int main() {
    InitGUI();
    while (!WindowShouldClose()){
        UpdateGUI();
    }
    CloseWindow();
    return 0;
}

