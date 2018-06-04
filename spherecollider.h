#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include <collider.h>

namespace FalconeEngine
{
    namespace Physics
    {
        class SphereCollider : public Collider
        {
		private:
			float radius;

			HitData lastData;
        public:
			SphereCollider();
			SphereCollider(float _radius);
            ~SphereCollider();

			void Start() override;
			void Update(float deltaTime) override;
			bool CheckCollision(Collider * other) override;
			HitData CalcHitData(Collider * other) override;
			float CalcMass(float _density) override;
			void Render() override;

			bool CheckCollisionSphere(Collider * other);
			bool CheckCollisionBox(Collider * other);
			bool CheckCollisionPoly(Collider * other);

			HitData HitDataSphere(Collider * other);
			HitData HitDataBox(Collider * other);
			HitData HitDataPoly(Collider * other);

			//Get and Set
			float GetRadius() const
			{
				return this->radius;
			}

        };
    }
}

#endif // SPHERECOLLIDER_H
