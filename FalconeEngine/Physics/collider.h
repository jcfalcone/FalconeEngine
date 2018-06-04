#ifndef COLLIDER_H
#define COLLIDER_H

#include <Object.h>
#include <Physics.h>
#include "Vector2.h"
#include "Component.h"
#include <rect.h>
#include <string>

namespace FalconeEngine
{
    namespace Physics
    {
        class Collider : public Component
        {
        protected:
            bool trigger;
			std::string type;
			class Rigidbody * rigidBody;

        public:
            Collider();

			virtual bool CheckCollision(Collider * other) = 0;
			
			virtual class HitData CalcHitData(Collider * other) = 0;

			virtual float CalcMass(float _density) = 0;

            bool isTrigger() const;

			//Set and Get
            void setAsTrigger(const bool trigger);
            void setCenter(const Vector2 _center);
			
			std::string GetType() 
			{
				return this->type;
			}

			Vector2 GetPosition();

			class Rigidbody * GetRigidBody()
			{
				return this->rigidBody;
			}

			void SetRigidBody(class Rigidbody * _rigidBody)
			{
				this->rigidBody = _rigidBody;
			}
        };
    }
}

#endif // COLLIDER_H
