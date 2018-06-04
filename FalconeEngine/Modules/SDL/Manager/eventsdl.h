#ifndef EVENTSDL_H
#define EVENTSDL_H

#include "../../../Managers/eventtemplate.h"
#include <SDL.h>

using namespace FalconeEngine;

class eventSDL : public eventTemplate
{
    SDL_Event event;
public:
    eventSDL();

    Vector2 mousePosition();
    bool mouseClick(mouseEvent typeEvent);

    bool quit();
};

#endif // EVENTSDL_H
