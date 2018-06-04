#include "scenetemplate.h"
#include "ObjectControl.h"

namespace FalconeEngine
{
    SceneTemplate::SceneTemplate()
    {

    }

    void SceneTemplate::AddObject(Object * _obj)
    {
        this->sceneObjects.push_back(_obj);
        FalconeEngine::ObjectControl::Instance()->Add(_obj);
    }
}
