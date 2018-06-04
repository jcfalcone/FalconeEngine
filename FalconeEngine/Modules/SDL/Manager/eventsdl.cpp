#include "eventsdl.h"
#include <iostream>

eventSDL::eventSDL():eventTemplate()
{

}


Vector2 eventSDL::mousePosition()
{
    SDL_PumpEvents();

    int x,y;

    SDL_GetMouseState(&x, &y);

    //
    //SDL_GetGlobalMouseState(&x,&y);

    return Vector2(x,y);
}

bool eventSDL::mouseClick(mouseEvent typeEvent)
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    return true;
                }
                break;
        }
    }

    return false;
}


bool eventSDL::quit()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                return true;
                break;
        }
    }

    return false;
}
