#ifndef UIOBJSDL_H
#define UIOBJSDL_H

#include "../../../Core/Object.h"
#include "uisdl.h"

class UIObjSDL : public FalconeEngine::Object
{
private:
    UISDL * component;

public:
    UIObjSDL();

    void Start() override;
    void Update(float _deltaTime) override;
    void Render() override;


    std::string GetText() const { return this->component->GetText(); }
    void SetText(std::string _text)
    {
        this->component->SetText(_text);
    }

    std::string GetFont() const { return this->component->GetFont(); }
    void SetFont(std::string _font)
    {
        this->component->SetFont(_font);
    }

    SDL_Color GetColor() const { return this->component->GetColor(); }
    void SetColor(SDL_Color _color)
    {
        this->component->SetColor(_color);
    }
};

#endif // UIOBJSDL_H
