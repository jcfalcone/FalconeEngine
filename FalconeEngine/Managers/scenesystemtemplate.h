#ifndef SCENESYSTEMTEMPLATE_H
#define SCENESYSTEMTEMPLATE_H

#include <map>
#include <string>


namespace FalconeEngine
{
    class SceneTemplate;

    class SceneSystemTemplate
    {
        private:
            std::map<std::string, SceneTemplate *> listScenes;

            std::string currScene;
        public:
            SceneSystemTemplate();
            ~SceneSystemTemplate();

            virtual void AddScene(SceneTemplate * _scene);
            virtual bool LoadScene(std::string _sceneName);
    };
}

#endif // SCENETEMPLATE_H
