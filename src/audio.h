#ifndef _audio_h_
#define _audio_h_

#include <raylib.h>
#include <ctype.h>

typedef struct _song {
    Music music;
    bool valid;
    char *name;
    bool paused;
    float length;
} Song;

typedef struct _play_list {
    Song  *songs;
    size_t length;
    size_t capacity;
    int current;
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
void SetLooping(bool looping);
bool IsPlayingPlayList();
bool IsLooping();

#endif // _audio_h_