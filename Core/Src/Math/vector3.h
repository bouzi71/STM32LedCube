#ifndef __VECTOR3_H
#define __VECTOR3_H

class Matrix3;
class Matrix4;

class Vector3
{
public:
	Vector3()
		: x(), y(), z()
	{}
	Vector3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{}
	explicit Vector3(float _xyz)
		: x(_xyz), y(_xyz), z(_xyz)
	{}
	Vector3(const Vector3& o)
		: x(o.x), y(o.y), z(o.z)
	{}

public:
	const Vector3& operator+=(const Vector3& o);
	const Vector3& operator-=(const Vector3& o);
	const Vector3& operator*=(float f);
	const Vector3& operator/=(float f);

	Vector3& operator*=(const Matrix3& mat);
	Vector3& operator*=(const Matrix4& mat);

	float operator[](unsigned int i) const;
	float& operator[](unsigned int i);

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	bool operator <(const Vector3& other) const;

	bool Equal(const Vector3& other, float epsilon = 1e-6) const;

public:
	/** @brief Set the components of a vector
	 *  @param pX X component
	 *  @param pY Y component
	 *  @param pZ Z component  */
	void Set(float pX, float pY, float pZ);

	/** @brief Get the squared length of the vector
	 *  @return Square length */
	float SquareLength() const;


	/** @brief Get the length of the vector
	 *  @return length */
	float Length() const;


	/** @brief Normalize the vector */
	Vector3& Normalize();

	/** @brief Normalize the vector with extra check for zero vectors */
	Vector3& NormalizeSafe();

	/** @brief Componentwise multiplication of two vectors
	 *
	 *  Note that vec*vec yields the dot product.
	 *  @param o Second factor */
	const Vector3 SymMul(const Vector3& o);

	float x, y, z;
};

#endif

