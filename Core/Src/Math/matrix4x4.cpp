
// General
#include "matrix4x4.h"

// Additional
#include "matrix3x3.h"
#include "quaternion.h"

#include <algorithm>
#include <limits>
#include <cmath>

Matrix4::Matrix4() :
	a1(1.0f), a2(), a3(), a4(),
	b1(), b2(1.0f), b3(), b4(),
	c1(), c2(), c3(1.0f), c4(),
	d1(), d2(), d3(), d4(1.0f)
{}

Matrix4 ::Matrix4(float _a1, float _a2, float _a3, float _a4,
                  float _b1, float _b2, float _b3, float _b4,
				  float _c1, float _c2, float _c3, float _c4,
				  float _d1, float _d2, float _d3, float _d4) :
	a1(_a1), a2(_a2), a3(_a3), a4(_a4),
	b1(_b1), b2(_b2), b3(_b3), b4(_b4),
	c1(_c1), c2(_c2), c3(_c3), c4(_c4),
	d1(_d1), d2(_d2), d3(_d3), d4(_d4)
{}

Matrix4::Matrix4(const Matrix3& m)
{
	a1 = m.a1; a2 = m.a2; a3 = m.a3; a4 = (0.0);
	b1 = m.b1; b2 = m.b2; b3 = m.b3; b4 = (0.0);
	c1 = m.c1; c2 = m.c2; c3 = m.c3; c4 = (0.0);

	d1 = (0.0);
	d2 = (0.0);
	d3 = (0.0);
	d4 = (1.0);
}

Matrix4::Matrix4(const Vector3& scaling, const Quaternion& rotation, const Vector3& position)
{
	// build a 3x3 rotation matrix
	Matrix3 m = rotation.GetMatrix();

	a1 = m.a1 * scaling.x;
	a2 = m.a2 * scaling.x;
	a3 = m.a3 * scaling.x;
	a4 = position.x;

	b1 = m.b1 * scaling.y;
	b2 = m.b2 * scaling.y;
	b3 = m.b3 * scaling.y;
	b4 = position.y;

	c1 = m.c1 * scaling.z;
	c2 = m.c2 * scaling.z;
	c3 = m.c3 * scaling.z;
	c4 = position.z;

	d1 = (0.0);
	d2 = (0.0);
	d3 = (0.0);
	d4 = (1.0);
}



//
// Operators
//
Matrix4& Matrix4::operator *= (const Matrix4& m)
{
	*this = Matrix4(
		m.a1 * a1 + m.b1 * a2 + m.c1 * a3 + m.d1 * a4,
		m.a2 * a1 + m.b2 * a2 + m.c2 * a3 + m.d2 * a4,
		m.a3 * a1 + m.b3 * a2 + m.c3 * a3 + m.d3 * a4,
		m.a4 * a1 + m.b4 * a2 + m.c4 * a3 + m.d4 * a4,
		m.a1 * b1 + m.b1 * b2 + m.c1 * b3 + m.d1 * b4,
		m.a2 * b1 + m.b2 * b2 + m.c2 * b3 + m.d2 * b4,
		m.a3 * b1 + m.b3 * b2 + m.c3 * b3 + m.d3 * b4,
		m.a4 * b1 + m.b4 * b2 + m.c4 * b3 + m.d4 * b4,
		m.a1 * c1 + m.b1 * c2 + m.c1 * c3 + m.d1 * c4,
		m.a2 * c1 + m.b2 * c2 + m.c2 * c3 + m.d2 * c4,
		m.a3 * c1 + m.b3 * c2 + m.c3 * c3 + m.d3 * c4,
		m.a4 * c1 + m.b4 * c2 + m.c4 * c3 + m.d4 * c4,
		m.a1 * d1 + m.b1 * d2 + m.c1 * d3 + m.d1 * d4,
		m.a2 * d1 + m.b2 * d2 + m.c2 * d3 + m.d2 * d4,
		m.a3 * d1 + m.b3 * d2 + m.c3 * d3 + m.d3 * d4,
		m.a4 * d1 + m.b4 * d2 + m.c4 * d3 + m.d4 * d4);
	return *this;
}

Matrix4 Matrix4::operator* (const Matrix4& m) const
{
	Matrix4 temp(*this);
	temp *= m;
	return temp;
}

float* Matrix4::operator[](unsigned int p_iIndex)
{
	if (p_iIndex > 3)
	{
		return NULL;
	}

	// XXX this is UB. Has been for years. The fact that it works now does not make it better.
	return &this->a1 + p_iIndex * 4;
}

const float* Matrix4::operator[](unsigned int p_iIndex) const
{
	if (p_iIndex > 3)
	{
		return NULL;
	}

	// XXX same
	return &this->a1 + p_iIndex * 4;
}

bool Matrix4::operator== (const Matrix4& m) const
{
	return (a1 == m.a1 && a2 == m.a2 && a3 == m.a3 && a4 == m.a4 &&
			b1 == m.b1 && b2 == m.b2 && b3 == m.b3 && b4 == m.b4 &&
			c1 == m.c1 && c2 == m.c2 && c3 == m.c3 && c4 == m.c4 &&
			d1 == m.d1 && d2 == m.d2 && d3 == m.d3 && d4 == m.d4);
}

bool Matrix4::operator!= (const Matrix4& m) const
{
	return !(*this == m);
}

bool Matrix4::Equal(const Matrix4& m, float epsilon) const
{
	return
		std::abs(a1 - m.a1) <= epsilon &&
		std::abs(a2 - m.a2) <= epsilon &&
		std::abs(a3 - m.a3) <= epsilon &&
		std::abs(a4 - m.a4) <= epsilon &&
		std::abs(b1 - m.b1) <= epsilon &&
		std::abs(b2 - m.b2) <= epsilon &&
		std::abs(b3 - m.b3) <= epsilon &&
		std::abs(b4 - m.b4) <= epsilon &&
		std::abs(c1 - m.c1) <= epsilon &&
		std::abs(c2 - m.c2) <= epsilon &&
		std::abs(c3 - m.c3) <= epsilon &&
		std::abs(c4 - m.c4) <= epsilon &&
		std::abs(d1 - m.d1) <= epsilon &&
		std::abs(d2 - m.d2) <= epsilon &&
		std::abs(d3 - m.d3) <= epsilon &&
		std::abs(d4 - m.d4) <= epsilon;
}



//
// Public
//
Matrix4& Matrix4::Transpose()
{
	// (float&) don't remove, GCC complains cause of packed fields
	std::swap((float&)b1, (float&)a2);
	std::swap((float&)c1, (float&)a3);
	std::swap((float&)c2, (float&)b3);
	std::swap((float&)d1, (float&)a4);
	std::swap((float&)d2, (float&)b4);
	std::swap((float&)d3, (float&)c4);
	return *this;
}


Matrix4& Matrix4::Inverse()
{
	// Compute the reciprocal determinant
	const float det = Determinant();
	if (det == (0.0))
	{
		// Matrix not invertible. Setting all elements to nan is not really
		// correct in a mathematical sense but it is easy to debug for the
		// programmer.
		const float nan = 0.0f; //std::numeric_limits::quiet_NaN<float>();
		*this = Matrix4
		(
			nan, nan, nan, nan,
			nan, nan, nan, nan,
			nan, nan, nan, nan,
			nan, nan, nan, nan
		);

		return *this;
	}

	const float invdet = (1.0) / det;

	Matrix4 res;
	res.a1 = invdet  * (b2 * (c3 * d4 - c4 * d3) + b3 * (c4 * d2 - c2 * d4) + b4 * (c2 * d3 - c3 * d2));
	res.a2 = -invdet * (a2 * (c3 * d4 - c4 * d3) + a3 * (c4 * d2 - c2 * d4) + a4 * (c2 * d3 - c3 * d2));
	res.a3 = invdet  * (a2 * (b3 * d4 - b4 * d3) + a3 * (b4 * d2 - b2 * d4) + a4 * (b2 * d3 - b3 * d2));
	res.a4 = -invdet * (a2 * (b3 * c4 - b4 * c3) + a3 * (b4 * c2 - b2 * c4) + a4 * (b2 * c3 - b3 * c2));
	res.b1 = -invdet * (b1 * (c3 * d4 - c4 * d3) + b3 * (c4 * d1 - c1 * d4) + b4 * (c1 * d3 - c3 * d1));
	res.b2 = invdet  * (a1 * (c3 * d4 - c4 * d3) + a3 * (c4 * d1 - c1 * d4) + a4 * (c1 * d3 - c3 * d1));
	res.b3 = -invdet * (a1 * (b3 * d4 - b4 * d3) + a3 * (b4 * d1 - b1 * d4) + a4 * (b1 * d3 - b3 * d1));
	res.b4 = invdet  * (a1 * (b3 * c4 - b4 * c3) + a3 * (b4 * c1 - b1 * c4) + a4 * (b1 * c3 - b3 * c1));
	res.c1 = invdet  * (b1 * (c2 * d4 - c4 * d2) + b2 * (c4 * d1 - c1 * d4) + b4 * (c1 * d2 - c2 * d1));
	res.c2 = -invdet * (a1 * (c2 * d4 - c4 * d2) + a2 * (c4 * d1 - c1 * d4) + a4 * (c1 * d2 - c2 * d1));
	res.c3 = invdet  * (a1 * (b2 * d4 - b4 * d2) + a2 * (b4 * d1 - b1 * d4) + a4 * (b1 * d2 - b2 * d1));
	res.c4 = -invdet * (a1 * (b2 * c4 - b4 * c2) + a2 * (b4 * c1 - b1 * c4) + a4 * (b1 * c2 - b2 * c1));
	res.d1 = -invdet * (b1 * (c2 * d3 - c3 * d2) + b2 * (c3 * d1 - c1 * d3) + b3 * (c1 * d2 - c2 * d1));
	res.d2 = invdet  * (a1 * (c2 * d3 - c3 * d2) + a2 * (c3 * d1 - c1 * d3) + a3 * (c1 * d2 - c2 * d1));
	res.d3 = -invdet * (a1 * (b2 * d3 - b3 * d2) + a2 * (b3 * d1 - b1 * d3) + a3 * (b1 * d2 - b2 * d1));
	res.d4 = invdet  * (a1 * (b2 * c3 - b3 * c2) + a2 * (b3 * c1 - b1 * c3) + a3 * (b1 * c2 - b2 * c1));
	*this = res;

	return *this;
}

float Matrix4::Determinant() const
{
	return a1*b2*c3*d4 - a1*b2*c4*d3 + a1*b3*c4*d2 - a1*b3*c2*d4
		+ a1*b4*c2*d3 - a1*b4*c3*d2 - a2*b3*c4*d1 + a2*b3*c1*d4
		- a2*b4*c1*d3 + a2*b4*c3*d1 - a2*b1*c3*d4 + a2*b1*c4*d3
		+ a3*b4*c1*d2 - a3*b4*c2*d1 + a3*b1*c2*d4 - a3*b1*c4*d2
		+ a3*b2*c4*d1 - a3*b2*c1*d4 - a4*b1*c2*d3 + a4*b1*c3*d2
		- a4*b2*c3*d1 + a4*b2*c1*d3 - a4*b3*c1*d2 + a4*b3*c2*d1;
}

bool Matrix4::IsIdentity() const
{
	// Use a small epsilon to solve floating-point inaccuracies
	const static float epsilon = 10e-3f;

	return (a2 <= epsilon && a2 >= -epsilon &&
			a3 <= epsilon && a3 >= -epsilon &&
			a4 <= epsilon && a4 >= -epsilon &&
			b1 <= epsilon && b1 >= -epsilon &&
			b3 <= epsilon && b3 >= -epsilon &&
			b4 <= epsilon && b4 >= -epsilon &&
			c1 <= epsilon && c1 >= -epsilon &&
			c2 <= epsilon && c2 >= -epsilon &&
			c4 <= epsilon && c4 >= -epsilon &&
			d1 <= epsilon && d1 >= -epsilon &&
			d2 <= epsilon && d2 >= -epsilon &&
			d3 <= epsilon && d3 >= -epsilon &&
			a1 <= 1.f + epsilon && a1 >= 1.f - epsilon &&
			b2 <= 1.f + epsilon && b2 >= 1.f - epsilon &&
			c3 <= 1.f + epsilon && c3 >= 1.f - epsilon &&
			d4 <= 1.f + epsilon && d4 >= 1.f - epsilon);
}

void Matrix4::Decompose(Vector3& scaling, Quaternion& rotation,  Vector3& position) const
{
	const Matrix4& _this = *this;

	// extract translation
	position.x = _this[0][3];
	position.y = _this[1][3];
	position.z = _this[2][3];

	// extract the rows of the matrix
	Vector3 vRows[3] = {
		Vector3(_this[0][0],_this[1][0],_this[2][0]),
		Vector3(_this[0][1],_this[1][1],_this[2][1]),
		Vector3(_this[0][2],_this[1][2],_this[2][2])
	};

	// extract the scaling factors
	scaling.x = vRows[0].Length();
	scaling.y = vRows[1].Length();
	scaling.z = vRows[2].Length();

	// and the sign of the scaling
	if(Determinant() < 0)
	{
		scaling.x = -scaling.x;
		scaling.y = -scaling.y;
		scaling.z = -scaling.z;
	}

	// and remove all scaling from the matrix
	if(scaling.x) {
		vRows[0] /= scaling.x;
	}
	if(scaling.y) {
		vRows[1] /= scaling.y;
	}
	if(scaling.z) {
		vRows[2] /= scaling.z;
	}

	// build a 3x3 rotation matrix
	Matrix3 m(vRows[0].x, vRows[1].x, vRows[2].x,
						vRows[0].y, vRows[1].y, vRows[2].y,
						vRows[0].z, vRows[1].z, vRows[2].z);

	// and generate the rotation quaternion from it
	rotation = Quaternion(m);
}

void Matrix4::DecomposeNoScaling(Quaternion& rotation, Vector3& position) const
{
	const Matrix4& _this = *this;

	// extract translation
	position.x = _this[0][3];
	position.y = _this[1][3];
	position.z = _this[2][3];

	// extract rotation
	rotation = Quaternion((Matrix3)_this);
}


Matrix4& Matrix4::FromEulerAnglesXYZ(float x, float y, float z)
{
	Matrix4& _this = *this;

	float cr = std::cos(x);
	float sr = std::sin(x);
	float cp = std::cos(y);
	float sp = std::sin(y);
	float cy = std::cos(z);
	float sy = std::sin(z);

	_this.a1 = cp*cy;
	_this.a2 = cp*sy;
	_this.a3 = -sp;

	float srsp = sr*sp;
	float crsp = cr*sp;

	_this.b1 = srsp*cy - cr*sy;
	_this.b2 = srsp*sy + cr*cy;
	_this.b3 = sr*cp;

	_this.c1 = crsp*cy + sr*sy;
	_this.c2 = crsp*sy - sr*cy;
	_this.c3 = cr*cp;

	return *this;
}

Matrix4& Matrix4::FromEulerAnglesXYZ(const Vector3& blubb)
{
	return FromEulerAnglesXYZ(blubb.x, blubb.y, blubb.z);
}



//
// Transform
//
Matrix4& Matrix4::RotationX(float a, Matrix4& out)
{
	/*
		 |  1  0       0       0 |
	 M = |  0  cos(A) -sin(A)  0 |
		 |  0  sin(A)  cos(A)  0 |
		 |  0  0       0       1 |  */
	out = Matrix4();
	out.b2 = out.c3 = std::cos(a);
	out.b3 = -(out.c2 = std::sin(a));
	return out;
}

Matrix4& Matrix4::RotationY(float a, Matrix4& out)
{
	/*
		 |  cos(A)  0   sin(A)  0 |
	 M = |  0       1   0       0 |
		 | -sin(A)  0   cos(A)  0 |
		 |  0       0   0       1 |
		*/
	out = Matrix4();
	out.a1 = out.c3 = std::cos(a);
	out.c1 = -(out.a3 = std::sin(a));
	return out;
}

Matrix4& Matrix4::RotationZ(float a, Matrix4& out)
{
	/*
		 |  cos(A)  -sin(A)   0   0 |
	 M = |  sin(A)   cos(A)   0   0 |
		 |  0        0        1   0 |
		 |  0        0        0   1 |   */
	out = Matrix4();
	out.a1 = out.b2 = std::cos(a);
	out.a2 = -(out.b1 = std::sin(a));
	return out;
}

Matrix4& Matrix4::Rotation(float a, const Vector3& axis, Matrix4& out)
{
	float c = std::cos(a), s = std::sin(a), t = 1 - c;
	float x = axis.x, y = axis.y, z = axis.z;

	// Many thanks to MathWorld and Wikipedia
	out.a1 = t*x*x + c;   out.a2 = t*x*y - s*z; out.a3 = t*x*z + s*y;
	out.b1 = t*x*y + s*z; out.b2 = t*y*y + c;   out.b3 = t*y*z - s*x;
	out.c1 = t*x*z - s*y; out.c2 = t*y*z + s*x; out.c3 = t*z*z + c;
	out.a4 = out.b4 = out.c4 = (0.0);
	out.d1 = out.d2 = out.d3 = (0.0);
	out.d4 = (1.0);

	return out;
}

Matrix4& Matrix4::Translation(const Vector3& v, Matrix4& out)
{
	out = Matrix4();
	out.a4 = v.x;
	out.b4 = v.y;
	out.c4 = v.z;
	return out;
}

Matrix4& Matrix4::Scaling(const Vector3& v, Matrix4& out)
{
	out = Matrix4();
	out.a1 = v.x;
	out.b2 = v.y;
	out.c3 = v.z;
	return out;
}
