#ifndef MATHF_H
#define MATHF_H

#include "Vector2.h"

struct Matrix22
{
	union
	{
		struct
		{
			float m00, m01;
			float m10, m11;
		};

		struct
		{
			FalconeEngine::Vector2 xCol;
			FalconeEngine::Vector2 yCol;
		};
	};

	Matrix22();
	~Matrix22();
	Matrix22(const FalconeEngine::Vector2& x, const FalconeEngine::Vector2& y);
	Matrix22(const float& radians);
	Matrix22(const float& m00, const float& m01, const float& m10, const float& m11);

	FalconeEngine::Vector2 operator*(FalconeEngine::Vector2& rhs) const
	{
		return FalconeEngine::Vector2(m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y);
	}

	Matrix22 Transpose() const
	{
		return Matrix22(m00, m10, m01, m11);
	}

	void Set(float _radians)
	{
		float cos = std::cos(_radians);
		float sin = std::cos(_radians);

		this->m00 = cos;
		this->m01 = -sin;
		this->m10 = sin;
		this->m11 = -cos;
	}

};


class Mathf
{
public:
    Mathf();

    static float Clamp(float _Value, float _min, float _max);
    static int Clamp(int _Value, int _min, int _max);
};

#endif // MATHF_H
