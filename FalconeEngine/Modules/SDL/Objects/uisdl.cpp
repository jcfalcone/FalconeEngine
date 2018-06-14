#include "uisdl.h"
#include "../Manager/uisdlsystem.h"
#include "../Manager/rendersdl.h"

UISDL::UISDL(std::string _font, std::string _text, SDL_Color _color) : font(_font), text(_text), color(_color)
{
}

void UISDL::Start()
{

    if (this->render = dynamic_cast<renderSDL*>(FalconeEngine::ObjectControl::Instance()->getRender()))
    {
        this->uiManager = dynamic_cast<UISDLSystem*>(FalconeEngine::ObjectControl::Instance()->getUISystem());
        TTF_Font * font = this->uiManager->GetFont(this->font);

        this->textSdl    = TTF_RenderText_Solid(font, this->text.c_str(), this->color);
        this->Message = SDL_CreateTextureFromSurface(this->render->getRender(), this->textSdl); //now you can convert it into a texture
    }
}

void UISDL::Update(float _deltaTime)
{
}

void UISDL::Render()
{
    if(this->render == nullptr || this->text.length() == 0 || !this->parent->isVisible())
    {
        return;
    }

    this->dest.x = this->parent->getPosition().x;
    this->dest.y = this->parent->getPosition().y;
    this->dest.h = this->parent->getScale().y;
    this->dest.w = this->parent->getScale().x;

    SDL_RenderCopyEx(this->rend->getRender(), this->Message, nullptr, &dest, this->parent->getRotation(), nullptr, SDL_FLIP_NONE);
}

void UISDL::SetText(std::string _text)
{
    if(this->text != _text)
    {
        this->text = _text;
        this->Start();
    }
}

void UISDL::SetFont(std::string _font)
{
    if(this->font != _font)
    {
        this->font = _font;
        this->Start();
    }
}

void UISDL::SetColor(SDL_Color _color)
{
    if(this->color != _color)
    {
        this->color = _color;
        this->Start();
    }
}
