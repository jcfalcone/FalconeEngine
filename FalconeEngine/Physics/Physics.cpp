#include "Physics.h"
#include "../Core/Object.h"

#include "collider.h"

#include <string>
#include <algorithm>
#include "rigidbody.h"

namespace FalconeEngine
{
    namespace Physics
    {
        Physics::Physics()
        {
             this->colliderList =  new std::vector<Collider *>();
        }


        Physics::~Physics()
        {
            delete this->colliderList;
        }

        void Physics::Update(float deltaTime)
        {
            for (int count = 0; count < this->colliderList->size(); count++)
            {
				for (int count2 = count + 1; count2 < this->colliderList->size(); count2++)
				{
					Collider * object = this->colliderList->at(count);
					Collider * other = this->colliderList->at(count2);

					if (object->CheckCollision(other))
					{
						if (this->colliderList->at(count)->GetType() == "SPHERE")
						{
							std::cout << "PT1" << std::endl;
						}

						HitData hitData = object->CalcHitData(other);
						Rigidbody * rigidBody = object->GetRigidBody();

						if (rigidBody != nullptr)
						{
							rigidBody->ResolveCollision(&hitData);
							rigidBody->ResolveImpulse(&hitData);
							this->PositionalCorrection(hitData);
						}
					}
				}
            }
        }

        void Physics::Render()
        {
        }

		void Physics::AddCollider(Collider * _collider)
		{
			this->colliderList->push_back(_collider);
		}

		void Physics::PositionalCorrection(HitData _data)
		{
			if (_data.object->GetRigidBody()->GetInverseMass() == 0 && _data.other->GetRigidBody()->GetInverseMass() == 0)
			{
				return;
			}

			float percent = 0.05;
			float slop = 0.01;
            Vector2 correction = _data.normal * std::max(_data.penetration - slop, 0.0f) / (_data.object->GetRigidBody()->GetInverseMass() + _data.other->GetRigidBody()->GetInverseMass()) * percent;
			Vector2 objPosition = _data.object->GetPosition();
			Vector2 otherPosition = _data.other->GetPosition();

			_data.object->GetParent()->setPosition(objPosition - correction * _data.object->GetRigidBody()->GetInverseMass());
			_data.other->GetParent()->setPosition(otherPosition - correction * _data.other->GetRigidBody()->GetInverseMass());
		}
    }
}
