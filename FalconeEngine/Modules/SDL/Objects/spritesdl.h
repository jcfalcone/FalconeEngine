#ifndef SPRITESDL_H
#define SPRITESDL_H

#include <string>
#include "../../../Core/Component.h"
#include <SDL.h>

class SpriteSDL : public FalconeEngine::Component
{
private:
    class renderSDL   * rend;
    class SDL_Texture * texture;
    SDL_Rect		dest;

    std::string path;
public:
    SpriteSDL();
    SpriteSDL(std::string _path);
    ~SpriteSDL();

    void Start() override;
    void Update(float _deltaTime) override;
    void Render() override;

    void SetPath(std::string _path);
};

#endif // SPRITESDL_H
