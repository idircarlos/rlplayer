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
} PlayList;

void InitPlayList();
void AddMusicToPlayList(char *song_path);
Song GetMusicFromPlayList(size_t index);
Song GetCurrentMusic();
size_t GetPlayListSize();
void RemoveSongFromPlayList(size_t index);
void StartPlaying();
void ToggleMusicPause();
void SetTimeSong(float percentage);
void UpdatePlayList();
void NextSong();
void PrevSong();
bool IsLastSong();
void SetLooping(bool looping);
bool IsPlayingPlayList();
bool IsLooping();
bool IsPaused();

#endif // _audio_h_