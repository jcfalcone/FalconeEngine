#ifndef OBJECT
#define OBJECT

#include <string>
#include <map>

#include "../stdafx.h"

#include "Vector2.h"
#include "behavior.h"
#include "Component.h"

namespace FalconeEngine
{
    class Object: public Behavior
    {
    private:
        float	destroyTime;
        float	startDestTime;
        bool	destroy;
        bool    physics;
    protected:
        Vector2 position;
        Vector2 scale;
        float	rotation;

        bool	visible;

        int		objID;

        std::string tag;
        std::string name;

		Object * parent;

		std::map<size_t, Component *> components;
		std::map<size_t, Object *> child;

        //FalconeEngine::ObjectControl * parent;

    public:
		//Object();
        Object(std::string _name, Object * _parent);
        Object(class Vector2 pos, class Vector2 scl);
        ~Object();

        //void setParent(FalconeEngine::ObjectControl * prt) { this->parent = prt; }

        void setId(int id);

        void setPosition(class Vector2 pos);
        void setScale(class Vector2 scl);
        void setRotation(float rot);
        void setTag(std::string tg);
        void setDestroy(bool destroyObj);
        void setVisible(bool vis);
        void setPhysics(bool phys);

        bool removeObject() { return this->destroy; }

        int getId() const { return this->objID; }

        std::string GetName() const { return this->name; }

        class Vector2 getPosition(){ return this->position; }

        class Vector2 getScale(){	return this->scale;}

		float getRotation() const { return this->rotation; }

        std::string getTag() { return this->tag; }

        bool getDestroy() { return this->destroy;  }

        bool isVisible() { return this->visible; }
        bool hasPhysics() { return this->physics; }

        void DestroyTime(float time);

		bool AddChild(std::string _id, Object * _child);
		void RemoveChild(std::string _id);

		Object * GetComponent(std::string _id)
		{
			std::hash<std::string> hash_fn;

			auto interator = this->child.find(hash_fn(_id));

			if (interator != this->child.end())
			{
				return interator->second;
			}

			return nullptr;
		};

		bool AddComponent(std::string _id, Component * _component);
		void RemoveComponent(std::string _id);

		template<typename Type>
		Type GetComponent(std::string _id)
		{
			std::hash<std::string> hash_fn;

			if (Type j = dynamic_cast<Type>(this->components[hash_fn(_id)]))
			{
				return j;
			}

			return nullptr;
		};

        virtual void Start();

		virtual void Object::StartComponents();

        virtual void Update(float deltaTime);

		virtual void UpdateComponents(float deltaTime);

        virtual void Render();

		virtual void RenderComponents();

        //virtual void OnCollision(Object * collision) = 0;

        virtual void OnDestroy();
    };
}
#endif
