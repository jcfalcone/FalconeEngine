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


    bool HasCommands() override;
    Command PopCommands() override;

    Vector2 mousePosition() override;
    bool mouseClick(mouseEvent _typeEvent) override;

    bool isQuiting() override;
    void Quit() override;

    void AddInput(Command _command) override;
};

#endif // EVENTSDL_H
