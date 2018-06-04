#include "UISystem.h"
//#include "FalconeEngine/rendersdl.h"
#include <iostream>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>

UISystem::UISystem() : uiSequence(0)
{
	this->uiMap = new std::map<int, UIMsg *>();

    /*this->gameFont      = TTF_OpenFont("Fonts/FreeSerif.ttf", 50);

    if(TTF_Init() != 0)
    {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
        //return 1;
    }

    atexit(TTF_Quit);*/
}

UISystem::~UISystem()
{
	for (auto iterator = this->uiMap->begin(); iterator != this->uiMap->end(); iterator++)
	{
		delete iterator->second;
	}

	delete this->uiMap;
}

int UISystem::addElement(UIMsg * msg)
{
    /*renderSDL * render = (renderSDL *)this->parent->getRender();
    msg->text    = TTF_RenderText_Solid(this->gameFont, msg->message.c_str(), this->White);
    msg->Message = SDL_CreateTextureFromSurface(render->getRender(), msg->text); //now you can convert it into a texture
	*/
	this->uiMap->emplace(this->uiSequence, msg);

	return this->uiSequence++;
}

void UISystem::updateString(int id, std::string msg)
{
	auto uiObj = this->uiMap->find(id);

	if (uiObj != this->uiMap->end())
	{
		uiObj->second->message = msg;
	}
}

void UISystem::Render()
{
    /*renderSDL * render = (renderSDL *)this->parent->getRender();
    for (auto iterator = this->uiMap->begin(); iterator != this->uiMap->end(); iterator++)
    {
        SDL_Rect		dest;

        dest.x = iterator->second->position.x;
        dest.y = iterator->second->position.y;
        dest.h = iterator->second->scale.y;
        dest.w = iterator->second->scale.x;

        SDL_RenderCopy(render->getRender(), iterator->second->Message, nullptr, &dest);
	}*/
}
