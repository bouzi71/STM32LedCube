
// General
#include "matrix3x3.h"

// Additional
#include "matrix4x4.h"

#include <algorithm>
#include <cmath>
#include <limits>

Matrix3::Matrix3(const Matrix4& pMatrix)
{
	a1 = pMatrix.a1; a2 = pMatrix.a2; a3 = pMatrix.a3;
	b1 = pMatrix.b1; b2 = pMatrix.b2; b3 = pMatrix.b3;
	c1 = pMatrix.c1; c2 = pMatrix.c2; c3 = pMatrix.c3;
}

Matrix3& Matrix3::operator *= (const Matrix3& m)
{
	*this = Matrix3(m.a1 * a1 + m.b1 * a2 + m.c1 * a3,
						  m.a2 * a1 + m.b2 * a2 + m.c2 * a3,
						  m.a3 * a1 + m.b3 * a2 + m.c3 * a3,
						  m.a1 * b1 + m.b1 * b2 + m.c1 * b3,
						  m.a2 * b1 + m.b2 * b2 + m.c2 * b3,
						  m.a3 * b1 + m.b3 * b2 + m.c3 * b3,
						  m.a1 * c1 + m.b1 * c2 + m.c1 * c3,
						  m.a2 * c1 + m.b2 * c2 + m.c2 * c3,
						  m.a3 * c1 + m.b3 * c2 + m.c3 * c3);
	return *this;
}

Matrix3 Matrix3::operator* (const Matrix3& m) const
{
	Matrix3 temp(*this);
	temp *= m;
	return temp;
}

float* Matrix3::operator[] (unsigned int p_iIndex)
{
	return &this->a1 + p_iIndex * 3;
}

const float* Matrix3::operator[] (unsigned int p_iIndex) const
{
	return &this->a1 + p_iIndex * 3;
}

bool Matrix3::operator== (const Matrix4& m) const
{
	return a1 == m.a1 && a2 == m.a2 && a3 == m.a3 &&
		   b1 == m.b1 && b2 == m.b2 && b3 == m.b3 &&
		   c1 == m.c1 && c2 == m.c2 && c3 == m.c3;
}

bool Matrix3::operator!= (const Matrix4& m) const
{
	return !(*this == m);
}

bool Matrix3::Equal(const Matrix4& m, float epsilon) const
{
	return
		std::abs(a1 - m.a1) <= epsilon &&
		std::abs(a2 - m.a2) <= epsilon &&
		std::abs(a3 - m.a3) <= epsilon &&
		std::abs(b1 - m.b1) <= epsilon &&
		std::abs(b2 - m.b2) <= epsilon &&
		std::abs(b3 - m.b3) <= epsilon &&
		std::abs(c1 - m.c1) <= epsilon &&
		std::abs(c2 - m.c2) <= epsilon &&
		std::abs(c3 - m.c3) <= epsilon;
}

Matrix3& Matrix3::Transpose()
{
	// (float&) don't remove, GCC complains cause of packed fields
	std::swap((float&)a2, (float&)b1);
	std::swap((float&)a3, (float&)c1);
	std::swap((float&)b3, (float&)c2);
	return *this;
}

float Matrix3::Determinant() const
{
	return a1*b2*c3 - a1*b3*c2 + a2*b3*c1 - a2*b1*c3 + a3*b1*c2 - a3*b2*c1;
}

Matrix3& Matrix3::Inverse()
{
	// Compute the reciprocal determinant
	float det = Determinant();
	if(det == (0.0))
	{
		// Matrix not invertible. Setting all elements to nan is not really
		// correct in a mathematical sense; but at least qnans are easy to
		// spot. XXX we might throw an exception instead, which would
		// be even much better to spot :/.
		const float nan = 0.0f; //std::numeric_limits::quiet_NaN();
		*this = Matrix3(nan, nan, nan, nan, nan, nan, nan, nan, nan);

		return *this;
	}

	float invdet = (1.0) / det;

	Matrix3 res;
	res.a1 = invdet  * (b2 * c3 - b3 * c2);
	res.a2 = -invdet * (a2 * c3 - a3 * c2);
	res.a3 = invdet  * (a2 * b3 - a3 * b2);
	res.b1 = -invdet * (b1 * c3 - b3 * c1);
	res.b2 = invdet  * (a1 * c3 - a3 * c1);
	res.b3 = -invdet * (a1 * b3 - a3 * b1);
	res.c1 = invdet  * (b1 * c2 - b2 * c1);
	res.c2 = -invdet * (a1 * c2 - a2 * c1);
	res.c3 = invdet  * (a1 * b2 - a2 * b1);
	*this = res;

	return *this;
}

Matrix3& Matrix3::RotationZ(float a, Matrix3& out) {
	out.a1 = out.b2 = std::cos(a);
	out.b1 = std::sin(a);
	out.a2 = -out.b1;

	out.a3 = out.b3 = out.c1 = out.c2 = 0.f;
	out.c3 = 1.f;

	return out;
}

Matrix3& Matrix3::Rotation(float a, const Vector3& axis, Matrix3& out)
{
	float c = std::cos(a), s = std::sin(a), t = 1 - c;
	float x = axis.x, y = axis.y, z = axis.z;

	// Many thanks to MathWorld and Wikipedia
	out.a1 = t*x*x + c;   out.a2 = t*x*y - s*z; out.a3 = t*x*z + s*y;
	out.b1 = t*x*y + s*z; out.b2 = t*y*y + c;   out.b3 = t*y*z - s*x;
	out.c1 = t*x*z - s*y; out.c2 = t*y*z + s*x; out.c3 = t*z*z + c;

	return out;
}

Matrix3& Matrix3::Translation(const Vector2& v, Matrix3& out)
{
	out = Matrix3();
	out.a3 = v.x;
	out.b3 = v.y;
	return out;
}
