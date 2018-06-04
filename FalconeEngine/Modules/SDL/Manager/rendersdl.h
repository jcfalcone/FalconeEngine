#ifndef RENDERERSDL_H
#define RENDERERSDL_H

#include <string>
#include <SDL.h>

#include "FalconeEngine/rendertemplate.h"
#include "FalconeEngine/Vector2.h"

class renderSpriteTemplate;

class renderSDL : public renderTemplate
{
private:
    SDL_Window		* window;
    SDL_Renderer	* render;
public:
    renderSDL(std::string windowTitle, Vector2 position, Vector2 size);
    ~renderSDL();

    void startRenderer();
    void endRenderer();

    renderSpriteTemplate * loadSprite(std::string path);

    SDL_Renderer * getRender() { return this->render; }
};

#endif // RENDERERSDL_H
