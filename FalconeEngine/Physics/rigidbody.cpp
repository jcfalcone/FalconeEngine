#include "rigidbody.h"

#include "boxcollider.h"

#include <algorithm>

namespace FalconeEngine
{
    namespace Physics
    {
		Rigidbody::Rigidbody() : Component(), Mass(0), velocity(Vector2::Zero())
        {
        }

		Rigidbody::Rigidbody(class PhysicsMaterial _material) : Component(), velocity(Vector2::Zero()), material(_material)
        {
        }

		Rigidbody::~Rigidbody()
        {

        }

		void Rigidbody::Start()
		{
			this->parent->setPhysics(true);

			Collider * collider = this->parent->GetComponent<Collider *>("Collider");

			this->Mass = 0;
			this->invMass = 0;

			if (collider != nullptr)
			{
				collider->SetRigidBody(this);

				collider->CalcMass(this->material.density);
			}
		}

		void Rigidbody::Update(float deltaTime)
        {

			if (this->invMass > FLT_EPSILON)
			{
				//Resolve velocity
				this->parent->setPosition(this->parent->getPosition() + this->velocity);

				Vector2 addVel = this->velocity + this->force;
				addVel.y += GRAVITY;

				this->velocity = this->velocity + (addVel * deltaTime);

				//Resolve Rotation
				float rotation = this->parent->getRotation();
				rotation += this->angularVel * deltaTime;

				this->parent->setRotation(rotation);

				this->angularVel += this->torque * this->inverseInertia * deltaTime;
			}
			else
			{
				this->velocity = Vector2::Zero();
			}
        }

		void Rigidbody::Render()
		{
		}

		void Rigidbody::ResolveCollision(HitData * _hitinfo)
		{
			Rigidbody * otherRB = _hitinfo->other->GetRigidBody();

			if (otherRB == nullptr)
			{
				return;
			}

			Vector2 resolve = otherRB->GetVelocity() - this->velocity;

			float velAlongNormal = resolve.Dot(_hitinfo->normal.normalize());

			if (velAlongNormal > 0)
			{
				return;
			}

			float restitution = std::min(this->GetRestitution(), otherRB->GetRestitution());

			float impulse = -(1 + restitution) * velAlongNormal;
			impulse /= (this->invMass + otherRB->GetInverseMass());

			Vector2 impulseVec = _hitinfo->normal.normalize() * impulse;

			float massSum = this->GetMass() + otherRB->GetMass();
			float ratio = this->GetMass() / massSum;

			Vector2 velObj = impulseVec * ratio * -1;

			this->AddVelocity(velObj);
			ratio = otherRB->GetMass() / massSum;

			Vector2 velOther = impulseVec * ratio;

			otherRB->AddVelocity(impulseVec * ratio);

			Vector2 relativeVelocity = velObj - velOther;

			// Solve for the tangent vector
			Vector2 tangent = (relativeVelocity - _hitinfo->normal ) * relativeVelocity.Dot(_hitinfo->normal);
			tangent = tangent.normalize();

			// Solve for magnitude to apply along the friction vector
			float impulseTangent = relativeVelocity.Dot(tangent);
			impulseTangent /= (this->GetInverseMass() + otherRB->GetInverseMass());

			float mu = std::sqrt(this->GetFrictionCoef() * this->GetFrictionCoef() + otherRB->GetFrictionCoef() * otherRB->GetFrictionCoef());

			Vector2 friction = Vector2::Zero();

			if (std::abs(impulseTangent) < impulse * mu)
			{
				friction = tangent * impulseTangent;
			}
			else
			{
				float dynamicFriction = std::sqrt(this->GetFrictionCoef() * this->GetFrictionCoef() * 0.5f + otherRB->GetFrictionCoef() * otherRB->GetFrictionCoef() * 0.5f);
				friction = tangent * -impulse * dynamicFriction;
			}

			this->AddVelocity(friction * this->GetInverseMass());
			otherRB->AddVelocity(friction * otherRB->GetInverseMass());
		}

		void Rigidbody::ResolveImpulse(HitData * _hitData)
		{
			Rigidbody * otherRB = _hitData->other->GetRigidBody();

			if (otherRB == nullptr)
			{
				return;
			}

			int countContact = _hitData->contacts.size();

			for (int count = 0; count < countContact; ++count)
			{
				Vector2 radiiObj = _hitData->contacts[count] - this->parent->getPosition();
				Vector2 radiiOther = _hitData->contacts[count] - _hitData->other->GetParent()->getPosition();

				// Relative velocity
				Vector2 rVel = otherRB->GetVelocity() + radiiOther.CrossInverse(otherRB->GetAngularVelocity()) -
							   this->GetVelocity() - radiiObj.CrossInverse(this->GetAngularVelocity());

				float contactVel = rVel.Dot(_hitData->normal);

				if (contactVel > 0)
				{
					return;
				}

				float crossObj	 = radiiObj.Cross(_hitData->normal);
				float crossOther = radiiOther.Cross(_hitData->normal);

				float sumInv = this->invMass + otherRB->GetInverseMass() + std::sqrt(crossObj) * this->inverseInertia + std::sqrt(crossOther) * otherRB->GetInverseMass();

				float restitution = std::min(this->GetRestitution(), otherRB->GetRestitution());

				float impulseS = -(1 + restitution) * contactVel;
				impulseS /= sumInv;
				impulseS /= (float)countContact;

				Vector2 impulse = _hitData->normal * impulseS;
				this->ApplyImpulse(impulse * -1, radiiObj);
				otherRB->ApplyImpulse(impulse, radiiOther);

				//Friction
				rVel = otherRB->GetVelocity() + radiiOther.CrossInverse(otherRB->GetAngularVelocity()) -
						this->GetVelocity() - radiiObj.CrossInverse(this->GetAngularVelocity());

				Vector2 tangent = rVel - (_hitData->normal * rVel.Dot(_hitData->normal));
				tangent = tangent.normalize();

				float tanMag = rVel.Dot(tangent) * -1;
				tanMag /= sumInv;
				tanMag /= (float)countContact;

				if (tanMag == 0)
				{
					return;
				}

				float mu = std::sqrt(this->GetFrictionCoef() * this->GetFrictionCoef() + otherRB->GetFrictionCoef() * otherRB->GetFrictionCoef());

				Vector2 tangentImpulse;

				if (std::abs(tanMag) < impulseS * mu)
				{
					tangentImpulse = tangent * tanMag;
				}
				else
				{
					float dynamicFriction = std::sqrt(this->GetFrictionCoef() * this->GetFrictionCoef() * 0.5f + otherRB->GetFrictionCoef() * otherRB->GetFrictionCoef() * 0.5f);
					tangentImpulse = tangent * (impulse * -1) * dynamicFriction;
				}

				this->ApplyImpulse(tangentImpulse * -1, radiiObj);
				this->ApplyImpulse(tangentImpulse, radiiOther);
			}
		}

		void Rigidbody::ApplyImpulse(Vector2& impulse, Vector2& contactVector)
		{
			velocity += impulse * this->invMass;
			this->angularVel += impulse.Cross(contactVector) * this->inverseInertia;
		}
    }
}
