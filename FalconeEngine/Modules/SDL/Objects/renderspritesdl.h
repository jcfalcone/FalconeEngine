#ifndef RENDERSPRITESDL_H
#define RENDERSPRITESDL_H

#include "renderspritetemplate.h"

class renderSDL;
class SDL_Texture;

class renderSpriteSDL : public renderSpriteTemplate
{
    renderSDL   * rend;
    SDL_Texture * texture;
public:
    renderSpriteSDL(renderSDL *render);

    bool load(std::string path);
    bool render(Vector2 position, Vector2 size);
};

#endif // RENDERSPRITESDL_H
