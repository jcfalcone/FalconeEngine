#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <Vector2.h>

namespace FalconeEngine
{
    class Vector3
    {
    public:

        float x;
        float y;
        float z;

        Vector3();
        Vector3(FalconeEngine::Vector2 startVector);
        Vector3(float vecX, float vecY);
        Vector3(float vecX, float vecY, float vecZ);

        float length();
        Vector3 normalize();
        Vector3 rotateAround(Vector3 positionRef, float angle);

        float distance(Vector3 positionDest);
        static float distance(Vector3 positionOri, Vector3 positionDest);

        float Product(Vector3 secondPoint);
        float AngleRad(Vector3 secondPoint);
        float Angle(Vector3 secondPoint);

        static Vector3 Random(float startNum, float endNum);
        static Vector3 Random(float startNumX, float endNumX, float startNumY, float endNumY, float startNumZ, float endNumZ);

        static Vector3 Zero();
        static Vector3 One();

        Vector3 direction(Vector3 positionDest);

        Vector3 operator+(Vector3 position);
        Vector3 operator+(float number);

        Vector3 operator+=(float number);
        Vector3 operator+=(Vector3 position);

        Vector3 operator-(Vector3 position);
        Vector3 operator/(float number);
        Vector3 operator*(float number);
        Vector3 operator*(Vector3 position);

        bool operator==(Vector3 position);

        friend std::ostream& operator<<(std::ostream& cout, const Vector3& vec);


        ~Vector3();
    };
}
#endif // VECTOR3

