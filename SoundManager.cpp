#include "SoundManager.h"

SoundManager* SoundManager::sp_instance = nullptr;
SoundManager::SoundManager() 
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

bool SoundManager::load(std::string file_name, std::string id, sound_type type)
{
    if (type == SOUND_MUSIC)
    {
        Mix_Music* p_music = Mix_LoadMUS(file_name.c_str());
        if (p_music == 0)
        {
            std::cout << "[SoundManager.cpp] Could not load music: Error - "
            << Mix_GetError() << std::endl;
            return false;
        }
        m_music[id] = p_music;
        return true;
    }
    else if (type == SOUND_SFX) 
    {
        Mix_Chunk* p_chunk = Mix_LoadWAV(file_name.c_str());
        if (p_chunk == 0)
        {
            std::cout << "[SoundManager.cpp] Could not load SFX: Error - "
            << Mix_GetError() << std::endl;
            return false;
        }
        m_sfxs[id] = p_chunk;
        return true;
    }
    return false;
}

void SoundManager::play_music(std::string id, int loop)
{
    Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::play_sound(std::string id, int loop)
{
    Mix_PlayChannel(-1, m_sfxs[id], loop);
}


SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}
