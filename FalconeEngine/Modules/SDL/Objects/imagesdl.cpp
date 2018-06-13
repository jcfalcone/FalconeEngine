#include "imagesdl.h"

ImageSDL::ImageSDL(std::string _path, std::string _name, FalconeEngine::Object *_parent) : Object(_name, _parent)
{
    this->AddComponent("SpriteRender", new SpriteSDL(_path));
}

void ImageSDL::Start() override
{
    FalconeEngine::Object::Start();
}

void ImageSDL::Update(float _deltaTime) override
{
    FalconeEngine::Object::Update(_deltaTime);
}

void ImageSDL::Render() override
{
    FalconeEngine::Object::Render();
}

void ImageSDL::OnDestroy() override
{
    FalconeEngine::Object::OnDestroy();
}
