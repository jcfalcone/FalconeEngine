#ifndef EVENTSDL_H
#define EVENTSDL_H

#include "../../../Managers/eventtemplate.h"
#include <SDL.h>

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
