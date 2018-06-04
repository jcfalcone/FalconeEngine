#include "Vector3.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h> 

namespace FalconeEngine
{
    Vector3::Vector3() : x(0), y(0), z(0)
    {

    }

    Vector3::Vector3(FalconeEngine::Vector2 startVector)
    {
        this->x = startVector.x;
        this->y = startVector.y;
        this->z = 0;
    }

    Vector3::Vector3(float vecX, float vecY): x(vecX), y(vecY), z(0)
    {

    }

    Vector3::Vector3(float vecX, float vecY, float vecZ): x(vecX), y(vecY), z(vecZ)
    {

    }

    Vector3::~Vector3()
    {

    }

    float Vector3::length()
    {
        return sqrt(x * x + y * y);
    }

    Vector3 Vector3::normalize()
    {
        Vector3 vector;
        float length = this->length();

        if (length != 0)
        {
            vector.x = this->x / length;
            vector.y = this->y / length;
        }

        return vector;
    }

    Vector3 Vector3::rotateAround(Vector3 positionRef, float angle)
    {
        float newX = this->x + ((this->x - positionRef.x) * cos((angle * M_PI) / 180) - (this->y - positionRef.y) * sin((angle * M_PI) / 180));
        float newY = this->y + ((this->x - positionRef.x) * sin((angle * M_PI) / 180) + (this->y - positionRef.y) * cos((angle * M_PI) / 180));

        return Vector3(newX, newY);
    }

    float Vector3::distance(Vector3 positionDest)
    {
        float xDist = positionDest.x - this->x;
        float yDist = positionDest.y - this->y;
        float zDist = positionDest.z - this->z;

        return sqrt(pow(xDist, 2) + pow(yDist, 2) + pow(zDist, 2));
    }

    float Vector3::Product(Vector3 secondPoint)
    {
        return this->x * secondPoint.y - this->y * secondPoint.x;
    }

    float Vector3::AngleRad(Vector3 secondPoint)
    {
        return (this->Product(secondPoint) < 0 ? -1 : 1) * acos(this->Product(secondPoint) / (this->length() * secondPoint.length()));
    }

    float Vector3::Angle(Vector3 secondPoint)
    {
        return this->AngleRad(secondPoint) / M_PI * 180;
    }

    float Vector3::distance(Vector3 positionOri, Vector3 positionDest)
    {
        return positionOri.distance(positionDest);
    }

    Vector3 Vector3::Random(float startNum, float endNum)
    {
        startNum *= 100;
        endNum *= 100;

        float randomX = startNum + (rand() % (int)(endNum - startNum + 1));
        float randomY = startNum + (rand() % (int)(endNum - startNum + 1));
        float randomZ = startNum + (rand() % (int)(endNum - startNum + 1));

        return Vector3(randomX / 100, randomY / 100, randomZ / 100);
    }


    Vector3 Vector3::Random(float startNumX, float endNumX, float startNumY, float endNumY, float startNumZ, float endNumZ)
    {

        startNumX	*= 100;
        startNumY	*= 100;
        endNumX		*= 100;
        endNumY		*= 100;

        float randomX = startNumX + (rand() % (int)(endNumX - startNumX + 1));
        float randomY = startNumY + (rand() % (int)(endNumY - startNumY + 1));
        float randomZ = startNumZ + (rand() % (int)(endNumZ - startNumZ + 1));

        return Vector3(randomX / 100, randomY / 100, randomZ / 100);
    }

    Vector3 Vector3::Zero()
    {
        return Vector3();
    }

    Vector3 Vector3::One()
    {
        return Vector3(1, 1, 1);
    }


    Vector3 Vector3::direction(Vector3 positionDest)
    {
        Vector3 vector;
        float length = this->length();

        if (length != 0)
        {
            vector.x = this->x / length;
            vector.y = this->y / length;
            vector.z = this->z / length;
        }

        return vector;
    }



    Vector3 Vector3::operator+(Vector3 position)
    {
        float sumX = this->x + position.x;
        float sumY = this->y + position.y;
        float sumZ = this->z + position.z;

        return Vector3(sumX, sumY, sumZ);   // return old value
    }

    Vector3 Vector3::operator+(float number)
    {
        float sumX = this->x + number;
        float sumY = this->y + number;
        float sumZ = this->z + number;

        return Vector3(sumX, sumY, sumZ);   // return old value
    }

    Vector3 Vector3::operator+=(float number)
    {
        float sumX = this->x + number;
        float sumY = this->y + number;
        float sumZ = this->z + number;

        return Vector3(sumX, sumY, sumZ);   // return old value
    }

    Vector3 Vector3::operator+=(Vector3 position)
    {
        float sumX = this->x + position.x;
        float sumY = this->y + position.y;
        float sumZ = this->z + position.z;

        return Vector3(sumX, sumY, sumZ);   // return old value
    }

    Vector3 Vector3::operator-(Vector3 position)
    {
        float sumX = this->x - position.x;
        float sumY = this->y - position.y;
        float sumZ = this->z - position.z;

        return Vector3(sumX, sumY, sumZ);   // return old value
    }

    Vector3 Vector3::operator/(float number)
    {
        float sumX = this->x / number;
        float sumY = this->y / number;
        float sumZ = this->z / number;

        return Vector3(sumX, sumY, sumZ);   // return old value
    }

    Vector3 Vector3::operator*(float number)
    {
        float sumX = this->x * number;
        float sumY = this->y * number;
        float sumZ = this->z * number;

        return Vector3(sumX, sumY, sumZ);   // return old value
    }

    Vector3 Vector3::operator*(Vector3 position)
    {
        float sumX = this->x * position.x;
        float sumY = this->y * position.y;
        float sumZ = this->z * position.z;

        return Vector3(sumX, sumY, sumZ);   // return old value
    }

    bool Vector3::operator==(Vector3 position)
    {
        if (this->x == position.x &&
            this->y == position.y &&
            this->z == position.z)
        {
            return true;
        }

        return false;
    }

    std::ostream& operator<<(std::ostream& cout, const Vector3& vec)
    {
        return cout << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
    }
  }
