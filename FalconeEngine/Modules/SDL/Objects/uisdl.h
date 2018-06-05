#ifndef UISDL_H
#define UISDL_H

#include "../../../Core/Component.h"
#include <string>

class UISDL : public FalconeEngine::Component
{
public:
    UISDL();

    void Start() override;
    void Update(float _deltaTime) override;
    void Render() override;
};

#endif // UISDL_H
