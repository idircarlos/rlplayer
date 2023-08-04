#include "audio.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static PlayList playlist = {0};

Song CreateSong(char *song_path) {
    Music music = LoadMusicStream(song_path);
    music.looping = false;
    Song song = {0};
    song.music = music;
    song.valid = true;
    const char *filename = GetFileName(song_path);
    song.name = malloc(strlen(filename) + 1);
    strcpy(song.name, filename);
    song.paused = false;
    song.length = GetMusicTimeLength(music);
    return song;
}

float GetSecondsFromPercetage(Song song, float percentage) {
    float totalSeconds = song.length;
    return (totalSeconds*percentage)/100;
}

void InitPlayList() {
    playlist.capacity = 5;
    playlist.length = 0;
    playlist.current = -1;
    playlist.songs = (Song*)malloc(playlist.capacity * sizeof(Music));
    if (playlist.songs == NULL) {
        fprintf(stderr, "Could not allocate memory for playlist");
        exit(-1);
    }
}

void AddMusicToPlayList(char *song_path) {
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

Song GetCurrentMusic() {
    if (IsPlayingPlayList() && GetPlayListSize() > 0){
        return playlist.songs[playlist.current];
    }
    return (Song){0};
}

size_t GetPlayListSize() {
    return playlist.length;
}

void RemoveSongFromPlayList(size_t index);

void StartPlaying() {
    if (playlist.length > 0) {
        playlist.current = 0;
        PlayMusicStream(playlist.songs[playlist.current].music);
    }
}

void ToggleMusicPause() {
    if (playlist.length > 0 && playlist.current != -1) {
        if (IsMusicStreamPlaying(playlist.songs[playlist.current].music)){
            PauseMusicStream(playlist.songs[playlist.current].music);
            playlist.songs[playlist.current].paused = true;
        }
        else {
            PlayMusicStream(playlist.songs[playlist.current].music);
            playlist.songs[playlist.current].paused = false;
        }
    }
}

void SetTimeSong(float percentage) {
    Song currentSong = GetCurrentMusic();
    if (!currentSong.valid) return;
    float seconds = GetSecondsFromPercetage(currentSong, percentage);
    SeekMusicStream(currentSong.music, seconds+1);
}

void UpdatePlayList() {
    Song currentSong = GetCurrentMusic();
    if (currentSong.valid && !currentSong.paused) {
        if (IsMusicStreamPlaying(currentSong.music)) {
            UpdateMusicStream(currentSong.music);
        }
        else {
            PlayMusicStream(playlist.songs[++playlist.current].music);
        }
    }
}

void SetLooping(bool looping);
bool IsPlayingPlayList() {
    return playlist.current >= 0;
}
bool IsLooping();