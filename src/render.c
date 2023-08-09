#include "render.h"

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800

void DrawTextCentered(char *text, int fontSize, Color color) {
    int size = MeasureText(text, fontSize);
    DrawText(text, (GetScreenWidth()/2) - (size/2), GetScreenHeight()/2, 40, RAYWHITE);
}