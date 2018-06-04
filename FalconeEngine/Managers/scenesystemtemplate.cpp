#include "scenesystemtemplate.h"

#include <iostream>

#include "scenetemplate.h"

namespace FalconeEngine
{
    SceneSystemTemplate::SceneSystemTemplate()
    {
        this->currScene = "";
    }

    SceneSystemTemplate::~SceneSystemTemplate()
    {

        if(this->currScene.length() > 0)
        {
            this->listScenes[this->currScene]->OnUnload();
        }

        auto iterator = this->listScenes.begin();

        while(iterator != this->listScenes.end())
        {
            iterator = this->listScenes.erase(iterator);
        }
    }

    void SceneSystemTemplate::AddScene(SceneTemplate * _scene)
    {
        this->listScenes[_scene->GetName()] = _scene;

        _scene->Start();
    }

    bool SceneSystemTemplate::LoadScene(std::string _sceneName)
    {
        auto it = this->listScenes.find(_sceneName);

        if(it == this->listScenes.end())
        {
            std::cerr << "Level " << _sceneName << " not found " << std::endl;
            return false;
        }

        if(this->currScene.length() > 0)
        {
            this->listScenes[this->currScene]->OnUnload();
        }

        this->listScenes[_sceneName]->OnLoad();
        this->currScene = _sceneName;
        return true;
    }
}
