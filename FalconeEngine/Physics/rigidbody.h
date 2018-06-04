#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "collider.h"
#include "Physics.h"

namespace FalconeEngine
{
    namespace Physics
    {

        class Rigidbody : public Component
        {
		private:
			float Mass;
			float invMass;

			float angularVel;
			float orientation; // radians
			float torque;

			float inertia;
			float inverseInertia;

			PhysicsMaterial material;

			Vector2 velocity;  
			Vector2 force;
			//float gravityScale;
        public:
			Rigidbody();
			Rigidbody(PhysicsMaterial _material);
            ~Rigidbody();

			void Start() override;
			void Update(float deltaTime) override;
			void Render() override;

			void ResolveCollision(class HitData * _hitinfo);
			void ResolveImpulse(class HitData * _hitData);

			//Get and Set
			float GetMass() const
			{
				return this->Mass;
			}

			void SetMass(float _mass)
			{
				this->Mass = _mass;
				this->invMass = 0;

				if (this->Mass > 0)
				{
					this->invMass = 1 / this->Mass;
				}
			}

			void SetInertia(float _inertia)
			{
				this->inertia = _inertia;
				this->inverseInertia = 0;

				if (this->inertia > 0)
				{
					this->inertia = 1 / this->inertia;
				}
			}

			Vector2 GetVelocity() const
			{
				return this->velocity;
			}

			float GetAngularVelocity() const
			{
				return this->angularVel;
			}

			void AddVelocity(Vector2 _add)
			{
				this->velocity = this->velocity + _add;
			}

			void ApplyImpulse(Vector2& impulse, Vector2& contactVector);

			void SetInverseMass(float _inverse)
			{
				this->invMass = _inverse;
			}

			float GetInverseMass()
			{
					return this->invMass;
			}

			float GetInverseInertia()
			{
				return this->inverseInertia;
			}

			float GetRestitution()
			{
				return this->material.restitution;
			}

			float GetFrictionCoef()
			{
				return this->material.frictionCoef;
			}

        };
    }
}

#endif // SPHERECOLLIDER_H
