#include "gui.h"
#include "utils.h"
#include "render.h"
#include "audio.h"

#define RAYGUI_IMPLEMENTATION   // If need raygui.h in more files, move this definition to main.c
#include <raygui.h>


void HandleDragAndDrop();
void DrawGUIComponents();
void DrawGUIText();

static GuiIconName currentPlayIcon = ICON_PLAYER_PAUSE;
static Song currentSong = {0};
static Rectangle slider = {50, SCREEN_HEIGHT - 100, SCREEN_WIDTH - 100, 20};

void InitGUI() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
    InitAudioDevice();
    InitPlaylist();
    SetTargetFPS(60);
}

void UpdateGUI() {
    currentSong = GetCurrentSong();
    BeginDrawing();
        ClearBackground(BG_COLOR);
        DrawGUIComponents();
        DrawGUIText();
    EndDrawing();
    HandleDragAndDrop();
    UpdatePlaylist();
}

void HandleDragAndDrop() {
    if (IsFileDropped()) {
        FilePathList files_path = LoadDroppedFiles();
        for (int i = 0; i < files_path.count; i++) {
            char *file = files_path.paths[i];
            AddSong(file);
        }
        UnloadDroppedFiles(files_path);
        if (!IsPlayingPlaylist()) {
            StartPlaying();
        }
    }
}

void DrawGUIComponents() {
    float total = currentSong.length;
    float elapsed = GetMusicTimePlayed(currentSong.music);
    //GuiProgressBar((Rectangle){50, SCREEN_HEIGHT - 100, SCREEN_WIDTH - 100, 20}, FormatTime(elapsed), FormatTime(total), (elapsed / total) * 100, 0, 100);
    float selected = GuiSliderBar(slider, FormatTime(elapsed), FormatTime(total), (elapsed / total) * 100, 0, 100);
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, slider)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            SetTimeSong(selected);
        }
    }
    if (GuiButton((Rectangle){SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT - 50 - 15, 30, 30}, GuiIconText(ICON_PLAYER_PREVIOUS, ""))) PrevSong();
    if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 15, SCREEN_HEIGHT - 50 - 15, 30, 30}, GuiIconText(currentPlayIcon, ""))) {
        if (IsPlayingPlaylist()) {
            TogglePause();
            currentPlayIcon = currentPlayIcon == ICON_PLAYER_PAUSE ? ICON_PLAYER_PLAY : ICON_PLAYER_PAUSE;
        }
    }
    if(GuiButton((Rectangle){SCREEN_WIDTH/2 + 30, SCREEN_HEIGHT - 50 - 15, 30, 30}, GuiIconText(ICON_PLAYER_NEXT, ""))) NextSong();
}

void DrawGUIText() {
    if (IsPlayingPlaylist() && GetPlaylistSize() > 0) {
        DrawText("Playlist", 20, 20, 30, WHITE);
        DrawLineEx((Vector2){20,55}, (Vector2){200,55}, 5, WHITE);
        int y = 60;
        Song currentSong = GetCurrentSong();
        for (size_t i = 0; i < GetPlaylistSize(); i++) {
            Song song = GetSongFromPlaylist(i);
            char *songName = song.name;
            if (!memcmp(&song, &currentSong, sizeof(Song))) {
                DrawText(songName, 50, y, 20, BLUE);
            }
            else {
                DrawText(songName, 50, y, 20, WHITE);
            }
            GuiButton((Rectangle){20, y, 20, 20}, GuiIconText(ICON_CROSS, ""));
            y += 30;
        }
        DrawTextCentered(currentSong.name, 40, WHITE);
    }
    else {
        DrawTextCentered("Drag & Drop your music!", 40, WHITE);
    }
}