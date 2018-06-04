#ifndef SCENETEMPLATE_H
#define SCENETEMPLATE_H

#include <string>
#include <list>

namespace FalconeEngine
{
    class Object;

    class SceneTemplate
    {
    protected:
        std::string name;
        std::list<Object *> sceneObjects;
    public:
        SceneTemplate();

        virtual void Start() = 0;
        virtual void OnUnload() = 0;
        virtual void OnLoad() = 0;

        std::string GetName() { return this->name; }

        virtual void AddObject(Object * _obj);
    };
}

#endif // SCENETEMPLATE_H
