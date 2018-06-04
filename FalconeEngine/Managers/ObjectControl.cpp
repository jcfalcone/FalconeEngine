#include "ObjectControl.h"
#include "../Physics/Physics.h"

#include "rendertemplate.h"
#include "eventtemplate.h"

#include <chrono>
#include <ctime>

namespace FalconeEngine
{

    ObjectControl *ObjectControl::instance = nullptr;

    ObjectControl::ObjectControl(bool usePhysics, bool useUI, bool useSound): objSequence(0), running(true)
    {
        // use current time as seed for random generator
        std::srand(std::time(0));

        this->objMap = new std::map<int, Object *>();

        this->physicsManager = nullptr;
        this->uiManager      = nullptr;
        this->soundManager   = nullptr;
        this->eventManager   = nullptr;
        this->sceneManager   = nullptr;
        this->gameRenderer   = nullptr;

        if(useSound)
        {
            //this->soundManager = new soundSystem();
        }
    }


    ObjectControl::~ObjectControl()
    {
        auto iterator = this->objMap->begin();
        while(iterator != this->objMap->end())
        {
            iterator->second->OnDestroy();
            iterator = this->objMap->erase(iterator);
        }

        std::cout << "Test: " << this->objMap->size() << std::endl;

        delete this->objMap;

        if(this->physicsManager != nullptr)
        {
            delete this->physicsManager;
        }

        /*if(this->uiManager != nullptr)
        {
            delete this->uiManager;
        }*/

        if(this->soundManager != nullptr)
        {
            delete this->soundManager;
        }

        if(this->gameRenderer != nullptr)
        {
           delete this->gameRenderer;
        }

        if(this->eventManager != nullptr)
        {
            if(!this->eventManager->isQuiting())
            {
                this->eventManager->Quit();
            }

            delete this->eventManager;
        }

        if(this->sceneManager != nullptr)
        {
            delete this->sceneManager;
        }
    }


    void ObjectControl::Add(Object *obj)
    {
        if(!obj)
        {
            return;
        }

        obj->setId(this->objSequence);
        //obj->setParent(this);

        this->objMap->emplace(this->objSequence, obj); // Assuming object ID is of type int

        this->objSequence++;

        if(this->GameStarted)
        {
            obj->Start();
        }
    }

    void ObjectControl::Delete(int objId)
    {
        auto objIte = this->objMap->find(objId);
        objIte->second->OnDestroy();
        this->objMap->erase(objIte);
    }

    void ObjectControl::Start()
    {
        for(auto it = this->objMap->begin(); it != this->objMap->end(); it++)
        {
            it->second->Start();
        }

        this->GameStarted = true;
    }

    int ObjectControl::getTimer()
    {
		auto value = std::chrono::high_resolution_clock::now();
		return value.time_since_epoch().count();
    }

    void ObjectControl::Update(float deltaTime)
    {
		float frameTime = deltaTime / 1000;
		this->fixedTime += frameTime;

        this->updateElapsedTime(frameTime);

        auto iterator = this->objMap->begin();
        while (iterator != this->objMap->end())
        {
            iterator->second->Update(frameTime);

            if (iterator->second->removeObject())
            {
                iterator->second->OnDestroy();
                iterator = this->objMap->erase(iterator);
            }
            else
            {
                iterator++;
            }


        }

        if(this->eventManager != nullptr)
        {
            if(this->eventManager->isQuiting())
            {
                this->exit();
            }
        }

		if (this->fixedTime > FIXEDDELTATIME)
		{
			this->fixedTime = FIXEDDELTATIME;
		}

		while (this->fixedTime > frameTime)
		{
			if (this->physicsManager)
			{
				this->physicsManager->Update(frameTime);
			}

			this->fixedTime -= frameTime;
		}
    }

    void ObjectControl::Render()
    {
        if(this->gameRenderer)
        {
            this->gameRenderer->startRenderer();
        }

        for (auto iterator = this->objMap->begin(); iterator != this->objMap->end(); iterator++)
        {
            iterator->second->Render();
        }

        if(this->physicsManager)
        {
            this->physicsManager->Render();
        }

        if(this->uiManager)
        {
            //this->uiManager->Render();
        }

        if(this->gameRenderer)
        {
            this->gameRenderer->endRenderer();
        }
    }

    void ObjectControl::updateElapsedTime(float deltaTime)
    {
        /*if(this->elapsedTime + deltaTime > FLT_MAX)
        {
            deltaTime = (this->elapsedTime + deltaTime) - FLT_MAX;
            this->elapsedTime = 0;
            this->elapsedTimeCount++;
        }*/

        this->elapsedTime += deltaTime;
    }
}
