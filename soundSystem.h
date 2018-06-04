#ifndef SOUNDSYSTEM
#define SOUNDSYSTEM
//#include <SDL_mixer.h>

#include <map>
class soundSystem
{
    /*std::map<char *, Mix_Music *> * soundMap;
    std::map<char *, Mix_Chunk *> * effectMap;*/
public:
	soundSystem();
	~soundSystem();

	void addSound(char * key, char * path);
	void playSound(char * key, bool loop);


    void addEffect(char * key, char * path);
    void playEffect(char * key);
};
#endif
