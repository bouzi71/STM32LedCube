
// General
#include "quaternion.h"

// Additional
#include "matrix3x3.h"

#include <cmath>

// ---------------------------------------------------------------------------

bool Quaternion::operator== (const Quaternion& o) const
{
	return x == o.x && y == o.y && z == o.z && w == o.w;
}

// ---------------------------------------------------------------------------

bool Quaternion::operator!= (const Quaternion& o) const
		{
	return !(*this == o);
}

// ---------------------------------------------------------------------------

bool Quaternion::Equal(const Quaternion& o, float epsilon) const
{
	return
		std::abs(x - o.x) <= epsilon &&
		std::abs(y - o.y) <= epsilon &&
		std::abs(z - o.z) <= epsilon &&
		std::abs(w - o.w) <= epsilon;
}

// ---------------------------------------------------------------------------
// Constructs a quaternion from a rotation matrix

Quaternion::Quaternion(const Matrix3 &pRotMatrix)
{
	float t = pRotMatrix.a1 + pRotMatrix.b2 + pRotMatrix.c3;

	// large enough
	if(t > (0)) {
		float s = std::sqrt(1 + t) * (2.0);
		x = (pRotMatrix.c2 - pRotMatrix.b3) / s;
		y = (pRotMatrix.a3 - pRotMatrix.c1) / s;
		z = (pRotMatrix.b1 - pRotMatrix.a2) / s;
		w = (0.25) * s;
	} // else we have to check several cases
	else if(pRotMatrix.a1 > pRotMatrix.b2 && pRotMatrix.a1 > pRotMatrix.c3) {
		// Column 0:
		float s = std::sqrt((1.0) + pRotMatrix.a1 - pRotMatrix.b2 - pRotMatrix.c3) * (2.0);
		x = (0.25) * s;
		y = (pRotMatrix.b1 + pRotMatrix.a2) / s;
		z = (pRotMatrix.a3 + pRotMatrix.c1) / s;
		w = (pRotMatrix.c2 - pRotMatrix.b3) / s;
	}
	else if(pRotMatrix.b2 > pRotMatrix.c3) {
		// Column 1:
		float s = std::sqrt((1.0) + pRotMatrix.b2 - pRotMatrix.a1 - pRotMatrix.c3) * (2.0);
		x = (pRotMatrix.b1 + pRotMatrix.a2) / s;
		y = (0.25) * s;
		z = (pRotMatrix.c2 + pRotMatrix.b3) / s;
		w = (pRotMatrix.a3 - pRotMatrix.c1) / s;
	}
	else {
		// Column 2:
		float s = std::sqrt((1.0) + pRotMatrix.c3 - pRotMatrix.a1 - pRotMatrix.b2) * (2.0);
		x = (pRotMatrix.a3 + pRotMatrix.c1) / s;
		y = (pRotMatrix.c2 + pRotMatrix.b3) / s;
		z = (0.25) * s;
		w = (pRotMatrix.b1 - pRotMatrix.a2) / s;
	}
}

// ---------------------------------------------------------------------------
// Construction from euler angles

Quaternion::Quaternion(float fPitch, float fYaw, float fRoll)
{
	const float fSinPitch(std::sin(fPitch*(0.5)));
	const float fCosPitch(std::cos(fPitch*(0.5)));
	const float fSinYaw(std::sin(fYaw*(0.5)));
	const float fCosYaw(std::cos(fYaw*(0.5)));
	const float fSinRoll(std::sin(fRoll*(0.5)));
	const float fCosRoll(std::cos(fRoll*(0.5)));
	const float fCosPitchCosYaw(fCosPitch*fCosYaw);
	const float fSinPitchSinYaw(fSinPitch*fSinYaw);

	x = fSinRoll * fCosPitchCosYaw - fCosRoll * fSinPitchSinYaw;
	y = fCosRoll * fSinPitch * fCosYaw + fSinRoll * fCosPitch * fSinYaw;
	z = fCosRoll * fCosPitch * fSinYaw - fSinRoll * fSinPitch * fCosYaw;
	w = fCosRoll * fCosPitchCosYaw + fSinRoll * fSinPitchSinYaw;
}

// ---------------------------------------------------------------------------
// Returns a matrix representation of the quaternion

Matrix3 Quaternion::GetMatrix() const
{
	Matrix3 resMatrix;
	resMatrix.a1 = (1.0) - (2.0) * (y * y + z * z);
	resMatrix.a2 = (2.0) * (x * y - z * w);
	resMatrix.a3 = (2.0) * (x * z + y * w);
	resMatrix.b1 = (2.0) * (x * y + z * w);
	resMatrix.b2 = (1.0) - (2.0) * (x * x + z * z);
	resMatrix.b3 = (2.0) * (y * z - x * w);
	resMatrix.c1 = (2.0) * (x * z - y * w);
	resMatrix.c2 = (2.0) * (y * z + x * w);
	resMatrix.c3 = (1.0) - (2.0) * (x * x + y * y);

	return resMatrix;
}

// ---------------------------------------------------------------------------
// Construction from an axis-angle pair

Quaternion::Quaternion(Vector3 axis, float angle)
{
	axis.Normalize();

	const float sin_a = std::sin(angle / 2);
	const float cos_a = std::cos(angle / 2);
	x = axis.x * sin_a;
	y = axis.y * sin_a;
	z = axis.z * sin_a;
	w = cos_a;
}
// ---------------------------------------------------------------------------
// Construction from am existing, normalized quaternion

Quaternion::Quaternion(Vector3 normalized) {
	x = normalized.x;
	y = normalized.y;
	z = normalized.z;

	const float t = (1.0) - (x*x) - (y*y) - (z*z);

	if(t < (0.0))
	{
		w = (0.0);
	}
	else w = std::sqrt(t);
}

// ---------------------------------------------------------------------------
// Performs a spherical interpolation between two quaternions
// Implementation adopted from the gmtl project. All others I found on the net fail in some cases.
// Congrats, gmtl!

void Quaternion::Interpolate(Quaternion& pOut, const Quaternion& pStart, const Quaternion& pEnd, float pFactor) {
	// calc cosine theta
	float cosom = pStart.x * pEnd.x + pStart.y * pEnd.y + pStart.z * pEnd.z + pStart.w * pEnd.w;

	// adjust signs (if necessary)
	Quaternion end = pEnd;
	if(cosom < (0.0)) {
		cosom = -cosom;
		end.x = -end.x;   // Reverse all signs
		end.y = -end.y;
		end.z = -end.z;
		end.w = -end.w;
	}

	// Calculate coefficients
	float sclp, sclq;
	if(((1.0) - cosom) > (0.0001)) // 0.0001 -> some epsillon
	{
		// Standard case (slerp)
		float omega, sinom;
		omega = std::acos(cosom); // extract theta from dot product's cos theta
		sinom = std::sin(omega);
		sclp = std::sin(((1.0) - pFactor) * omega) / sinom;
		sclq = std::sin(pFactor * omega) / sinom;
	}
	else {
		// Very close, do linear interp (because it's faster)
		sclp = (1.0) - pFactor;
		sclq = pFactor;
	}

	pOut.x = sclp * pStart.x + sclq * end.x;
	pOut.y = sclp * pStart.y + sclq * end.y;
	pOut.z = sclp * pStart.z + sclq * end.z;
	pOut.w = sclp * pStart.w + sclq * end.w;
}

// ---------------------------------------------------------------------------

Quaternion& Quaternion::Normalize() {
	// compute the magnitude and divide through it
	const float mag = std::sqrt(x*x + y*y + z*z + w*w);
	if(mag) {
		const float invMag = (1.0) / mag;
		x *= invMag;
		y *= invMag;
		z *= invMag;
		w *= invMag;
	}
	return *this;
}

// ---------------------------------------------------------------------------

Quaternion Quaternion::operator* (const Quaternion& t) const {
	return Quaternion(w*t.w - x*t.x - y*t.y - z*t.z,
						 w*t.x + x*t.w + y*t.z - z*t.y,
						 w*t.y + y*t.w + z*t.x - x*t.z,
						 w*t.z + z*t.w + x*t.y - y*t.x);
}

// ---------------------------------------------------------------------------

Quaternion& Quaternion::Conjugate()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

// ---------------------------------------------------------------------------

Vector3 Quaternion::Rotate(const Vector3& v)
{
	Quaternion q2(0.f, v.x, v.y, v.z), q = *this, qinv = q;
	qinv.Conjugate();

	q = q*q2*qinv;
	return Vector3(q.x, q.y, q.z);
}
