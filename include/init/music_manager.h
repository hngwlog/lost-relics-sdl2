#pragma once
#include <SDL_mixer.h>
#include <string>

class MusicManager {

public:
    MusicManager();
    ~MusicManager();

    void load(const std::string& path);

    void setVolume(int volume);

    void play(int loops = - 1);

    void pause();

    void resume();

    void stop();

    void free();

private:
    Mix_Music* music;
    Mix_Chunk* soundEffect;
    int volume = MIX_MAX_VOLUME;
};

