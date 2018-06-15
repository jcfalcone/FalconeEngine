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

bool UISDLSystem::AddFont(std::string _name, std::string _path, int _size)
{
    std::cout << _name << " - "<< _path << std::endl;

    if(TTF_Init() != 0)
    {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
        //return 1;
    }

    atexit(TTF_Quit);

    this->fonts[_name] = TTF_OpenFont(_path.c_str(), _size);

    std::cout << this->fonts[_name] << TTF_GetError() << std::endl;
}

void UISDLSystem::Render()
{
}
