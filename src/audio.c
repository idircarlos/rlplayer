#include "audio.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _playlist {
    LinkedList *songs;
    int current;
    bool paused;
} Playlist;

static float masterVolume = 0.5f;
static Playlist playlist = {0};

void DestroySong(void *elem) {
    Song *song = (Song*)elem;
    UnloadMusicStream(song->music);
    free(song->name);
}

Song *CreateSong(char *song_path) {
    Music music = LoadMusicStream(song_path);
    music.looping = false;
    Song *song = (Song*)malloc(sizeof(Song));
    song->music = music;
    song->valid = true;
    const char *filename = GetFileName(song_path);
    song->name = malloc(strlen(filename) + 1);
    strcpy(song->name, filename);
    song->length = GetMusicTimeLength(music);
    return song;
}

bool PlaylistContainsSong(const char *song_name) {
    for (size_t i = 0; i < GetPlaylistSize(); i++) {
        Song song = GetSongFromPlaylist(i);
        if (strcmp(song_name, song.name) == 0) {
            return true;
        }
    }
    return false;
}

float GetSecondsFromPercetage(Song song, float percentage) {
    float totalSeconds = song.length;
    return (totalSeconds*percentage)/100;
}

void InitPlaylist() {
    playlist.songs = ListCreate();
    playlist.paused = true;
    playlist.current = -1;
    if (playlist.songs == NULL) {
        fprintf(stderr, "Could not allocate memory for playlist");
        exit(-1);
    }
    SetVolume(masterVolume);
}

void AddSong(char *song_path) {
    const char *song_name = GetFileName(song_path);
    if (!PlaylistContainsSong(song_name)) {
        Song *song = CreateSong(song_path);
        ListAdd(playlist.songs, (void*)song);
    }
}

Song GetSongFromPlaylist(size_t index) {
    Song *song = (Song*)ListGet(playlist.songs, index);
    return *song;
}

Song GetCurrentSong() {
    if (IsPlaylistReady() && GetPlaylistSize() > 0){
        return GetSongFromPlaylist(playlist.current);
    }
    return (Song){0};
}

float GetVolume() {
    return masterVolume;
}

void SetVolume(float volPercentage) {
    if (volPercentage < 0 || volPercentage > 1.0f) return;
    masterVolume = volPercentage;
    SetMasterVolume(volPercentage);
}

size_t GetPlaylistSize() {
    return ListSize(playlist.songs);
}

size_t GetCurrentSongIndex() {
    return playlist.current;
}

void SwapSongs(int i, int j) {
    if (IsPlaylistReady()) {
        int currentIndex = GetCurrentSongIndex();
        ListSwap(playlist.songs, i, j);
        if (currentIndex == i) {
            playlist.current = j;
        }
        else if (currentIndex == j) {
            playlist.current = i;
        }
    }
}

void RemoveSongAt(int index) {
    if (index < 0) return;
    if (GetPlaylistSize() == 1 && index == 0) {
        Song onlySong = GetCurrentSong();
        StopMusicStream(onlySong.music);
        ListRemove(playlist.songs, index, DestroySong);
        playlist.current = -1;
        return;
    }
    Song songToPlay;
    if (IsFirstSong() && index == 0) {
        ListRemove(playlist.songs, index, DestroySong);
        songToPlay = GetSongFromPlaylist(0);
        PlayMusicStream(songToPlay.music);
    }
    else if (IsLastSong() && index == GetPlaylistSize() - 1) {
        songToPlay = GetSongFromPlaylist(GetPlaylistSize() - 1);
        PlayMusicStream(songToPlay.music);
        playlist.current--;
        ListRemove(playlist.songs, index, DestroySong);
    }
    else {
        if (playlist.current == index) {
            songToPlay = GetSongFromPlaylist(index+1);
            PlayMusicStream(songToPlay.music);
        }
        else if (playlist.current > index) {
            playlist.current--;
        }
        ListRemove(playlist.songs, index, DestroySong);
    }
}

void StartPlaying() {
    if (GetPlaylistSize() > 0) {
        playlist.current = 0;
        playlist.paused = false;
        Song song = GetCurrentSong();
        PlayMusicStream(song.music);
    }
}

void TogglePause() {
    if (GetPlaylistSize() > 0 && playlist.current != -1) {
        Song song = GetCurrentSong();
        if (!IsPaused()){
            PauseMusicStream(song.music);
            playlist.paused = true;
        }
        else {
            PlayMusicStream(song.music);
            playlist.paused = false;
        }
    }
}

void SetTimeSong(float percentage) {
    Song currentSong = GetCurrentSong();
    if (!currentSong.valid) return;
    float seconds = GetSecondsFromPercetage(currentSong, percentage);
    SeekMusicStream(currentSong.music, seconds);
}

void UpdatePlaylist() {
    Song currentSong = GetCurrentSong();
    if (currentSong.valid && !playlist.paused) {
        if (IsMusicStreamPlaying(currentSong.music)) {
            UpdateMusicStream(currentSong.music);
        }
        else if (!IsLastSong()){
            NextSong();
            currentSong = GetCurrentSong();
            PlayMusicStream(currentSong.music);
        }
    }
}

void PlaySong(int index) {
    if (IsPlaylistReady()) {
        if (playlist.current < 0 || playlist.current > GetPlaylistSize()) return;
        playlist.current = index;
        Song currentSong = GetCurrentSong();
        PlayMusicStream(currentSong.music);
    }
}

void PrevSong() {
    if (IsPlaylistReady()) {
        if (playlist.current == 0) return;
        playlist.current--;
        Song currentSong = GetCurrentSong();
        PlayMusicStream(currentSong.music);
    }
}

void NextSong() {
    if (IsPlaylistReady()) {
        if (playlist.current == GetPlaylistSize() - 1) return;
        playlist.current++;
        Song currentSong = GetCurrentSong();
        PlayMusicStream(currentSong.music);
    }
}

bool IsFirstSong() {
    if (IsPlaylistReady()) {
        return playlist.current == 0;
    }
    return false;
}

bool IsLastSong() {
    if (IsPlaylistReady()) {
        if (playlist.current == GetPlaylistSize() - 1) return true;
    }
    return false;
}

void SetLooping(bool looping);

bool IsPlaylistReady() {
    return playlist.current >= 0;
}
bool IsLooping();

bool IsPaused() {
    return playlist.paused;
}