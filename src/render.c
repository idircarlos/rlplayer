#include "render.h"

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   800

void DrawTextCentered(char *text, int fontSize, Color color) {
    int size = MeasureText(text, fontSize);
    DrawText(text, (SCREEN_WIDTH/2) - (size/2), SCREEN_HEIGHT/2, 40, RAYWHITE);
}