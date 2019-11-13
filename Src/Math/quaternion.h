#ifndef __QUATERNION_H
#define __QUATERNION_H

#include "vector3.h"
class Matrix3;

class Quaternion
{
public:
	Quaternion() : w(1.0), x(), y(), z() { }
	Quaternion(float pw, float px, float py, float pz) : w(pw), x(px), y(py), z(pz) { }

	/** Construct from rotation matrix. Result is undefined if the matrix is not orthonormal. */
	explicit Quaternion(const Matrix3& pRotMatrix);

	/** Construct from euler angles */
	Quaternion(float rotx, float roty, float rotz);

	/** Construct from an axis-angle pair */
	Quaternion(Vector3 axis, float angle);

	/** Construct from a normalized quaternion stored in a vec3 */
	explicit Quaternion(Vector3 normalized);

	/** Returns a matrix representation of the quaternion */
	Matrix3 GetMatrix() const;

public:

	bool operator== (const Quaternion& o) const;
	bool operator!= (const Quaternion& o) const;

	bool Equal(const Quaternion& o, float epsilon = 1e-6) const;

public:

	/** Normalize the quaternion */
	Quaternion& Normalize();

	/** Compute quaternion conjugate */
	Quaternion& Conjugate();

	/** Rotate a point by this quaternion */
	Vector3 Rotate(const Vector3& in);

	/** Multiply two quaternions */
	Quaternion operator* (const Quaternion& two) const;

public:

	/** Performs a spherical interpolation between two quaternions and writes the result into the third.
	 * @param pOut Target object to received the interpolated rotation.
	 * @param pStart Start rotation of the interpolation at factor == 0.
	 * @param pEnd End rotation, factor == 1.
	 * @param pFactor Interpolation factor between 0 and 1. Values outside of this range yield undefined results.
	 */
	static void Interpolate(Quaternion& pOut, const Quaternion& pStart, const Quaternion& pEnd, float pFactor);

public:

	//! w,x,y,z components of the quaternion
	float w, x, y, z;
};

#endif
