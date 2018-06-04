#ifndef RENDERSPRITETEMPLATE_H
#define RENDERSPRITETEMPLATE_H

#include "../Core/Vector2.h"
#include<string>

namespace FalconeEngine
{
    class renderSpriteTemplate
    {
    protected:
        std::string path;
    public:
        renderSpriteTemplate(std::string path);

        virtual bool load(std::string path) = 0;
        virtual bool render(Vector2 position, Vector2 size) = 0;


    };
}

#endif // RENDERSPRITETEMPLATE_H
