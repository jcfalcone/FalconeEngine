#ifndef EVENTTEMPLATE_H
#define EVENTTEMPLATE_H

#include "Vector2.h"
#include "eventdefinitions.h"
#include <string>

namespace FalconeEngine
{
    enum class mouseEvent
    {
        LEFTBUTTON,
        RIGHTBUTTON
    };

    class eventTemplate
    {
    public:
        eventTemplate();

        Command parseString(std::string _command);

        virtual bool HasCommands() = 0;
        virtual Command PopCommands() = 0;

        virtual Vector2 mousePosition() =  0;
        virtual bool mouseClick(mouseEvent typeEvent) =  0;

        virtual bool isQuiting() = 0;
        virtual void Quit() = 0;

        virtual void AddInput(Command _command) = 0;
    };
}

#endif // EVENTTEMPLATE_H
