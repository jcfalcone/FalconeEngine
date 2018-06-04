#ifndef RENDERERTEMPLATE_H
#define RENDERERTEMPLATE_H

#include <string>

namespace FalconeEngine
{
    class renderSpriteTemplate;

    class renderTemplate
    {
    private:
        std::string windowTitle;
    public:
        renderTemplate(std::string windowTitle);

        virtual void startRenderer() = 0;
        virtual void endRenderer() = 0;

        virtual renderSpriteTemplate * loadSprite(std::string path) = 0;
    };
}

#endif // RENDERERTEMPLATE_H
