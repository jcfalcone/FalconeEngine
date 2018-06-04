#include "Vector2.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h> 

namespace FalconeEngine
{
    Vector2::Vector2() : x(0), y(0)
    {

    }

    Vector2::Vector2(float vecX, float vecY): x(vecX), y(vecY)
    {

    }

    Vector2::~Vector2()
    {

    }

    float Vector2::length()
    {
        return sqrt(x * x + y * y);
    }

	float Vector2::lengthSqrd() const 
	{ 
		return x * x + y * y; 
	}

    Vector2 Vector2::normalize()
    {
        Vector2 vector;
        float length = this->length();

        if (length != 0)
        {
            vector.x = this->x / length;
            vector.y = this->y / length;
        }

        return vector;
    }

    Vector2 Vector2::rotateAround(Vector2 positionRef, float angle)
    {
        float newX = this->x + ((this->x - positionRef.x) * cos((angle * M_PI) / 180) - (this->y - positionRef.y) * sin((angle * M_PI) / 180));
        float newY = this->y + ((this->x - positionRef.x) * sin((angle * M_PI) / 180) + (this->y - positionRef.y) * cos((angle * M_PI) / 180));

        return Vector2(newX, newY);
    }

    float Vector2::distance(Vector2 positionDest)
    {
        float xDist = positionDest.x - this->x;
        float yDist = positionDest.y - this->y;

        return sqrt(pow(xDist, 2) + pow(yDist, 2));
    }

	float Vector2::distanceSqr(Vector2 positionDest)
	{
		Vector2 dist = *this - positionDest;
		return dist.Dot(dist);
	}

    float Vector2::Cross(Vector2 secondPoint)
    {
        return this->x * secondPoint.y - this->y * secondPoint.x;
    }
	Vector2 Vector2::Cross(float scalar)
	{
		return Vector2(scalar * this->y, -scalar * this->x);
	}

	Vector2 Vector2::CrossInverse(float scalar)
	{
		return Vector2(-scalar * this->y, scalar * this->x);
	}

	float Vector2::Dot(Vector2 secondPoint)
	{
		return this->x * secondPoint.x + this->y * secondPoint.y;
	}

    float Vector2::AngleRad(Vector2 secondPoint)
    {
        return (this->Cross(secondPoint) < 0 ? -1 : 1) * acos(this->Cross(secondPoint) / (this->length() * secondPoint.length()));
    }

    float Vector2::Angle(Vector2 secondPoint)
    {
        return this->AngleRad(secondPoint) / M_PI * 180;
    }

    float Vector2::distance(Vector2 positionOri, Vector2 positionDest)
    {
        return positionOri.distance(positionDest);
    }

    Vector2 Vector2::Random(float startNum, float endNum)
    {
        startNum *= 100;
        endNum *= 100;

        float randomX = startNum + (rand() % (int)(endNum - startNum + 1));
        float randomY = startNum + (rand() % (int)(endNum - startNum + 1));

        return Vector2(randomX / 100, randomY / 100);
    }


    Vector2 Vector2::Random(float startNumX, float endNumX, float startNumY, float endNumY)
    {

        startNumX	*= 100;
        startNumY	*= 100;
        endNumX		*= 100;
        endNumY		*= 100;

        float randomX = startNumX + (rand() % (int)(endNumX - startNumX + 1));
        float randomY = startNumY + (rand() % (int)(endNumY - startNumY + 1));

        return Vector2(randomX / 100, randomY / 100);
    }

    Vector2 Vector2::Zero()
    {
        return Vector2(0, 0);
    }
	Vector2 Vector2::Up()
	{
		return Vector2(0, 1);
	}

	Vector2 Vector2::Right()
	{
		return Vector2(1, 0);
	}


    Vector2 Vector2::direction(Vector2 positionDest)
    {
        Vector2 vector;
        float length = this->length();

        if (length != 0)
        {
            vector.x = this->x / length;
            vector.y = this->y / length;
        }

        return vector;
    }



    Vector2 Vector2::operator+(Vector2 position)
    {
        float sumX = this->x + position.x;
        float sumY = this->y + position.y;

        return Vector2(sumX, sumY);   // return old value
    }

    Vector2 Vector2::operator+(float number)
    {
        float sumX = this->x + number;
        float sumY = this->y + number;

        return Vector2(sumX, sumY);   // return old value
    }

    Vector2 Vector2::operator+=(float number)
    {
        float sumX = this->x + number;
        float sumY = this->y + number;

        return Vector2(sumX, sumY);   // return old value
    }

    Vector2 Vector2::operator+=(Vector2 position)
    {
        float sumX = this->x + position.x;
        float sumY = this->y + position.y;

        return Vector2(sumX, sumY);   // return old value
    }

    Vector2 Vector2::operator-(Vector2 position)
    {
        float sumX = this->x - position.x;
        float sumY = this->y - position.y;

        return Vector2(sumX, sumY);   // return old value
    }

    Vector2 Vector2::operator/(float number)
    {
        float sumX = this->x / number;
        float sumY = this->y / number;

        return Vector2(sumX, sumY);   // return old value
    }

    Vector2 Vector2::operator*(float number)
    {
        float sumX = this->x * number;
        float sumY = this->y * number;

        return Vector2(sumX, sumY);   // return old value
    }

    Vector2 Vector2::operator*(Vector2 position)
    {
        float sumX = this->x * position.x;
        float sumY = this->y * position.y;

        return Vector2(sumX, sumY);   // return old value
    }

    bool Vector2::operator==(Vector2 position)
    {
        if (this->x == position.x &&
            this->y == position.y)
        {
            return true;
        }

        return false;
    }

    std::ostream& operator<<(std::ostream& cout, const Vector2& vec)
    {
        return cout << "(" << vec.x << "," << vec.y << ")";
    }
}
