#include "spherecollider.h"

#define _USE_MATH_DEFINES

#include "boxcollider.h"
#include "polycollider.h"
#include "rigidbody.h"

#include <algorithm>
#include <math.h>

namespace FalconeEngine
{
    namespace Physics
    {
		SphereCollider::SphereCollider() : Collider()
        {
        }

		SphereCollider::SphereCollider(float _radius) : Collider()
        {
			this->radius = _radius;
        }

		SphereCollider::~SphereCollider()
        {

        }

		void SphereCollider::Start()
		{
			this->type = "SPHERE";
			//FalconeEngine::ObjectControl::Instance()->getPhysics()->
		}

		void SphereCollider::Update(float deltaTime)
        {
        }

		void SphereCollider::Render()
		{
		}

		float SphereCollider::CalcMass(float _density)
		{
			float radiusCM = this->radius * UNITTOCM;
			float volume = (4.0f / 3.0f) * M_PI * (radiusCM *  radiusCM * radiusCM);

			float mass = _density * volume;

			this->rigidBody->SetMass(mass);
			this->rigidBody->SetInertia(mass * radiusCM * radiusCM);
			return _density * volume;
		}

		bool SphereCollider::CheckCollision(Collider * other)
		{
			if (other->GetType() == "SPHERE")
			{
				return this->CheckCollisionSphere(other);
			}
			else if (other->GetType() == "BOX")
			{
				return this->CheckCollisionBox(other);
			}
			else if (other->GetType() == "POLY")
			{
				return this->CheckCollisionPoly(other);
			}

			return false;
		}

		bool SphereCollider::CheckCollisionSphere(Collider * other)
		{
			if (SphereCollider* collider = dynamic_cast<SphereCollider*>(other))
			{
				FalconeEngine::Vector2 posOther = collider->GetPosition();
				FalconeEngine::Vector2 position = this->GetPosition();

				double deltaX = position.x - posOther.x;
				deltaX *= deltaX;

				double deltaY = position.y - posOther.y;
				deltaY *= deltaY;

				float sumRadius = collider->GetRadius() + this->GetRadius();
				sumRadius *= sumRadius;

				if (deltaX + deltaY <= sumRadius)
				{
					return true;
				}
			}

			return false;
		}

		bool SphereCollider::CheckCollisionBox(Collider * other)
		{
			if (BoxCollider* collider = dynamic_cast<BoxCollider*>(other))
			{
				float distance = collider->SquaredDistPointAABB(this->GetPosition());

				return distance <= (this->radius * this->radius);
			}

			return false;
		}

		bool SphereCollider::CheckCollisionPoly(Collider * other)
		{
			this->lastData.Clear();
			this->lastData.object = this;
			this->lastData.other = other;

			if (PolyCollider* collider = dynamic_cast<PolyCollider*>(other))
			{
				// Transform circle center to Polygon model space
				Vector2 center = this->GetPosition();
				center = collider->GetMatrix().Transpose() * (center - collider->GetPosition());

				// Find edge with minimum penetration
				// Exact concept as using support points in Polygon vs Polygon
				float separation = -FLT_MAX;
				int faceNormal = 0;
				for (int count = 0;count < collider->GetVerticesCount(); ++count)
				{
					float sep = collider->GerNormal()[count].Dot(center - collider->GetVertices()[count]);

					if (sep > this->radius)
						return false;

					if (sep > separation)
					{
						separation = sep;
						faceNormal = count;
					}
				}

				// Grab face's vertices
				Vector2 vertice1 = collider->GetVertices()[faceNormal];
				int count2 = faceNormal + 1 < collider->GetVerticesCount() ? faceNormal + 1 : 0;
				Vector2 vertice2 = collider->GetVertices()[count2];

				// Check to see if center is within polygon
				if (separation < FLT_EPSILON)
				{
					this->lastData.normal = (collider->GetMatrix() * collider->GerNormal()[faceNormal]);
					this->lastData.normal = this->lastData.normal * -1;
					this->lastData.contacts.push_back(this->lastData.normal * this->radius + this->GetPosition());
					this->lastData.penetration = this->radius;
					return true;
				}

				// Determine which voronoi region of the edge center of circle lies within
				Vector2 centerVert1 = center - vertice1;
				Vector2 centerVert2 = center - vertice2;

				float dot1 = centerVert1.Dot(vertice2 - vertice1);
				float dot2 = centerVert2.Dot(vertice1 - vertice2);
				this->lastData.penetration = this->radius - separation;

				// Closest to v1
				if (dot1 <= 0.0f)
				{
					if (center.distanceSqr(vertice1) > this->radius * this->radius)
					{
						return false;
					}

					Vector2 normal = vertice1 - center;
					normal = (collider->GetMatrix() * normal);
					normal = normal.normalize();
					this->lastData.normal = normal;
					vertice1 = collider->GetMatrix() * (vertice1 + collider->GetPosition());
					this->lastData.contacts.push_back(vertice1);
				}
				// Closest to v2
				else if (dot2 <= 0.0f)
				{
					if (center.distanceSqr(vertice2) > this->radius * this->radius)
					{
						return false;
					}

					Vector2 normal = vertice2 - center;
					vertice2 = collider->GetMatrix() * (vertice2 + collider->GetPosition());
					this->lastData.contacts.push_back(vertice2);
					this->lastData.normal = (collider->GetMatrix() * normal);
					this->lastData.normal = this->lastData.normal.normalize();
				}
				// Closest to face
				else
				{
					Vector2 normal = collider->GerNormal()[faceNormal];
					Vector2 centerVertice = center - vertice1;

					if (centerVertice.Dot(normal) > this->radius)
					{
						return false;
					}

					normal = collider->GetMatrix() * normal;
					this->lastData.normal = normal * -1;
					this->lastData.contacts.push_back((this->lastData.normal * this->radius) + this->GetPosition());
				}

				return true;
			}

			return false;
		}

		HitData SphereCollider::CalcHitData(Collider * other)
		{
			if (other->GetType() == "SPHERE")
			{
				return this->HitDataSphere(other);
			}
			else if (other->GetType() == "BOX")
			{
				return this->HitDataBox(other);
			}
			else if (other->GetType() == "POLY")
			{
				return this->lastData;
			}
		}

		HitData SphereCollider::HitDataSphere(Collider * other)
		{
			HitData returnValue;
			returnValue.object = this;
			returnValue.other = other;

			if (SphereCollider* collider = dynamic_cast<SphereCollider*>(other))
			{
				FalconeEngine::Vector2 posOther = collider->GetPosition();
				FalconeEngine::Vector2 position = this->GetPosition();

				FalconeEngine::Vector2 direction = posOther - position;

				float sumRadius = collider->GetRadius() + this->GetRadius();
				sumRadius *= sumRadius;

				double deltaX = position.x - posOther.x;
				deltaX *= deltaX;

				double deltaY = position.y - posOther.y;
				deltaY *= deltaY;

				if (deltaX + deltaY <= sumRadius)
				{
					float dist = direction.length();

					if (dist != 0)
					{
						returnValue.penetration = sumRadius - dist;
						returnValue.normal = direction / dist;
						returnValue.contacts.push_back(returnValue.normal * this->radius + this->parent->getPosition());
					}
					else
					{
						returnValue.penetration = this->GetRadius();
						returnValue.normal = FalconeEngine::Vector2::Up();
						returnValue.contacts.push_back(this->GetPosition());
					}
				}
			}

			return returnValue;
		}

		HitData SphereCollider::HitDataBox(Collider * other)
		{
			HitData returnValue;
			returnValue.object = this;
			returnValue.other = other;

			if (BoxCollider* collider = dynamic_cast<BoxCollider*>(other))
			{
				FalconeEngine::Vector2 posOther = collider->GetPosition();
				FalconeEngine::Vector2 position = this->GetPosition();

				FalconeEngine::Vector2 direction = posOther - position;
				FalconeEngine::Vector2 closest = direction;

				float otherExtentX = (collider->GetMaxAABB().x - collider->GetMinAABB().x) / 2;
				float otherExtentY = (collider->GetMaxAABB().y - collider->GetMinAABB().y) / 2;


				closest.x = std::min(otherExtentX, std::max(closest.x, -otherExtentX));
				closest.y = std::min(otherExtentY, std::max(closest.y, -otherExtentY));

				bool inside = false;

				if (direction == closest)
				{
					inside = true;

					// Find closest axis
					if (std::abs(direction.x) > std::abs(direction.y))
					{
						if (closest.x > 0)
						{
							closest.x = otherExtentX;
						}
						else
						{
							closest.x = -otherExtentX;
						}
					}
					else
					{
						// Clamp to closest extent
						if (closest.y > 0)
						{
							closest.y = otherExtentY;
						}
						else
						{
							closest.y = -otherExtentY;
						}
					}
				}

				FalconeEngine::Vector2 normal = direction - closest;
				float distance = normal.lengthSqrd();
				float radius = this->GetRadius();

				if (distance > radius * radius && !inside)
				{
					return returnValue;
				}

				distance = std::sqrt(distance);

				if (inside)
				{
					returnValue.normal = normal * -1;//normal * -1;
					returnValue.penetration = radius - distance;
				}
				else
				{
					returnValue.normal = normal;
					returnValue.penetration = radius - distance;
				}
			}

			return returnValue;
		}

		HitData SphereCollider::HitDataPoly(Collider * other)
		{
			this->CheckCollisionPoly(other);
			return this->lastData;
		}
    }
}
