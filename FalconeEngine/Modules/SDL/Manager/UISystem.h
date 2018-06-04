#ifndef UISYSTEM
#define UISYSTEM

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <SDL_ttf.h>
#include "Vector2.h"
#include "FalconeEngine/ObjectControl.h"

class UIMsg
{
	public:
        UIMsg(){}//std::string msg, Vector2 pos) : message(msg), position(pos) { };

		std::string message;
        Vector2 position;
        Vector2 scale;
        SDL_Surface *text;
        SDL_Texture* Message;
};

class UISystem
{
private:
	std::map<int, UIMsg *> * uiMap;
	int uiSequence;
    TTF_Font        *gameFont      = NULL;
    SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    ObjectControl * parent;
public:
	UISystem();
	~UISystem();

    void setParent(ObjectControl * prt) { this->parent = prt; }

	int addElement(UIMsg * msg);
	void updateString(int id, std::string msg);

	void Render();
};

#endif // UISYSTEM

