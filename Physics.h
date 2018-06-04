#ifndef PHYSICS
#define PHYSICS

#include<vector>
#include "collider.h"

#define GRAVITY -9.8f

class Object;

namespace FalconeEngine
{
    namespace Physics
    {
		class HitData
		{
		public:
			class Collider * object = nullptr;
			class Collider * other = nullptr;
			float penetration = 0;
			Vector2 normal = FalconeEngine::Vector2::Zero();

			std::vector<Vector2> contacts;

			void Clear()
			{
				object = nullptr;
				other = nullptr;
				penetration = 0;
				normal = FalconeEngine::Vector2::Zero();

				contacts.clear();
			}
		};


		class PhysicsMaterial
		{
		public:
			float density;
			float restitution;
			float frictionCoef;

			static PhysicsMaterial Rock()
			{
				PhysicsMaterial temp;

				temp.density = 0.6f;
				temp.restitution = 0.1f;
				temp.frictionCoef = 0.6f;

				return temp;
			}

			static PhysicsMaterial Wood()
			{
				PhysicsMaterial temp;

				temp.density = 0.3f;
				temp.restitution = 0.2f;
				temp.frictionCoef = 0.2f;

				return temp;
			}

			static PhysicsMaterial Metal()
			{
				PhysicsMaterial temp;

				temp.density = 1.2f;
				temp.restitution = 0.05f;
				temp.frictionCoef = 1.0f;

				return temp;
			}

			static PhysicsMaterial BouncyBall()
			{
				PhysicsMaterial temp;

				temp.density = 0.3f;
				temp.restitution = 0.8f;
				temp.frictionCoef = 0.7f;

				return temp;
			}

			static PhysicsMaterial SuperBall()
			{
				PhysicsMaterial temp;

				temp.density = 0.3f;
				temp.restitution = 0.95f;
				temp.frictionCoef = 0.8f;

				return temp;
			}

			static PhysicsMaterial Pillow()
			{
				PhysicsMaterial temp;

				temp.density = 0.1f;
				temp.restitution = 0.2f;
				temp.frictionCoef = 0.26f;

				return temp;
			}

			static PhysicsMaterial Static()
			{
				PhysicsMaterial temp;

				temp.density = 0.0f;
				temp.restitution = 0.4f;
				temp.frictionCoef = 0.5f;

				return temp;
			}
		};

        class Physics
        {
        protected:
			std::vector<class Collider *> * colliderList;

        public:
            Physics();
            ~Physics();

            void Update(float deltaTime);

            void Render();

			void AddCollider(class Collider * _collider);
			void PositionalCorrection(HitData _data);
        };
    }
}

#endif // !PHYSICS
