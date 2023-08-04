#include "audio.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static Playlist playlist = {0};

Song CreateSong(char *song_path) {
    Music music = LoadMusicStream(song_path);
    music.looping = false;
    Song song = {0};
    song.music = music;
    song.valid = true;
    const char *filename = GetFileName(song_path);
    song.name = malloc(strlen(filename) + 1);
    strcpy(song.name, filename);
    song.length = GetMusicTimeLength(music);
    return song;
}

float GetSecondsFromPercetage(Song song, float percentage) {
    float totalSeconds = song.length;
    return (totalSeconds*percentage)/100;
}

void InitPlaylist() {
    playlist.capacity = 5;
    playlist.length = 0;
    playlist.current = -1;
    playlist.paused = true;
    playlist.songs = (Song*)malloc(playlist.capacity * sizeof(Music));
    if (playlist.songs == NULL) {
        fprintf(stderr, "Could not allocate memory for playlist");
        exit(-1);
    }
}

void AddSong(char *song_path) {
    Song song = CreateSong(song_path);
    if (playlist.length == playlist.capacity) {
        playlist.capacity *= 2;
        playlist.songs = realloc(playlist.songs, playlist.capacity);
        if (playlist.songs == NULL) {
            fprintf(stderr, "Could not reallocate memory for playlist");
            exit(-1);
        }
    }
    playlist.songs[playlist.length++] = song;
}

Song GetSongFromPlayList(size_t index) {
    if (index >= 0 && index < playlist.length) {
        return playlist.songs[index];
    }
    fprintf(stderr, "Index %lld is out of bounds for playlist with size %lld", index, playlist.length);
    exit(-1);
}

Song GetCurrentSong() {
    if (IsPlayingPlaylist() && GetPlaylistSize() > 0){
        return playlist.songs[playlist.current];
    }
    return (Song){0};
}

size_t GetPlaylistSize() {
    return playlist.length;
}

void RemoveSongAt(size_t index);

void StartPlaying() {
    if (playlist.length > 0) {
        playlist.current = 0;
        playlist.paused = false;
        PlayMusicStream(playlist.songs[playlist.current].music);
    }
}

void TogglePause() {
    if (playlist.length > 0 && playlist.current != -1) {
        if (!IsPaused()){
            PauseMusicStream(playlist.songs[playlist.current].music);
            playlist.paused = true;
        }
        else {
            PlayMusicStream(playlist.songs[playlist.current].music);
            playlist.paused = false;
        }
    }
}

void SetTimeSong(float percentage) {
    Song currentSong = GetCurrentSong();
    if (!currentSong.valid) return;
    float seconds = GetSecondsFromPercetage(currentSong, percentage);
    SeekMusicStream(currentSong.music, seconds+1);
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

void NextSong() {
    if (IsPlayingPlaylist()) {
        if (playlist.current == playlist.length - 1) return;
        playlist.current++;
        PlayMusicStream(playlist.songs[playlist.current].music);
    }
}

void PrevSong() {
    if (IsPlayingPlaylist()) {
        if (playlist.current == 0) return;
        playlist.current--;
        PlayMusicStream(playlist.songs[playlist.current].music);
    }
}

bool IsLastSong() {
    if (IsPlayingPlaylist()) {
        if (playlist.current == playlist.length - 1) return true;
    }
    return false;
}

void SetLooping(bool looping);
bool IsPlayingPlaylist() {
    return playlist.current >= 0;
}
bool IsLooping();

bool IsPaused() {
    return playlist.paused;
}