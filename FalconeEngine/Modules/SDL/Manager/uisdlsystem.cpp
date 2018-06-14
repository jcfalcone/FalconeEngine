#include "uisdlsystem.h"
#include "rendersdl.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../../../Managers/ObjectControl.h"

UISDLSystem::UISDLSystem() : uiSequence(0)
{
    this->render = static_cast<renderSDL*>(ObjectControl::Instance()->getRender());
}

UISDLSystem::~UISDLSystem()
{
}

int UISDLSystem::AddElement(Component * _msg)
{

    return UITemplate::AddElement(_msg);
    /*

    this->uiMap[this->uiSequence] = msg;

    return this->uiSequence++;*/
}

bool UISDLSystem::AddFont(std::string _name, std::string _path, int _size) override
{
    this->fonts[_name] = TTF_OpenFont(_path, _size);

    if(TTF_Init() != 0)
    {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
        //return 1;
    }

    atexit(TTF_Quit);
}

void UISDLSystem::Render()
{
}
