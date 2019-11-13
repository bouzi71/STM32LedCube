
// General
#include "Figure.h"

CFugure3D::CFugure3D()
{
}

void CFugure3D::Clear()
{
	m_Points.clear();
}

void CFugure3D::AddPoint(uint8_t x, uint8_t y, uint8_t z)
{
	m_Points.push_back(ToVector3(x, y, z));
}

void CFugure3D::AddPoint(const Vector3& Point)
{
	m_Points.push_back(Point);
}

const std::vector<Vector3>& CFugure3D::GetPoints() const
{
	return m_Points;
}

size_t CFugure3D::GetPointCount() const
{
	return m_Points.size();
}

Vector3 CFugure3D::GetConvertedPoint(const Matrix4& Matrix, size_t Index) const
{
	Vector3 p = m_Points[Index];
	p *= Matrix;

	p += cOffsetVector;
	p *= 7.0f;

	return p;
}

void CFugure3D::ModifyData(const Matrix4& Matrix)
{
	for (size_t i = 0; i < m_Points.size(); i++)
	{
		Vector3 p = m_Points[i];
		p *= Matrix;
		m_Points[i] = p;
	}
}

Vector3 CFugure3D::ToVector3(uint8_t x, uint8_t y, uint8_t z) const
{
	Vector3 p = Vector3(x, y, z); // TODO: Optimize me
	p /= cMultiplyValue;
	p -= cOffsetVector;
	return p;
}


