#ifndef OBJECTCONTROLTEMPLATE_H
#define OBJECTCONTROLTEMPLATE_H

#include "FalconeEngine/Object.h"
#include <string>
#include <map>
#include <iostream>
#include <utility>

namespace FalconeEngine
{
    template<typename T>
    T ObjectControl::FindElementByName(std::string _name)
    {
        auto it = std::find_if(this->objMap->begin(), this->objMap->end(), [_name](const std::pair<int, Object *> & obj)
        {
            return obj.second->GetName() == _name;
        });

        if (it != this->objMap->end())
        {
          // found element. it is an iterator to the first matching element.
          // if you really need the index, you can also get it:
          return (T)it->second;
        }

        return nullptr;
    }

    template<typename T>
    T ObjectControl::FindElementByTag(std::string _tag)
    {
        auto it = find_if(this->objMap->begin(), this->objMap->end(), [&_tag](const std::pair<int, Object *> & obj) { return obj.second->getTag() == _tag; });

        if (it != this->objMap->end())
        {
          // found element. it is an iterator to the first matching element.
          // if you really need the index, you can also get it:
          return (T)it->second;
        }

        return nullptr;
    }
}

#endif // OBJECTCONTROLTEMPLATE_H
