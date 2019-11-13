#ifndef __VECTOR2_H
#define __VECTOR2_H

class Vector2
{
public:
	Vector2()
	: x(), y()
	{}

	Vector2(float _x, float _y)
		: x(_x), y(_y)
	{}

	explicit Vector2(float _xyz)
		: x(_xyz), y(_xyz)
	{}

	Vector2(const Vector2& o)
		: x(o.x), y(o.y)
	{}

public:
	const Vector2& operator+= (const Vector2& o);
	const Vector2& operator-= (const Vector2& o);
	const Vector2& operator*= (float f);
	const Vector2& operator/= (float f);

	float operator[](unsigned int i) const;
	float& operator[](unsigned int i);

	bool operator== (const Vector2& other) const;
	bool operator!= (const Vector2& other) const;

	bool Equal(const Vector2& other, float epsilon = 1e-6) const;

public:
	void Set(float pX, float pY);
	float SquareLength() const;
	float Length() const;
	Vector2& Normalize();

	const Vector2 SymMul(const Vector2& o);

	float x, y;
};

#endif
