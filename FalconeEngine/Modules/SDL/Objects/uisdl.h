#ifndef UISDL_H
#define UISDL_H

#include "../../../Core/Component.h"
#include "../../../Managers/ObjectControl.h"
#include <string>
#include <SDL.h>

class UISDL : public FalconeEngine::Component
{
private:
    SDL_Rect		dest;
    class renderSDL   * render;
    class UITemplate * uiManager;

    SDL_Surface *text;
    SDL_Texture* Message;
    SDL_COLOR color;

    std::string text;
    std::string font;

public:
    UISDL(std::string _font, std::string _text, SDL_COLOR _color);

    void Start() override;
    void Update(float _deltaTime) override;
    void Render() override;

    std::string GetText() const { return this->text; }
    void SetText(std::string _text);

    std::string GetFont() const { return this->font; }
    void SetFont(std::string _font);

    SDL_COLOR GetColor() const { return this->color; }
    void SetColor(SDL_COLOR _color);

    static const SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
};

#endif // UISDL_H
