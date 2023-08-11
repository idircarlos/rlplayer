#ifndef _audio_h_
#define _audio_h_

#include <raylib.h>
#include <ctype.h>
#include "list.h"

typedef struct _song {
    Music music;
    bool valid;
    char *name;
    float length;
} Song;

void InitPlaylist();
void AddSong(char *song_path);
Song GetSongFromPlaylist(size_t index);
void RemoveSongAt(int index);
Song GetCurrentSong();
size_t GetPlaylistSize();
size_t GetCurrentSongIndex();
void SwapSongs(int i, int j);
float GetVolume();
void SetVolume(float volPercentage);
void StartPlaying();
void TogglePause();
void SetTimeSong(float percentage);
void UpdatePlaylist();
void PlaySong(int index);
void PrevSong();
void NextSong();
bool IsFirstSong();
bool IsLastSong();
void SetLooping(bool looping);
bool IsPlaylistReady();
bool IsLooping();
bool IsPaused();

#endif // _audio_h_