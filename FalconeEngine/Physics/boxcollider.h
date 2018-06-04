#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "collider.h"
#include "../Core/Vector2.h"

namespace FalconeEngine
{
    namespace Physics
    {
        class BoxCollider : public Collider
        {
		private:
			Vector2 minAABB;
			Vector2 maxAABB;
        public:
            BoxCollider();
			BoxCollider(Vector2 _position, Vector2 _scale, float _size);
            BoxCollider(Vector2 _min, Vector2 _max);
            ~BoxCollider();

			void Start() override;
			void Update(float deltaTime) override;
			bool CheckCollision(Collider * other) override;
			HitData CalcHitData(Collider * other) override;
			float CalcMass(float _density) override;
			void Render() override;

			float DistanceToPosition(const float pn,
									 const float bmin,
									 const float bmax);

			float SquaredDistPointAABB(const Vector2 & p);

			bool CheckCollisionSphere(Collider * other);
			bool CheckCollisionBox(Collider * other);

			HitData HitDataSphere(Collider * other);
			HitData HitDataBox(Collider * other);

			//Get and Set
			Vector2 GetMinAABB() 
			{
				return this->minAABB;
			}

			Vector2 GetMaxAABB()
			{
				return this->maxAABB;
			}

        };
    }
}

#endif // BOXCOLLIDER_H
