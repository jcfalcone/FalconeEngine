#ifndef UISDL_H
#define UISDL_H

#include "../../../Core/Component.h"

class UISDL : public FalconeEngine::Component
{
public:
    UISDL();

    void Start() override;
    void Update(float _deltaTime) override;
    void Render() override;

    void SetPath(std::string _path);
};

#endif // UISDL_H
