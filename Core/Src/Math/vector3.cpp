
// General
#include "vector3.h"

// Additional
#include "matrix3x3.h"
#include "matrix4x4.h"

#include <cmath>

/** Transformation of a vector by a 3x3 matrix */
Vector3 operator*(const Matrix3& pMatrix, const Vector3& pVector)

{
	Vector3 res;
	res.x = pMatrix.a1 * pVector.x + pMatrix.a2 * pVector.y + pMatrix.a3 * pVector.z;
	res.y = pMatrix.b1 * pVector.x + pMatrix.b2 * pVector.y + pMatrix.b3 * pVector.z;
	res.z = pMatrix.c1 * pVector.x + pMatrix.c2 * pVector.y + pMatrix.c3 * pVector.z;
	return res;
}

/** Transformation of a vector by a 4x4 matrix */
Vector3 operator* (const Matrix4& pMatrix, const Vector3& pVector)
{
	Vector3 res;
	res.x = pMatrix.a1 * pVector.x + pMatrix.a2 * pVector.y + pMatrix.a3 * pVector.z + pMatrix.a4;
	res.y = pMatrix.b1 * pVector.x + pMatrix.b2 * pVector.y + pMatrix.b3 * pVector.z + pMatrix.b4;
	res.z = pMatrix.c1 * pVector.x + pMatrix.c2 * pVector.y + pMatrix.c3 * pVector.z + pMatrix.c4;
	return res;
}


//
// Operators
//
const Vector3& Vector3::operator+= (const Vector3& o)
{
	x += o.x; y += o.y; z += o.z; return *this;
}

const Vector3& Vector3::operator-= (const Vector3& o)
{
	x -= o.x; y -= o.y; z -= o.z; return *this;
}

const Vector3& Vector3::operator*= (float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

const Vector3& Vector3::operator/= (float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

Vector3& Vector3::operator*= (const Matrix3& mat)
{
	return (*this = mat * (*this));
}

Vector3& Vector3::operator *= (const Matrix4& mat)
{
	return(*this = mat * (*this));
}

float Vector3::operator[](unsigned int i) const
{
	return *(&x + i);
}

float& Vector3::operator[](unsigned int i)
{
	return *(&x + i);
}

bool Vector3::operator== (const Vector3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

bool Vector3::operator!= (const Vector3& other) const
{
	return x != other.x || y != other.y || z != other.z;
}

bool Vector3::operator < (const Vector3& other) const
{
	return x != other.x ? x < other.x : y != other.y ? y < other.y : z < other.z;
}

bool Vector3::Equal(const Vector3& other, float epsilon) const
{
	return
		std::abs(x - other.x) <= epsilon &&
		std::abs(y - other.y) <= epsilon &&
		std::abs(z - other.z) <= epsilon;
}



//
// Public
//
void Vector3::Set(float pX, float pY, float pZ)
{
	x = pX; y = pY; z = pZ;
}

float Vector3::SquareLength() const
{
	return x*x + y*y + z*z;
}

float Vector3::Length() const
{
	return std::sqrt(SquareLength());
}

Vector3& Vector3::Normalize()
{
	*this /= Length(); return *this;
}

Vector3& Vector3::NormalizeSafe()
{
	float len = Length();
	if(len > 0.0f)
		*this /= len;
	return *this;
}

const Vector3 Vector3::SymMul(const Vector3& o)
{
	return Vector3(x*o.x, y*o.y, z*o.z);
}

