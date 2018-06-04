#ifndef VECTOR2
#define VECTOR2

#include <iostream>

namespace FalconeEngine
{
    class Vector2
    {
    public:

        float x;
        float y;

        Vector2();
        Vector2(float vecX, float vecY);

        float length();
		float lengthSqrd() const;
        Vector2 normalize();
        Vector2 rotateAround(Vector2 positionRef, float angle);

        float distance(Vector2 positionDest);
		float distanceSqr(Vector2 positionDest);
        static float distance(Vector2 positionOri, Vector2 positionDest);

        float Cross(Vector2 secondPoint);
		Vector2 Cross(float scalar);
		Vector2 CrossInverse(float scalar);
		float Dot(Vector2 secondPoint);
        float AngleRad(Vector2 secondPoint);
        float Angle(Vector2 secondPoint);

        static Vector2 Random(float startNum, float endNum);
        static Vector2 Random(float startNumX, float endNumX, float startNumY, float endNumY);

        static Vector2 Zero();
		static Vector2 Up();
		static Vector2 Right();

        Vector2 direction(Vector2 positionDest);

        Vector2 operator+(Vector2 position);
        Vector2 operator+(float number);

        Vector2 operator+=(float number);
        Vector2 operator+=(Vector2 position);

        Vector2 operator-(Vector2 position);
        Vector2 operator/(float number);
        Vector2 operator*(float number);
        Vector2 operator*(Vector2 position);

        bool operator==(Vector2 position);

        friend std::ostream& operator<<(std::ostream& cout, const Vector2& vec);

        ~Vector2();
    };
}
#endif // VECTOR2

