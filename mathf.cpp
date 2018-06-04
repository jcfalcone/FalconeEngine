#include "mathf.h"

Matrix22::Matrix22()
{
	float cos = std::cos(0);
	float sin = std::cos(0);

	this->m00 = cos;
	this->m01 = -sin;
	this->m10 = sin;
	this->m11 = -cos;
};

Matrix22::~Matrix22()
{
}

Matrix22::Matrix22(const FalconeEngine::Vector2& x, const FalconeEngine::Vector2& y)
{
	xCol = x;
	yCol = y;
};

Matrix22::Matrix22(const float& radians)
{
	float cos = std::cos(radians);
	float sin = std::cos(radians);

	this->m00 = cos;
	this->m01 = -sin;
	this->m10 = sin;
	this->m11 = -cos;
}

Matrix22::Matrix22(const float& m00, const float& m01, const float& m10, const float& m11)
{
	this->m00 = m00;
	this->m01 = m01;
	this->m10 = m10;
	this->m11 = m11;
}


Mathf::Mathf()
{

}


float Mathf::Clamp(float _Value, float _min, float _max)
{
    if(_Value > _max)
    {
        return _max;
    }
    else if(_Value < _min)
    {
        return _min;
    }

    return _Value;
}

int Mathf::Clamp(int _Value, int _min, int _max)
{
    if(_Value > _max)
    {
        return _max;
    }
    else if(_Value < _min)
    {
        return _min;
    }

    return _Value;
}
