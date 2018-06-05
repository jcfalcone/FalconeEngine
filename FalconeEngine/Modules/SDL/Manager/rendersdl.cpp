#include "rendersdl.h"
#include <iostream>
#include <SDL_image.h>

renderSDL::renderSDL(std::string windowTitle, Vector2 position, Vector2 size): renderTemplate(windowTitle), render(nullptr), window(nullptr)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    std::cout << "Everything works A-OK!!" << std::endl;

    this->window = SDL_CreateWindow(windowTitle.c_str(), position.x, position.y, size.x, size.y, SDL_WINDOW_SHOWN);

    if (this->window == NULL)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return;
    }

    this->render = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (this->render == NULL)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return;
    }
}

renderSDL::~renderSDL()
{
    //SDL Manager
    SDL_DestroyRenderer(this->render);
    SDL_DestroyWindow(this->window);
}


void renderSDL::startRenderer()
{
    //Clear Scren to prepare to drawing
    SDL_RenderClear(this->render);
}

void renderSDL::endRenderer()
{
    //Update Screen
    SDL_RenderPresent(this->render);
}
