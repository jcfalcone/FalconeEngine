#ifndef UISYSTEM
#define UISYSTEM

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <SDL_ttf.h>
#include "../../../Core/Vector2.h"
#include "../../../Managers/UITemplate.h"

using namespace FalconeEngine;

class UISDLSystem : public UITemplate
{
private:
    std::map<std::string, TTF_Font *> fonts;
    int uiSequence;

    class renderSDL * render;
public:
    UISDLSystem();
    ~UISDLSystem();

    int AddElement(Component * _msg) override;
    bool AddFont(std::string _name, std::string _path, int _size) override;



    template<typename T>
    virtual T GetFont(std::string _name) override
    {
        return (T)&this->fonts[_name];
    }

    void Render();
};

#endif // UISYSTEM

