#include "Object.h"

#include <algorithm>

#include "../Managers/ObjectControl.h"
#include "Component.h"

namespace FalconeEngine
{
	/*Object::Object() : speed(0.03f), rotation(0), destroyTime(0), visible(true), physics(true), destroy(false), position(Vector2(0, 0)), scale(Vector2(1, 1)), name("Unknown"), parent(nullptr)
	{
	}*/

    Object::Object(std::string _name, Object * _parent): rotation(0), destroyTime(0), visible(true), physics(true), destroy(false), /*parent(nullptr),*/ position(Vector2(0,0)), scale(Vector2(1,1)), name(_name), parent(_parent)
    {
		if (_parent != nullptr)
		{
			_parent->AddChild(_name, this);
		}
    }

    Object::Object(Vector2 pos, Vector2 scl) : position(pos), scale(scl), rotation(0), destroyTime(0), visible(true), physics(true)/*, parent(nullptr)*/, name("Unknown")
    {
    }


    Object::~Object()
    {
    }

    void Object::setId(int id)
    {
        this->objID = id;

        if(this->name == "Unknown")
        {
            this->name = "object_"+id;
        }
    }

    int Object::SetSequence(int _sequence)
    {
        this->sequence = _sequence;
        ObjectControl::Instance()->SortObjects();
    }

    void Object::setPosition(Vector2 pos)
    {
        this->position = pos;
    }

    void Object::setScale(Vector2 scl)
    {
        this->scale = scl;
    }
    void Object::setRotation(float rot)
    {
        this->rotation = rot;
    }

    void Object::setTag(std::string tg)
    {
        this->tag = tg;
    }

    void Object::setDestroy(bool destroyObj)
    {
        this->destroy = destroyObj;
    }

    void Object::setVisible(bool vis)
    {
        this->visible = vis;
    }
    void Object::setPhysics(bool phys)
    {
        this->physics = phys;
    }

    void Object::DestroyTime(float time)
    {
        this->destroyTime = time;
        //this->startDestTime = this->parent->getElapsedTime();
    }

	bool Object::AddChild(std::string _id, Object * _child)
	{
		std::hash<std::string> hash_fn;

		size_t hash = hash_fn(_id);

		auto it = this->components.find(hash);

		if (it != this->components.end())
		{
			return false;
		}

		this->child[hash] = _child;
	}

	void Object::RemoveChild(std::string _id)
	{
		std::hash<std::string> hash_fn;
		this->child.erase(hash_fn(_id));
	}

	bool Object::AddComponent(std::string _id, Component * _component)
	{
		std::hash<std::string> hash_fn;

		size_t hash = hash_fn(_id);

		auto it = this->components.find(hash);

		if (it != this->components.end())
		{
			return false;
		}

		this->components.insert(std::pair<size_t, Component *>(hash, _component));

		_component->SetParent(this);
        _component->Start();

		return true;
	}

	void Object::RemoveComponent(std::string _id)
	{
		std::hash<std::string> hash_fn;
		this->components.erase(hash_fn(_id));
	}

	void Object::Start()
	{
        //this->StartComponents();
	}

	void Object::StartComponents()
	{
		if (this->components.size() <= 0)
		{
			return;
		}

		std::for_each(this->components.begin(), this->components.end(), [](std::pair<const size_t, Component *> & _comp)
		{
			_comp.second->Start();
		});
	}

    void Object::Update(float deltaTime)
    {
        if (this->destroyTime != 0)
        {
            if (this->startDestTime > this->destroyTime)
            {
                this->setDestroy(true);
                //this->parent->Delete(this->objID);
            }

			this->startDestTime += deltaTime;
        }

		this->UpdateComponents(deltaTime);
    }

	void Object::UpdateComponents(float deltaTime)
	{
		if (this->components.size() <= 0)
		{
			return;
		}

		std::for_each(this->components.begin(), this->components.end(), [deltaTime](std::pair<const size_t, Component *> & _comp)
		{ 
			_comp.second->Update(deltaTime); 
		});
	}


	void Object::Render()
	{
		this->RenderComponents();
	}

	void Object::RenderComponents()
	{
		if (this->components.size() <= 0)
		{
			return;
		}

		std::for_each(this->components.begin(), this->components.end(), [](std::pair<const size_t, Component *> & _comp)
		{
			_comp.second->Render();
		});
	}


	void Object::OnDestroy()
	{
		std::for_each(this->child.begin(), this->child.end(), [](std::pair<const size_t, Object *> & _comp)
		{
			_comp.second->setDestroy(true);
		});
	}
}
