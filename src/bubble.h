#pragma once
#include <raylib.h>

typedef struct _bubble {
    Vector2 pos;
    float size;
    bool aumenting;
} Bubble;

static Bubble *bubbles[3] = {0};
static bool paused = false;

void InitBubbles() {
    bubbles[0] = malloc(sizeof(Bubble));
    bubbles[1] = malloc(sizeof(Bubble));
    bubbles[2] = malloc(sizeof(Bubble));
    
    bubbles[0]->pos  = (Vector2){300,300};
    bubbles[0]->size = 6;
    bubbles[0]->aumenting = true;

    bubbles[1]->pos  = (Vector2){315,300};
    bubbles[1]->size = 3;
    bubbles[1]->aumenting = true;

    bubbles[2]->pos  = (Vector2){330,300};
    bubbles[2]->size = 1;
    bubbles[2]->aumenting = true;
}

void DrawBubbles(Vector2 pos, Color color) {
    Bubble *bubble;
    off_t offsetx = 0;
    for (int i = 0; i < 3; i++) {
        bubble = bubbles[i];
        DrawCircle(pos.x + offsetx, pos.y, (int)bubble->size, color);
        offsetx += 15;
    }
}

void UpdateBubbles() {
    if (paused) return;
    Bubble *bubble;
    for (int i = 0; i < 3; i++) {
        bubble = bubbles[i];
        if (bubble->aumenting) bubble->size += 0.4;
        else bubble->size -= 0.4;
        if (bubble->size >= 6) bubble->aumenting = false;
        else if (bubble->size <= 1) bubble->aumenting = true;
    }
}

void TogglePauseBubbles() {
    paused = paused ? false : true;
}