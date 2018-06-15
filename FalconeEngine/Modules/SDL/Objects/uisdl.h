#ifndef UISDL_H
#define UISDL_H

#include "../../../Core/Component.h"
#include "../../../Managers/ObjectControl.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class UISDL : public FalconeEngine::Component
{
private:
    SDL_Rect		dest;
    class renderSDL   * render;
    class UISDLSystem * uiManager;

    SDL_Surface *textSdl;
    SDL_Texture* Message;
    SDL_Color color;

    std::string text;
    std::string font;

public:
    UISDL(std::string _font, std::string _text, SDL_Color _color);
    UISDL(std::string _font, int _text, SDL_Color _color);
    UISDL(std::string _font, double _text, SDL_Color _color);
    UISDL(std::string _font, float _text, SDL_Color _color);

    void Start() override;
    void Update(float _deltaTime) override;
    void Render() override;

    std::string GetText() const { return this->text; }
    void SetText(std::string _text);

    std::string GetFont() const { return this->font; }
    void SetFont(std::string _font);

    SDL_Color GetColor() const { return this->color; }
    void SetColor(SDL_Color _color);

    static SDL_Color WHITE() const { return {255, 255, 255}; }
    static SDL_Color BLACK() const { return {0, 0, 0}; }
};

#endif // UISDL_H
