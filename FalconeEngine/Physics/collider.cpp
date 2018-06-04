#include "collider.h"
#include "../Managers/ObjectControl.h"

namespace FalconeEngine
{
    namespace Physics
    {
        Collider::Collider() : rigidBody(nullptr)
        {
			FalconeEngine::ObjectControl::Instance()->getPhysics()->AddCollider(this);
        }

        bool Collider::isTrigger() const
        {
            return this->trigger;
        }

        void Collider::setAsTrigger(const bool trigger)
        {
            this->trigger = trigger;
        }

        void Collider::setCenter(const Vector2 _center)
        {
        }

		Vector2 Collider::GetPosition()
		{
			//return Vector2::Zero();
			return this->parent->getPosition();
		}
    }
}
