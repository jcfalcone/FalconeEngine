#ifndef EVENTDEFINITIONS_H
#define EVENTDEFINITIONS_H

#include<string>
#include<vector>

namespace FalconeEngine
{
    struct Command
    {
        std::string command;
        std::vector<std::string> param;

        std::string fullCommand;
    };
}
#endif // EVENTDEFINITIONS_H
