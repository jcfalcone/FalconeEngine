#include "soundSystem.h"
#include <iostream>

soundSystem::soundSystem()
{
    /*this->soundMap = new std::map<char *, Mix_Music *>();
    this->effectMap = new std::map<char *, Mix_Chunk *>();

    if( SDL_Init(SDL_INIT_AUDIO) < 0 ) exit(1);
    Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);

    Mix_Init(0);*/
}

soundSystem::~soundSystem()
{
    /*for(auto music: *this->soundMap)
    {
        Mix_FreeMusic(music.second);
    }

    for(auto music: *this->effectMap)
    {
        Mix_FreeChunk(music.second);
    }

	delete this->soundMap;*/
}

void soundSystem::addSound(char * key, char * path)
{
    /*Mix_Music * mus = Mix_LoadMUS(path);

    if(mus == NULL)
    {
        std::cerr << "Mix_LoadMUS Error: " << SDL_GetError() << std::endl;
        return;
    }

    this->soundMap->emplace(key, mus);*/
}

void soundSystem::playSound(char * key, bool loop)
{
	/*auto soundObj = this->soundMap->find(key);

	if (soundObj != this->soundMap->end())
	{
        if(loop)
        {
            Mix_PlayMusic(soundObj->second, 10);
        }
        else
        {
            Mix_PlayMusic(soundObj->second,0);
        }
        //App::PlaySoundW(soundObj->second, loop);
	}*/
}


void soundSystem::addEffect(char * key, char * path)
{
    /*Mix_Chunk * mus = Mix_LoadWAV(path);

    if(mus == NULL)
    {
        std::cerr << "Mix_LoadMUS Error: " << SDL_GetError() << std::endl;
        return;
    }

    this->effectMap->emplace(key, mus);*/
}

void soundSystem::playEffect(char * key)
{
/*    auto soundObj = this->effectMap->find(key);

    if (soundObj != this->effectMap->end())
    {
        //Mix_PlayChannel(-1, soundObj->second, 0);
    }*/
}
