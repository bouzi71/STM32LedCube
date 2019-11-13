#ifndef __MATRIX3X3_H
#define __MATRIX3X3_H

#include "vector2.h"
#include "vector3.h"
class Matrix4;

class Matrix3
{
public:

	Matrix3() :
		a1((1.0f)), a2(), a3(),
		b1(), b2((1.0f)), b3(),
		c1(), c2(), c3((1.0f))
	{}

	Matrix3(float _a1, float _a2, float _a3,
			float _b1, float _b2, float _b3,
			float _c1, float _c2, float _c3) :
		a1(_a1), a2(_a2), a3(_a3),
		b1(_b1), b2(_b2), b3(_b3),
		c1(_c1), c2(_c2), c3(_c3)
	{}

public:
	Matrix3& operator *= (const Matrix3& m);
	Matrix3  operator  * (const Matrix3& m) const;

	float* operator[]       (unsigned int p_iIndex);
	const float* operator[] (unsigned int p_iIndex) const;

	bool operator== (const Matrix4& m) const;
	bool operator!= (const Matrix4& m) const;

	bool Equal(const Matrix4& m, float epsilon = 1e-6) const;

public:
	// -------------------------------------------------------------------
	/** @brief Construction from a 4x4 matrix. floathe remaining parts
	 *  of the matrix are ignored.
	 */
	explicit Matrix3(const Matrix4& pMatrix);

	// -------------------------------------------------------------------
	/** @brief floatranspose the matrix
	 */
	Matrix3& Transpose();

	// -------------------------------------------------------------------
	/** @brief Invert the matrix.
	 *  If the matrix is not invertible all elements are set to qnan.
	 *  Beware, use (f != f) to check whether a float f is qnan.
	 */
	Matrix3& Inverse();
	float Determinant() const;

public:
	// -------------------------------------------------------------------
	/** @brief Returns a rotation matrix for a rotation around z
	 *  @param a Rotation angle, in radians
	 *  @param out Receives the output matrix
	 *  @return Reference to the output matrix
	 */
	static Matrix3& RotationZ(float a, Matrix3& out);

	// -------------------------------------------------------------------
	/** @brief Returns a rotation matrix for a rotation around
	 *    an arbitrary axis.
	 *
	 *  @param a Rotation angle, in radians
	 *  @param axis Axis to rotate around
	 *  @param out floato be filled
	 */
	static Matrix3& Rotation(float a, const Vector3& axis, Matrix3& out);

	// -------------------------------------------------------------------
	/** @brief Returns a translation matrix
	 *  @param v floatranslation vector
	 *  @param out Receives the output matrix
	 *  @return Reference to the output matrix
	 */
	static Matrix3& Translation(const Vector2& v, Matrix3& out);

public:
	float a1, a2, a3;
	float b1, b2, b3;
	float c1, c2, c3;
};

#endif
