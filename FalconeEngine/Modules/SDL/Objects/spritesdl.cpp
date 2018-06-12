#include "spritesdl.h"
#include "../../../Managers/ObjectControl.h"
#include "../Manager/rendersdl.h"
#include <SDL_image.h>

SpriteSDL::SpriteSDL() : path(""), rend(nullptr), texture(nullptr)
{
}

SpriteSDL::SpriteSDL(std::string _path) : path(_path), rend(nullptr), texture(nullptr)
{

}

SpriteSDL::~SpriteSDL()
{
    SDL_DestroyTexture(this->texture);
}

void SpriteSDL::Start()
{
    if(this->path.length() > 0)
    {
        if (renderSDL *render = dynamic_cast<renderSDL*>(FalconeEngine::ObjectControl::Instance()->getRender()))
        {
            if(this->texture != nullptr)
            {
                SDL_DestroyTexture(this->texture);
            }

            this->rend = render;

            this->texture = IMG_LoadTexture(render->getRender(), this->path.c_str());

            if (!this->texture)
            {
                std::cerr << "IMG_LoadTexture(texture) Error: " << IMG_GetError() << std::endl;
            }
        }
    }
}

void SpriteSDL::Update(float _deltaTime)
{
}

void SpriteSDL::Render()
{
    if(this->rend == nullptr || this->path.length() == 0 || !this->parent->isVisible())
    {
        return;
    }

    this->dest.x = this->parent->getPosition().x;
    this->dest.y = this->parent->getPosition().y;
    this->dest.h = this->parent->getScale().y;
    this->dest.w = this->parent->getScale().x;

    SDL_RenderCopyEx(this->rend->getRender(), this->texture, nullptr, &dest, this->parent->getRotation(), nullptr, SDL_FLIP_NONE);
}

void SpriteSDL::SetPath(std::string _path)
{
    if(_path != this->path)
    {
        this->path = _path;
        this->Start();
    }
}
