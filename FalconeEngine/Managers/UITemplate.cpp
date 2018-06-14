#include "UITemplate.h"
//#include "FalconeEngine/rendersdl.h"
#include "../Core/Component.h"
#include <iostream>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>

namespace FalconeEngine
{
    UITemplate::UITemplate() : uiSequence(0)
    {
        this->uiMap = new std::map<int, Component *>();
    }

    UITemplate::~UITemplate()
    {
    }

    int UITemplate::AddElement(Component * msg)
    {
        this->uiMap[this->uiSequence] = msg;

        return this->uiSequence++;
    }

    void UITemplate::Render()
    {
    }
}
