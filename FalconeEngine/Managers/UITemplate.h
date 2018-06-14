#ifndef UITEMPLATE
#define UITEMPLATE

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "../Core/Vector2.h"
#include "ObjectControl.h"

namespace FalconeEngine
{
    class UITemplate
    {
    private:
        std::map<int, Component *> * uiMap;
        int uiSequence;
        //TTF_Font        *gameFont      = NULL;
        //SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

        //ObjectControl * parent;
    public:
        UITemplate();
        ~UITemplate();

        //void setParent(ObjectControl * prt) { this->parent = prt; }

        virtual int AddElement(Component *msg);

        virtual bool AddFont(std::string _name, std::string _path, int _size) = 0;

        template<typename T>
        virtual T GetFont(std::string _name) = 0;

        void Render();
    };
}

#endif // UITEMPLATE

