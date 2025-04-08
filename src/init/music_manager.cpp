#include "../../include/init/defs.h"
#include "../../include/init/music_manager.h"

MusicManager::MusicManager(): music(nullptr), soundEffect(nullptr) {}

MusicManager::~MusicManager() {

    free();
}

void MusicManager::load(const std::string& path) {

    if (path.find(".wav") != std::string::npos) {
        soundEffect = Mix_LoadWAV(path.c_str());
        if (soundEffect == nullptr) logErrorAndExit("Failed to load sound effect! Mix_Error: %s\n", Mix_GetError());
    }
    else {
        music = Mix_LoadMUS(path.c_str());
        if (music == nullptr) logErrorAndExit("Failed to load music! Mix_Error: %s\n", Mix_GetError());
    }
}

void MusicManager::setVolume(int vol) {

    volume = vol;
}

void MusicManager::play(int loops) {

    if (music != nullptr) {
        if (Mix_PlayingMusic() == 0) Mix_PlayMusic(music, loops);
    }
    else if (soundEffect != nullptr) {
        int channel = Mix_PlayChannel(-1, soundEffect, loops);
        Mix_Volume(channel, volume);
    }
}

void MusicManager::pause() {

    if (Mix_PlayingMusic()) Mix_PauseMusic();
}

void MusicManager::resume() {

    if (Mix_PausedMusic()) Mix_ResumeMusic();
}

void MusicManager::stop() {

    if (music != nullptr) Mix_HaltMusic();
    else if (soundEffect != nullptr) Mix_HaltChannel(- 1);
}

void MusicManager::free() {

    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
    else if (soundEffect != nullptr) {
        Mix_FreeChunk(soundEffect);
        soundEffect = nullptr;
    }
}

