#include "eventthread.h"
#include <vector>
namespace FalconeEngine
{
    eventThread::eventThread() : eventTemplate(), isPlaying(true), inputThread(nullptr)
    {
        this->inputThread = new std::thread(&eventThread::GetInput, this);
    }

    eventThread::~eventThread()
    {
        if(this->inputThread != nullptr)
        {
            this->inputThread->join();
            delete this->inputThread;
        }
    }

    bool eventThread::HasCommands()
    {
        this->mutex.lock();
        bool hasCommands = (this->commands.size() > 0);
        this->mutex.unlock();

        return hasCommands;
    }

    Command eventThread::PopCommands()
    {
        this->mutex.lock();
        Command cmd = this->commands.front();
        this->commands.pop_front();
        this->mutex.unlock();
        return cmd;
    }

    Vector2 eventThread::mousePosition()
    {
		return Vector2::Zero();
    }

    bool eventThread::mouseClick(mouseEvent typeEvent)
    {
		return false;
    }

    bool eventThread::isQuiting()
    {
        this->mutex.lock();
        bool isPlaying = this->isPlaying;
        this->mutex.unlock();

        return !isPlaying;
    }

    void eventThread::Quit()
    {
        this->mutex.lock();
        this->isPlaying = false;
        this->mutex.unlock();
    }

    void eventThread::GetInput()
    {
        std::string cmd;

        while(this->isPlaying)
        {
            std::cout << "Write AI command: ";
            std::getline(std::cin, cmd);

            if(cmd.length() > 0)
            {
                this->AddInput(this->parseString(cmd));
            }

        }
    }

    void eventThread::AddInput(Command _command)
    {
        this->mutex.lock();
        this->commands.push_back(_command);
        this->mutex.unlock();
    }

    void eventThread::AddInput(std::string _command)
    {
        this->AddInput(this->parseString(_command));
    }
}
