#include "gui.h"
#include "utils.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION   // If need raygui.h in more files, move this definition to main.c
#include <raygui.h>

static Music currentMusic = {0};

void InitGUI() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
    InitAudioDevice();
    SetTargetFPS(60);
}

void UpdateGUI() {
    BeginDrawing();
    ClearBackground(BG_COLOR);
    float total = GetMusicTimeLength(currentMusic);
    float elapsed = GetMusicTimePlayed(currentMusic);
    GuiProgressBar((Rectangle){50, SCREEN_HEIGHT - 100, SCREEN_WIDTH - 100, 20}, FormatTime(elapsed), FormatTime(total), (elapsed / total) * 100, 0, 100);
    GuiButton((Rectangle){SCREEN_WIDTH/2 - 15, SCREEN_HEIGHT - 50 - 15, 30, 30}, GuiIconText(ICON_ARROW_RIGHT_FILL, ""));
    DrawTextCentered("Drag & Drop your music!", 40, WHITE);
    if (IsFileDropped()) {
        FilePathList files_path = LoadDroppedFiles();
        for (int i = 0; i < files_path.count; i++) {
            char *file = files_path.paths[i];
            currentMusic = LoadMusicStream(file);
            PlayMusicStream(currentMusic);
        }
        UnloadDroppedFiles(files_path);
    }
    if (IsMusicStreamPlaying(currentMusic)) {
        UpdateMusicStream(currentMusic);
    }
    EndDrawing();
}