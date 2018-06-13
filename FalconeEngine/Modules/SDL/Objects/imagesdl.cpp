#include "imagesdl.h"

ImageSDL::ImageSDL(std::string _path, std::string _name, FalconeEngine::Object *_parent) : Object(_name, _parent)
{
    this->AddComponent("SpriteRender", new SpriteSDL(_path));
}

void ImageSDL::Start()
{
    FalconeEngine::Object::Start();
}

void ImageSDL::Update(float _deltaTime)
{
    FalconeEngine::Object::Update(_deltaTime);
}

void ImageSDL::Render()
{
    FalconeEngine::Object::Render();
}

void ImageSDL::OnDestroy()
{
    FalconeEngine::Object::OnDestroy();
}
