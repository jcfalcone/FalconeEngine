#ifndef IMAGESDL_H
#define IMAGESDL_H

#include "../../../Core/Object.h"
#include "spritesdl.h"

class ImageSDL : public FalconeEngine::Object
{
public:
    ImageSDL(std::string _path, std::string _name, FalconeEngine::Object * _parent);

    void Start() override;
    void Update(float _deltaTime) override;
    void Render() override;
    void OnDestroy() override;
};

#endif // IMAGESDL_H
