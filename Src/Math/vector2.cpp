
// General
#include "vector2.h"

// Additional
#include <cmath>


//
// Operators
//
const Vector2& Vector2::operator += (const Vector2& o)
{
	x += o.x;
	y += o.y;
	return *this;
}

const Vector2& Vector2::operator -= (const Vector2& o)
{
	x -= o.x;
	y -= o.y;
	return *this;
}

const Vector2& Vector2::operator *= (float f)
{
	x *= f;
	y *= f;
	return *this;
}

const Vector2& Vector2::operator /= (float f)
{
	x /= f;
	y /= f;
	return *this;
}

float Vector2::operator[](unsigned int i) const
{
	return *(&x + i);
}

float& Vector2::operator[](unsigned int i)
{
	return *(&x + i);
}

bool Vector2::operator== (const Vector2& other) const
{
	return x == other.x && y == other.y;
}

bool Vector2::operator!= (const Vector2& other) const
{
	return x != other.x || y != other.y;
}

bool Vector2::Equal(const Vector2& other, float epsilon) const
{
	return
		std::abs(x - other.x) <= epsilon &&
		std::abs(y - other.y) <= epsilon;
}



//
// Public
//
void Vector2::Set(float pX, float pY)
{
	x = pX; y = pY;
}

float Vector2::SquareLength() const
{
	return x*x + y*y;
}

float Vector2::Length() const
{
	return std::sqrt(SquareLength());
}

Vector2& Vector2::Normalize()
{
	*this /= Length();
	return *this;
}

const Vector2 Vector2::SymMul(const Vector2& o)
{
	return Vector2(x*o.x, y*o.y);
}
