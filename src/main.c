#include "gui.h"

int main() {
    InitGUI();
    while (!WindowShouldClose()){
        UpdateGUI();
    }
    CloseWindow();
    return 0;
}

