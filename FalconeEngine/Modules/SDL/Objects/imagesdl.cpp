#include "imagesdl.h"

ImageSDL::ImageSDL(std::string _path, std::string _name, FalconeEngine::Object *_parent) : Object(_name, _parent)
{
    this->AddComponent("SpriteRender", new SpriteSDL(_path));
}

void Start() override
{
    FalconeEngine::Object::Start();
}

void Update(float _deltaTime) override
{
    FalconeEngine::Object::Update(_deltaTime);
}

void Render() override
{
    FalconeEngine::Object::Render();
}

void OnDestroy() override
{
    FalconeEngine::Object::OnDestroy();
}
