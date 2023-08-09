#include "gui.h"
#include "utils.h"
#include "render.h"
#include "audio.h"

#define RAYGUI_IMPLEMENTATION   // If need raygui.h in more files, move this definition to main.c
#include <raygui.h>

#define BG_COLOR        GetColor(0x1A1A1AFF)
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   500
#define APP_NAME        "RLPlayer"
#define EMPTY_STRING    ""
#define VOLUME_STRING   "Vol  "

void HandleInput();
void HandleDragAndDrop();
void DrawGUIComponents();
void DrawGUIText();
void HandlePause();

static GuiIconName currentPlayIcon = ICON_PLAYER_PAUSE;
static Song currentSong = {0};
static Rectangle slider = {50, SCREEN_HEIGHT - 100, SCREEN_WIDTH - 100, 20};
static Rectangle volSlider = {650, SCREEN_HEIGHT - 60, 100, 15};
bool draggingSong = false;
bool draggingVol = false;
float percentageSong = 0.0f;


char timeElapsedFormatted [10];
char timeTotalFormatted [10];
char volumeFormatted [10];

void InitGUI() {
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
    SetExitKey(KEY_NULL);
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
    HandleInput();
    HandleDragAndDrop();
    UpdatePlaylist();
}

void HandleInput() {
    int key = GetKeyPressed();
    switch (key) {
        case KEY_UP: PrevSong(); break;
        case KEY_DOWN: NextSong(); break;
        case KEY_SPACE: HandlePause(); break;
        case KEY_DELETE: RemoveSongAt(GetCurrentSongIndex());
        default: break;
    }
}

void HandleDragAndDrop() {
    if (IsFileDropped()) {
        FilePathList files_path = LoadDroppedFiles();
        for (int i = 0; i < files_path.count; i++) {
            char *file = files_path.paths[i];
            AddSong(file);
        }
        UnloadDroppedFiles(files_path);
        if (!IsPlaylistReady()) {
            StartPlaying();
        }
    }
}

void DrawGUIComponents() {
    float total = -1;
    float elapsed = -1;
    if (IsPlaylistReady()) {
        total = currentSong.length;
        elapsed = GetMusicTimePlayed(currentSong.music);
        percentageSong = draggingSong ? percentageSong : (elapsed / total) * 100;   // if we are dragging the slider, then do not compute the percentage elapsed.
    }
    else {
        percentageSong = 0;   // if playlist not ready, no percentage of song available
    }
    percentageSong = GuiSliderBar(slider, FormatTime(elapsed, timeElapsedFormatted), FormatTime(total, timeTotalFormatted), percentageSong, 0, 100);
    Vector2 mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, slider) && IsPlaylistReady()) {
        if (!draggingSong && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            draggingSong = true;
        }
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && draggingSong) {
        SetTimeSong(percentageSong);
        draggingSong = false;
    }
    if (GuiButton((Rectangle){SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT - 50 - 15, 30, 30}, GuiIconText(ICON_PLAYER_PREVIOUS, ""))) PrevSong();
    if(GuiButton((Rectangle){SCREEN_WIDTH/2 - 15, SCREEN_HEIGHT - 50 - 15, 30, 30}, GuiIconText(currentPlayIcon, ""))) {
        HandlePause();
    }
    if(GuiButton((Rectangle){SCREEN_WIDTH/2 + 30, SCREEN_HEIGHT - 50 - 15, 30, 30}, GuiIconText(ICON_PLAYER_NEXT, ""))) NextSong();
    float volume = GetVolume();
    volume = GuiSliderBar(volSlider, VOLUME_STRING, FormatVolume(volume, volumeFormatted), volume, 0, 1);
    if (CheckCollisionPointRec(mousePoint, volSlider)) {
        if (!draggingVol && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            draggingVol = true;
        }
    }
    if (draggingVol && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        SetVolume(volume);
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && draggingVol) {
        draggingVol = false;
    }
}

void DrawGUIText() {
    if (!IsPlaylistReady()) {
        DrawTextCentered("Drag & Drop your music!", 40, WHITE);
        return;
    }
    DrawText("Playlist", 20, 20, 30, WHITE);
    DrawLineEx((Vector2){20,55}, (Vector2){140,55}, 5, WHITE);
    int y = 70;
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
        if (GuiButton((Rectangle){20, y, 20, 20}, GuiIconText(ICON_CROSS, ""))) RemoveSongAt(i);
        y += 30;
    }
    DrawTextCentered(currentSong.name, 40, WHITE);
}

void HandlePause() {
    if (IsPlaylistReady()) {
        TogglePause();
        currentPlayIcon = currentPlayIcon == ICON_PLAYER_PAUSE ? ICON_PLAYER_PLAY : ICON_PLAYER_PAUSE;
    }
}