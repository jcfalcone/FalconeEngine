#ifndef OBJECTCONTROL
#define OBJECTCONTROL

#include <map>
#include "../Core/Object.h"
#define FIXEDDELTATIME 0.2f
#define UNITTOCM 0.026

namespace FalconeEngine
{
    namespace Physics
    {
        class Physics;
    }

    class UITemplate;
    class soundSystem;
    class renderTemplate;
    class eventTemplate;
    class SceneSystemTemplate;
	class Object;

    class ObjectControl
    {
    private:
        int objSequence;
        std::map<int, Object *> * objMap;

        int elapsedTimeCount;
        float elapsedTime;
		float fixedTime;

        bool running;
        bool GameStarted = false;

        Physics::Physics * physicsManager;
        UITemplate * uiManager;
        soundSystem * soundManager;
        renderTemplate * gameRenderer;
        eventTemplate * eventManager;
        SceneSystemTemplate * sceneManager;

        static ObjectControl *instance;

    public:
        static ObjectControl* Instance()
        {
            if(instance == nullptr)
            {
                instance = new ObjectControl(false, false, false);
            }

            return instance;
        }

        ObjectControl(bool usePhysics, bool useUI, bool useSound);
        ~ObjectControl();

        std::string path() { return "/Users/juliocesarsoaresfalconecunha/Documents/College/Term2/CPlusPlus/build-CrazyEight-Desktop_Qt_5_8_0_clang_64bit-Profile/"; }

        void Add(Object *obj);
        void Delete(int objId);
        void Start();
        void Update(float deltaTime);
        void Render();

        void updateElapsedTime(float deltaTime);
        void SetRenderer(renderTemplate * render) { this->gameRenderer = render; }
		void SetPhysics(Physics::Physics * _physics) { this->physicsManager = _physics; }
        void SetEventSystem(eventTemplate * event) { this->eventManager = event; }
        void SetUISystem(UITemplate * _ui) { this->uiManager = _ui; }
        void SetSceneSystem(SceneSystemTemplate * _scene) { this->sceneManager = _scene; }

        int getTimer();
        float getElapsedTime() { return this->elapsedTime; }

		Physics::Physics * getPhysics() { return this->physicsManager; }
        UITemplate * getUISystem() { return this->uiManager; }
        soundSystem * getSoundSystem() { return this->soundManager; }
        renderTemplate * getRender() { return this->gameRenderer; }
        eventTemplate * getEventSystem() { return this->eventManager; }
        SceneSystemTemplate * GetSceneSystem() { return this->sceneManager; }

        template<typename T>
        T FindElementById(int _id)
        {
            return (T)&this->objMap[_id];
        }

        template<typename T>
        T FindElementByName(std::string _name);

        template<typename T>
        T FindElementByTag(std::string _tag);

        bool isRunning() { return this->running; }

        void exit() { this->running = false; }
    };
}

#endif // !OBJECTCONTROL
