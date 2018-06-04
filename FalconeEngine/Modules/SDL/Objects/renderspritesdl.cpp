#include "renderspritesdl.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "rendersdl.h"


renderSpriteSDL::renderSpriteSDL(renderSDL *render):renderSpriteTemplate(""), rend(render)
{
}

bool renderSpriteSDL::load(std::string path)
{
    this->path = path;

    this->texture = IMG_LoadTexture(this->rend->getRender(), this->path.c_str());

    if (!this->texture)
    {
        std::cerr << "IMG_LoadTexture(texture) Error: " << IMG_GetError() << std::endl;
    }
}

bool renderSpriteSDL::render(Vector2 position, Vector2 size)
{
    SDL_Rect		dest;

    dest.x = position.x;
    dest.y = position.y;
    dest.h = size.y;
    dest.w = size.x;

    SDL_RenderCopy(this->rend->getRender(), this->texture, nullptr, &dest);
}
