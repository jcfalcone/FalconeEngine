#ifndef POLYCOLLIDER_H
#define POLYCOLLIDER_H

#include <collider.h>
#include "../FalconeEngine/mathf.h"

namespace FalconeEngine
{
    namespace Physics
    {
        class PolyCollider : public Collider
        {
		private:
			int vertexCount;
			std::vector<Vector2> vertices;
			std::vector<Vector2> normals;

			float FindAxisLeastPenetration(int *faceIndex, PolyCollider * _other);
			std::vector<Vector2> FindIncidentFace(PolyCollider *RefPoly, PolyCollider *IncPoly, int referenceIndex);
			int Clip(Vector2 normal, float c, std::vector<Vector2> *face);

			Matrix22 matrix;

			HitData lastData;

        public:
			PolyCollider();
            ~PolyCollider();

			void Start() override;
			void Update(float deltaTime) override;
			bool CheckCollision(Collider * other) override;
			HitData CalcHitData(Collider * other) override;
			float CalcMass(float _density) override;
			void Render() override;

			bool SetShape(std::vector<Vector2> *vertices);
			// Half width and half height
			void SetShapeToBox(float width, float height)
			{
				this->vertexCount = 4;
				this->vertices.push_back(Vector2(-width, -height));
				this->vertices.push_back(Vector2(width, -height));
				this->vertices.push_back(Vector2(width, height));
				this->vertices.push_back(Vector2(-width, height));

				this->normals.push_back(Vector2::Up() * -1);
				this->normals.push_back(Vector2::Right());
				this->normals.push_back(Vector2::Up());
				this->normals.push_back(Vector2::Right() * -1);
			}

			Vector2 GetSupport(const Vector2& dir);

			bool CheckCollisionSphere(Collider * other);
			bool CheckCollisionBox(Collider * other);
			bool CheckCollisionPoly(Collider * other);

			HitData HitDataSphere(Collider * other);
			HitData HitDataBox(Collider * other);


			void SetOrient(float radians)
			{
				this->matrix.Set(radians);
			}

			void SetOrientDegree(float degree);

			//Get and Set
			Matrix22 GetMatrix() const
			{
				return this->matrix;
			}

			Matrix22 * GetMatrixRef()
			{
				return &matrix;
			}

			std::vector<Vector2> GetVertices() const
			{
				return this->vertices;
			}

			std::vector<Vector2> * GetVerticesRef()
			{
				return &vertices;
			}

			std::vector<Vector2> GerNormal() const
			{
				return this->normals;
			}

			int GetVerticesCount() const
			{
				return this->vertexCount;
			}

        };
    }
}

#endif // SPHERECOLLIDER_H
