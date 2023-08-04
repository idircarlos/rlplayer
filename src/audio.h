#ifndef _audio_h_
#define _audio_h_

#include <raylib.h>
#include <ctype.h>

typedef struct _song {
    Music music;
    bool valid;
    char *name;
    float length;
} Song;

typedef struct _play_list {
    Song  *songs;
    size_t length;
    size_t capacity;
    int current;
    bool paused;
} Playlist;

void InitPlaylist();
void AddSong(char *song_path);
Song GetSongAt(size_t index);
void RemoveSongAt(size_t index);
Song GetCurrentSong();
size_t GetPlaylistSize();
void StartPlaying();
void TogglePause();
void SetTimeSong(float percentage);
void UpdatePlaylist();
void NextSong();
void PrevSong();
bool IsLastSong();
void SetLooping(bool looping);
bool IsPlayingPlaylist();
bool IsLooping();
bool IsPaused();

#endif // _audio_h_