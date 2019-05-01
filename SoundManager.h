#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include <iostream>
#include <map>
#include "SDL2/SDL_mixer.h"
//FIXME: sound_t sounds cool ?
enum sound_type 
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager
{
public:
    static SoundManager* get_instance()
    {
        if (sp_instance == 0)
            sp_instance = new SoundManager();
        return sp_instance;
    }

    bool load(std::string file_name, std::string id, sound_type type);

    void play_sound(std::string id, int loop);
    void play_music(std::string id, int loop);

private:
    SoundManager();
    ~SoundManager();
    static SoundManager* sp_instance;

    std::map<std::string, Mix_Chunk*> m_sfxs;
    std::map<std::string, Mix_Music*> m_music;
};

typedef SoundManager SoundMgr;
#endif /* __SOUND_MANAGER_H__ */