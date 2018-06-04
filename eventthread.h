#ifndef EVENTTHREAD_H
#define EVENTTHREAD_H

#include <thread>
#include <mutex>
#include <list>
#include <string>
#include "eventtemplate.h"
#include "Vector2.h"
#include "eventdefinitions.h"

namespace FalconeEngine
{

    class eventThread : public eventTemplate
    {
    private:
        std::thread * inputThread;
        std::mutex mutex;
        std::list<Command> commands;

        bool isPlaying;

    public:
        eventThread();
        ~eventThread();

        bool HasCommands() override;
        Command PopCommands() override;

        Vector2 mousePosition() override;
        bool mouseClick(mouseEvent typeEvent) override;

        bool isQuiting() override;
        void Quit() override;

        void GetInput();
        void AddInput(Command _command) override;
        void AddInput(std::string _command);
    };
}

#endif // EVENTTHREAD_H
