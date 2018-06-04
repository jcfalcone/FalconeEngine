#include "polycollider.h"

#define _USE_MATH_DEFINES

#include "spherecollider.h"
#include "boxcollider.h"

#include "../Core/Vector2.h"
#include "rigidbody.h"

#include <algorithm>
#include <math.h>

namespace FalconeEngine
{
    namespace Physics
    {
		PolyCollider::PolyCollider() : Collider()
        {
        }

		PolyCollider::~PolyCollider()
        {

        }

		void PolyCollider::Start()
		{
			this->type = "POLY";
			//FalconeEngine::ObjectControl::Instance()->getPhysics()->
		}

		void PolyCollider::Update(float deltaTime)
        {
        }

		void PolyCollider::Render()
		{
		}


		void PolyCollider::SetOrientDegree(float degree)
		{
			float radians = (degree * M_PI) / 180;
			this->SetOrient(radians);
		}

		float PolyCollider::CalcMass(float _density)
		{
			// Calculate centroid and moment of interia
			Vector2 center(0.0f, 0.0f); // centroid
			float area = 0.0f;
			float I = 0.0f;
			float k_inv3 = 1.0f / 3.0f;

			for (int count = 0; count < this->vertexCount; ++count)
			{
				// Triangle vertices, third vertex implied as (0, 0)
				Vector2 point1(this->vertices[count]);
				int count2 = count + 1 < this->vertexCount ? count + 1 : 0;
				Vector2 point2(this->vertices[count2]);

				float crossPoint = point1.Cross(point2);
				float triangleArea = 0.5f * crossPoint;

				area += triangleArea;

				// Use area to weight the centroid average, not just vertex position
				center = center + (point1 + point2) * triangleArea * k_inv3;

				float intx2 = point1.x * point1.x + point2.x * point1.x + point2.x * point2.x;
				float inty2 = point1.y * point1.y + point2.y * point1.y + point2.y * point2.y;
				I += (0.25f * k_inv3 * crossPoint) * (intx2 + inty2);
			}

			center = center * (1.0f / area);

			// Translate vertices to centroid (make the centroid (0, 0)
			// for the polygon in model space)
			// Not really necessary, but I like doing this anyway
			for (int count = 0; count < this->vertexCount; ++count)
			{
				this->vertices[count] = this->vertices[count] - center;
			}

			this->rigidBody->SetMass(_density * area);
			this->rigidBody->SetInertia(I * _density);

			return _density * area;
		}

		bool PolyCollider::SetShape(std::vector<Vector2> *vertices)
		{
			int sizeVert = vertices->size();

			if (sizeVert < 2)
			{
				return false;
			}

			// Find the right most point on the hull
			int rightMost = 0;
			float highestXCoord = vertices->at(0).x;

			for (int count = 1; count < sizeVert; ++count)
			{
				Vector2 vertice = vertices->at(count);
				float x = vertice.x;

				if (x > highestXCoord)
				{
					highestXCoord = x;
					rightMost = count;
				}
				else if (x == highestXCoord)
				{
					if (vertice.y < vertice.y)
					{
						rightMost = count;
					}
				}
			}

			std::vector<int> hull;
			int outCount = 0;
			int indexHull = rightMost;

			for (;;)
			{
				hull[outCount] = indexHull;

				int nextHullIndex = 0;
				for (int count = 1; count < sizeVert; ++count)
				{
					if (nextHullIndex == indexHull)
					{
						nextHullIndex = count;
						continue;
					}

					Vector2 e1 = vertices->at(nextHullIndex) - vertices->at(hull[outCount]);
					Vector2 e2 = vertices->at(count) - vertices->at(hull[outCount]);
					float c = e1.Cross(e2);

					if (c < 0.0f)
					{
						nextHullIndex = count;
					}

					if (c == 0.0f && e2.lengthSqrd() > e1.lengthSqrd())
						nextHullIndex = count;
				}

				++outCount;
				indexHull = nextHullIndex;

				// Conclude algorithm upon wrap-around
				if (nextHullIndex == rightMost)
				{
					this->vertexCount = outCount;
					break;
				}
			}

			for (int count = 0; count < this->vertexCount; ++count)
			{
				this->vertices.push_back(vertices->at(hull[count]));
			}

			// Compute face normals
			for (int count = 0; count < this->vertexCount; ++count)
			{
				int count2 = count + 1 < this->vertexCount ? count + 1 : 0;
				Vector2 face = this->vertices[count2] - this->vertices[count];

				// Calculate normal with 2D cross product between vector and scalar
				this->normals[count] = Vector2(face.y, -face.x).normalize();
			}
		}

		// The extreme point along a direction within a polygon
		Vector2 PolyCollider::GetSupport(const Vector2& dir)
		{
            //float bestProjection = -FLT_MAX;
			Vector2 bestVertex;

            /*for (int count = 0; count < this->vertexCount; ++count)
			{
				Vector2 vertice = this->vertices[count];
				float projection = vertice.Dot(dir);

				if (projection > bestProjection)
				{
					bestVertex = vertice;
					bestProjection = projection;
				}
            }*/

			return bestVertex;
		}

		bool PolyCollider::CheckCollision(Collider * other)
		{
			if (other->GetType() == "SPHERE")
			{
				return this->CheckCollisionSphere(other);
			}

			return false;
		}

		bool PolyCollider::CheckCollisionSphere(Collider * other)
		{
			if (SphereCollider* collider = dynamic_cast<SphereCollider*>(other))
			{
				collider->CheckCollisionPoly(this);
			}

			return false;
		}

		bool PolyCollider::CheckCollisionBox(Collider * other)
		{

			return false;
		}

		bool PolyCollider::CheckCollisionPoly(Collider * other)
		{
			this->lastData.Clear();
			this->lastData.object = this;
			this->lastData.other = other;

            /*if (PolyCollider* collider = dynamic_cast<PolyCollider*>(other))
			{
				// Check for a separating axis with A's face planes
				int faceA;
				float penetrationA = this->FindAxisLeastPenetration(&faceA, collider);
				if (penetrationA >= 0.0f)
				{
					return false;
				}

				// Check for a separating axis with B's face planes
				int faceB;
				float penetrationB = FindAxisLeastPenetration(&faceB, collider);
				
				if (penetrationB >= 0.0f)
				{
					return false;
				}

				int referenceIndex;
				bool flip; // Always point from a to b

				PolyCollider *RefPoly; // Reference
				PolyCollider *IncPoly; // Incident

									   // Determine which shape contains reference face
				if (penetrationA >= penetrationB * 0.95f + penetrationA * 0.01f)
				{
					RefPoly = this;
					IncPoly = collider;
					referenceIndex = faceA;
					flip = false;
				}
				else
				{
					RefPoly = collider;
					IncPoly = this;
					referenceIndex = faceB;
					flip = true;
				}

				// World space incident face
				std::vector<Vector2> incidentFace;
				incidentFace = this->FindIncidentFace(RefPoly, IncPoly, referenceIndex);

				// Setup reference face vertices
				Vector2 vertice1 = RefPoly->GetVertices()[referenceIndex];
				referenceIndex = referenceIndex + 1 == RefPoly->GetVerticesCount() ? 0 : referenceIndex + 1;
				Vector2 vertice2 = RefPoly->GetVertices()[referenceIndex];

				// Transform vertices to world space
				vertice1 = RefPoly->GetMatrix() * (vertice1 + RefPoly->GetPosition());
				vertice2 = RefPoly->GetMatrix() * (vertice1 + RefPoly->GetPosition());

				// Calculate reference face side normal in world space
				Vector2 sidePlaneNormal = (vertice2 - vertice1).normalize();

				// Orthogonalize
				Vector2 refFaceNormal(sidePlaneNormal.y, -sidePlaneNormal.x);

				// ax + by = c
				// c is distance from origin
				float refC = refFaceNormal.Dot(vertice1);
				float negSide = sidePlaneNormal.Dot(vertice1) * -1;
				float posSide = sidePlaneNormal.Dot(vertice2);

				// Clip incident face to reference face side planes
				if (this->Clip(sidePlaneNormal * -1, negSide, &incidentFace) < 2)
					return false; // Due to floating point error, possible to not have required points

				if (Clip(sidePlaneNormal, posSide, &incidentFace) < 2)
					return false; // Due to floating point error, possible to not have required points

				this->lastData.normal = flip ? refFaceNormal * -1 : refFaceNormal;

				// Keep points behind reference face
				int cp = 0; // clipped points behind reference face
				float separation = refFaceNormal.Dot(incidentFace[0]) - refC;
				if (separation <= 0.0f)
				{
					this->lastData.contacts.push_back(incidentFace[0]);
					this->lastData.penetration = -separation;
					++cp;
				}
				else
				{
					this->lastData.penetration = 0;
				}

				separation = refFaceNormal.Dot(incidentFace[1]) - refC;
				if (separation <= 0.0f)
				{
					this->lastData.contacts[cp] = incidentFace[1];
					this->lastData.penetration += -separation;

					++cp;

					this->lastData.penetration /= -cp;
				}

				return true;
            }*/

			return false;
		}

		float PolyCollider::FindAxisLeastPenetration(int *faceIndex, PolyCollider * _other)
		{
            float bestDistance = 0;//-FLT_MAX;
            //int bestIndex;

            /*for (int count = 0; count < this->vertexCount; ++count)
			{
				// Retrieve a face normal from A
				Vector2 normal = this->normals[count];
				Vector2 normalMat = this->matrix * normal;

				// Transform face normal into B's model space
				Matrix22 buT = _other->GetMatrix().Transpose();
				normal = buT * normalMat;

				Vector2 support = _other->GetSupport(normal * -1);

				Vector2 vertice = this->vertices[count];
				vertice = this->matrix * (vertice + this->GetPosition());
				vertice = vertice - _other->GetPosition();
				vertice = buT * vertice;

				float distance = normal.Dot(support - vertice);

				// Store greatest distance
				if (distance > bestDistance)
				{
					bestDistance = distance;
					bestIndex = count;
				}
			}

            *faceIndex = bestIndex;*/
			return bestDistance;
		}

		std::vector<Vector2> PolyCollider::FindIncidentFace(PolyCollider *RefPoly, PolyCollider *IncPoly, int referenceIndex)
		{
			std::vector<Vector2> vertice;

            /*Vector2 referenceNormal = RefPoly->GerNormal()[referenceIndex];

			// Calculate normal in incident's frame of reference
			referenceNormal = RefPoly->GetMatrix() * referenceNormal; // To world space
			referenceNormal = IncPoly->GetMatrix().Transpose() * referenceNormal; // To incident's model space

																		// Find most anti-normal face on incident polygon
			int incidentFace = 0;
			float minDot = FLT_MAX;

			for (int count = 0; count < IncPoly->GetVerticesCount(); ++count)
			{
				float dot = referenceNormal.Dot(IncPoly->GerNormal()[count]);

				if (dot < minDot)
				{
					minDot = dot;
					incidentFace = count;
				}
			}

			// Assign face vertices for incidentFace
			vertice.push_back(IncPoly->GetMatrix() * (IncPoly->GetVertices()[incidentFace] + IncPoly->GetPosition()));
			incidentFace = incidentFace + 1 >= IncPoly->GetVerticesCount() ? 0 : incidentFace + 1;
            vertice.push_back(IncPoly->GetMatrix() * (IncPoly->GetVertices()[incidentFace] + IncPoly->GetPosition()));*/

			return vertice;
		}

		int PolyCollider::Clip(Vector2 normal, float c, std::vector<Vector2> *face)
		{
			int sp = 0;
			std::vector<Vector2> out;
			out.push_back(face->at(0));
			out.push_back(face->at(1));

			// Retrieve distances from each endpoint to the line
			// d = ax + by - c
			float distances1 = normal.Dot(face->at(0)) - c;
			float distances2 = normal.Dot(face->at(1)) - c;

			// If negative (behind plane) clip
			if (distances1 <= 0.0f) out[sp++] = face->at(0);
			if (distances2 <= 0.0f) out[sp++] = face->at(1);

			// If the points are on different sides of the plane
			if (distances1 * distances2 < 0.0f) // less than to ignore -0.0f
			{
				// Push interesection point
				float alpha = distances1 / (distances1 - distances2);
				out[sp] = face->at(0) + ((face->at(0) - face->at(1)) * alpha);
				++sp;
			}

			// Assign our new converted values
			face->clear();
			face->push_back(out[0]);
			face->push_back(out[1]);

			return sp;
		}


		HitData PolyCollider::CalcHitData(Collider * other)
		{
			if (other->GetType() == "SPHERE")
			{
				return this->HitDataSphere(other);
			}
			else if (other->GetType() == "POLY")
			{
				return this->lastData;
			}
		}

		HitData PolyCollider::HitDataSphere(Collider * other)
		{

			if (SphereCollider* collider = dynamic_cast<SphereCollider*>(other))
			{
				return collider->HitDataPoly(this);
			}

			HitData returnValue;
			returnValue.object = this;
			returnValue.other = other;

			return returnValue;
		}

		HitData PolyCollider::HitDataBox(Collider * other)
		{
			HitData returnValue;
			returnValue.object = this;
			returnValue.other = other;

			return returnValue;
		}
    }
}
