#include "boxcollider.h"

#include "spherecollider.h"
#include <cmath>

namespace FalconeEngine
{
    namespace Physics
    {
        BoxCollider::BoxCollider() : Collider()
        {

        }

		BoxCollider::BoxCollider(Vector2 _position, Vector2 _scale, float _size)
		{
			this->minAABB = Vector2(_position.x - (_size / 2 * _scale.x), _position.y - (_size / 2 * _scale.y));
			this->maxAABB = Vector2(_position.x + (_size / 2 * _scale.x), _position.y + (_size / 2 * _scale.y));
		}


		BoxCollider::BoxCollider(Vector2 _min, Vector2 _max): Collider()
        {
			this->minAABB = _min;
			this->maxAABB = _max;
        }

        BoxCollider::~BoxCollider()
        {

        }


		void BoxCollider::Start()
		{
			this->type = "BOX";
			//FalconeEngine::ObjectControl::Instance()->getPhysics()->
		}

        void BoxCollider::Update(const float deltaTime)
        {
        }

		void BoxCollider::Render()
		{
		}

		float BoxCollider::CalcMass(float _density)
		{
			float width = this->maxAABB.x - this->minAABB.x;
			float height = this->maxAABB.y - this->minAABB.y;

            float volume = width * height /** UNITTOCM*/;

			return _density * volume;
		}

		bool BoxCollider::CheckCollision(Collider * other)
		{
			if (other->GetType() == "SPHERE")
			{
				return this->CheckCollisionSphere(other);
			}
			else if (other->GetType() == "BOX")
			{
				return this->CheckCollisionBox(other);
			}

			return false;
		}

		bool BoxCollider::CheckCollisionSphere(Collider * other)
		{
			if (SphereCollider* collider = dynamic_cast<SphereCollider*>(other))
			{
				return collider->CheckCollisionBox(this);
			}

			return false;
		}

		bool BoxCollider::CheckCollisionBox(Collider * other)
		{
			if (BoxCollider* collider = dynamic_cast<BoxCollider*>(other))
			{
				Vector2 minOther = collider->GetMinAABB();
				Vector2 maxOther = collider->GetMaxAABB();

				return	(this->minAABB.x <= maxOther.x && this->maxAABB.x >= minOther.x) &&
						(this->minAABB.y <= maxOther.y && this->maxAABB.y >= minOther.y);
			}

			return false;
		}

		float BoxCollider::DistanceToPosition(const float pn,
											  const float bmin,
											  const float bmax)
		{
			float out = 0;
			float v = pn;

			if (v < bmin)
			{
				float val = (bmin - v);
				out += val * val;
			}

			if (v > bmax)
			{
				float val = (v - bmax);
				out += val * val;
			}

			return out;
		}

		float BoxCollider::SquaredDistPointAABB(const Vector2 & point)
		{
			// Squared distance
			double sq = 0.0;

			sq += this->DistanceToPosition(point.x, this->minAABB.x, this->maxAABB.x);
			sq += this->DistanceToPosition(point.y, this->minAABB.y, this->maxAABB.y);

			return sq;
		}

		HitData BoxCollider::CalcHitData(Collider * other)
		{
			if (other->GetType() == "SPHERE")
			{
				return this->HitDataSphere(other);
			}
			else if (other->GetType() == "BOX")
			{
				return this->HitDataBox(other);
			}
		}

		HitData BoxCollider::HitDataSphere(Collider * other)
		{
			if (SphereCollider* collider = dynamic_cast<SphereCollider*>(other))
			{
				return collider->HitDataBox(this);
			}

			HitData returnValue;
			returnValue.object = this;
			returnValue.other = other;

			return returnValue;
		}

		HitData BoxCollider::HitDataBox(Collider * other)
		{
			HitData returnValue;
			returnValue.object = this;
			returnValue.other = other;

			if (BoxCollider* collider = dynamic_cast<BoxCollider*>(other))
			{
				FalconeEngine::Vector2 posOther = collider->GetPosition();
				FalconeEngine::Vector2 position = this->GetPosition();

				FalconeEngine::Vector2 direction = posOther - position;

				float objExtentX = (this->maxAABB.x - this->minAABB.x) / 2;
				float otherExtentX = (collider->GetMaxAABB().x - collider->GetMinAABB().x) / 2;

				// Calculate overlap on x axis
				float overlapX = objExtentX + otherExtentX - std::abs(direction.x);

				if (overlapX > 0)
				{
					float objExtentY = (this->maxAABB.y - this->minAABB.y) / 2;
					float otherExtentY = (collider->GetMaxAABB().y - collider->GetMinAABB().y) / 2;

					float overlapY = objExtentY + otherExtentY - std::abs(direction.y);

					if (overlapY > 0)
					{
						if (overlapX > overlapY)
						{
							returnValue.normal = FalconeEngine::Vector2::Right();

							if (direction.x < 0)
							{
								returnValue.normal = FalconeEngine::Vector2::Right() * -1;
							}

							returnValue.penetration = overlapX;
						}
						else
						{
							returnValue.normal = FalconeEngine::Vector2::Up();

							if (direction.y < 0)
							{
								returnValue.normal = FalconeEngine::Vector2::Up() * -1;
							}

							returnValue.penetration = overlapY;
						}
					}
				}
			}

			return returnValue;
		}
    }
}
