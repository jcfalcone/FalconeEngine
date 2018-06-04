#ifndef RENDERERSDL_H
#define RENDERERSDL_H

#include <string>
#include <SDL.h>

#include "../../../Managers/rendertemplate.h"
#include "../../../Core/Vector2.h"

using namespace FalconeEngine;

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

    SDL_Renderer * getRender() { return this->render; }
};

#endif // RENDERERSDL_H
