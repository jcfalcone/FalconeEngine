#include "rendersdl.h"
#include <iostream>
#include <SDL_image.h>
#include "FalconeEngine/renderspritesdl.h"
#include "FalconeEngine/rendertemplate.h"

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


    /*SDL_Texture		* menuOp;
    SDL_Rect		src, dest;

    SDL_Texture *texture = IMG_LoadTexture(this->render, "cards-1.3/3_of_diamonds.png");

    if (!texture)
    {
        std::cerr << "IMG_LoadTexture(texture)2  Error: " << IMG_GetError() << std::endl;
    }

    menuOp = IMG_LoadTexture(this->renderSDL, "C:/Projects/VisualStudio/SDL_Week9/Debug/Lab/Pong_MenuOp1.bmp");

    if (!menuOp)
    {
        std::cerr << "IMG_LoadTexture(menuOp) Error: " << IMG_GetError() << std::endl;
        system("PAUSE");
        return;
    }

    src.x = 125;
    src.y = 155;
    src.h = 50;
    src.w = 387;

    dest.x = 125;
    dest.y = 155;
    dest.h = 50;
    dest.w = 387;

    //Drawing textures to screen
    SDL_RenderCopy(this->renderSDL, menuOp, nullptr, &dest);


    //Wait for 2 seconds
    SDL_Delay(2000);

    //Clean Up Project
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(menuOp);*/
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

renderSpriteTemplate *renderSDL::loadSprite(std::string path)
{
    renderSpriteSDL* sprite = new renderSpriteSDL(this);
    sprite->load(path);
    return sprite;
}
