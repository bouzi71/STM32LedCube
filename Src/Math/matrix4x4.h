#ifndef __MATRIX4X4_H
#define __MATRIX4X4_H

#include "vector3.h"
#include "quaternion.h"

class Matrix4
{
public:

	/** set to identity */
	Matrix4();

	/** construction from single values */
	Matrix4
	(
			float _a1, float _a2, float _a3, float _a4,
			float _b1, float _b2, float _b3, float _b4,
			float _c1, float _c2, float _c3, float _c4,
			float _d1, float _d2, float _d3, float _d4
	);

	/** construction from 3x3 matrix, remaining elements are set to identity */
	explicit Matrix4(const Matrix3& m);


	/** construction from position, rotation and scaling components
	 * @param scaling The scaling for the x,y,z axes
	 * @param rotation The rotation as a hamilton quaternion
	 * @param position The position for the x,y,z axes
	 */
	Matrix4(const Vector3& scaling, const Quaternion& rotation, const Vector3& position);

public:
	Matrix4& operator *= (const Matrix4& m);
	Matrix4  operator *  (const Matrix4& m) const;

	float* operator[]       (unsigned int p_iIndex);
	const float* operator[] (unsigned int p_iIndex) const;

	bool operator== (const Matrix4& m) const;
	bool operator!= (const Matrix4& m) const;

	bool Equal(const Matrix4& m, float epsilon = 1e-6) const;

public:
	// -------------------------------------------------------------------
	/** @brief Transpose the matrix */
	Matrix4& Transpose();

	// -------------------------------------------------------------------
	/** @brief Invert the matrix.
	 *  If the matrix is not invertible all elements are set to qnan.
	 *  Beware, use (f != f) to check whether a float f is qnan.
	 */
	Matrix4& Inverse();
	float Determinant() const;


	// -------------------------------------------------------------------
	/** @brief Returns true of the matrix is the identity matrix.
	 *  The check is performed against a not so small epsilon.
	 */
	inline bool IsIdentity() const;

	// -------------------------------------------------------------------
	/** @brief Decompose a trafo matrix into its original components
	 *  @param scaling Receives the output scaling for the x,y,z axes
	 *  @param rotation Receives the output rotation as a hamilton
	 *   quaternion
	 *  @param position Receives the output position for the x,y,z axes
	 */
	void Decompose(Vector3& scaling, Quaternion& rotation, Vector3& position) const;

	// -------------------------------------------------------------------
	/** @brief Decompose a trafo matrix with no scaling into its
	 *    original components
	 *  @param rotation Receives the output rotation as a hamilton
	 *    quaternion
	 *  @param position Receives the output position for the x,y,z axes
	 */
	void DecomposeNoScaling(Quaternion& rotation, Vector3& position) const;


	// -------------------------------------------------------------------
	/** @brief Creates a trafo matrix from a set of euler angles
	 *  @param x Rotation angle for the x-axis, in radians
	 *  @param y Rotation angle for the y-axis, in radians
	 *  @param z Rotation angle for the z-axis, in radians
	 */
	Matrix4& FromEulerAnglesXYZ(float x, float y, float z);
	Matrix4& FromEulerAnglesXYZ(const Vector3& blubb);

public:
	// -------------------------------------------------------------------
	/** @brief Returns a rotation matrix for a rotation around the x axis
	 *  @param a Rotation angle, in radians
	 *  @param out Receives the output matrix
	 *  @return Reference to the output matrix
	 */
	static Matrix4& RotationX(float a, Matrix4& out);

	// -------------------------------------------------------------------
	/** @brief Returns a rotation matrix for a rotation around the y axis
	 *  @param a Rotation angle, in radians
	 *  @param out Receives the output matrix
	 *  @return Reference to the output matrix
	 */
	static Matrix4& RotationY(float a, Matrix4& out);

	// -------------------------------------------------------------------
	/** @brief Returns a rotation matrix for a rotation around the z axis
	 *  @param a Rotation angle, in radians
	 *  @param out Receives the output matrix
	 *  @return Reference to the output matrix
	 */
	static Matrix4& RotationZ(float a, Matrix4& out);

	// -------------------------------------------------------------------
	/** Returns a rotation matrix for a rotation around an arbitrary axis.
	 *  @param a Rotation angle, in radians
	 *  @param axis Rotation axis, should be a normalized vector.
	 *  @param out Receives the output matrix
	 *  @return Reference to the output matrix
	 */
	static Matrix4& Rotation(float a, const Vector3& axis, Matrix4& out);

	// -------------------------------------------------------------------
	/** @brief Returns a translation matrix
	 *  @param v Translation vector
	 *  @param out Receives the output matrix
	 *  @return Reference to the output matrix
	 */
	static Matrix4& Translation(const Vector3& v, Matrix4& out);

	// -------------------------------------------------------------------
	/** @brief Returns a scaling matrix
	 *  @param v Scaling vector
	 *  @param out Receives the output matrix
	 *  @return Reference to the output matrix
	 */
	static Matrix4& Scaling(const Vector3& v, Matrix4& out);

public:
	float a1, a2, a3, a4;
	float b1, b2, b3, b4;
	float c1, c2, c3, c4;
	float d1, d2, d3, d4;
};

#endif
