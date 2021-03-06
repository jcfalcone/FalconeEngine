#include "uiobjsdl.h"

UIObjSDL::UIObjSDL(std::string _font, std::string _text, SDL_Color _color, std::string _name, FalconeEngine::Object *_parent) : Object(_name, _parent)
{
    this->component = new UISDL(_font, _text, _color);
    this->AddComponent("UI Text", this->component);
}

void UIObjSDL::Start()
{
    FalconeEngine::Object::Start();
}

void UIObjSDL::Update(float _deltaTime)
{
    FalconeEngine::Object::Update(_deltaTime);
}

void UIObjSDL::Render()
{
    FalconeEngine::Object::Render();
}

void UIObjSDL::OnDestroy()
{
    FalconeEngine::Object::OnDestroy();
}
