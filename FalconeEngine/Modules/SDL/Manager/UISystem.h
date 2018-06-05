#ifndef UISYSTEM
#define UISYSTEM

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <SDL_ttf.h>
#include "../../../Core/Vector2.h"

using namespace FalconeEngine;

class UISystem/* : public UITemplate*/
{
private:
	int uiSequence;
    TTF_Font        *gameFont      = NULL;

    class renderSDL * render;
public:
	UISystem();
    ~UISystem();

	int addElement(UIMsg * msg);
	void updateString(int id, std::string msg);

	void Render();
    static const SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
};

#endif // UISYSTEM

