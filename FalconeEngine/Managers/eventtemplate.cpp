#include "eventtemplate.h"
#include <sstream>
#include <algorithm>


namespace FalconeEngine
{
    eventTemplate::eventTemplate()
    {

    }

    Command eventTemplate::parseString(std::string _command)
    {
        std::stringstream   sCommand(_command);
        std::string         part;
        Command paramList;

        paramList.fullCommand = _command;

        while(sCommand >> part)
        {
            if(paramList.command.empty())
            {
                std::transform(part.begin(), part.end(), part.begin(), ::toupper);
                paramList.command = part;
            }
            else
            {
                paramList.param.push_back(part);
            }

        }

        return paramList;
    }
}
