
// General
#include "Effect3D.h"

// Additonal
#include <cmath>

#define SLOW_ROUND(x) ::round(x)
#define FAST_ROUND(x) (uint8_t)(x + 0.5f)
#define DEFAUL_ROUND(x) SLOW_ROUND(x)

CEffect3D::CEffect3D(ICubeController * CubeController)
	: CEffect(CubeController)
{
	SetClearBeforeFrame(false); // DO NOT CHANGE!!!
}

void CEffect3D::FuncFrame(uint32_t Frame)
{
	if (!FuncFrame3D(Frame))
		return;

	// Do redraw fugure
	m_CubeController->GetMatrix()->Clear();
	for (const auto& p : m_Fugure)
	{
		Vector3 pResult = p;
		pResult *= m_WorldMatrix;

		ApplyPointToMatrix(pResult);
	}
}


//
// Protected
//

void CEffect3D::ClearFigure()
{
	m_Fugure.clear();
}

Vector3 CEffect3D::ToVector3(uint8_t x, uint8_t y, uint8_t z) const
{
	Vector3 p = Vector3(x, y, z); // TODO: Optimize me
	p /= cMultiplyValue;
	p -= cOffsetVector;
	return p;
}

bool CEffect3D::FuncFrame3D(uint32_t Frame)
{
	return true;
}

//
// Virtual protected
//
void CEffect3D::PlaneX(uint32_t plane)
{
	ClearFigure();

	for (uint32_t y = 0; y < 8; y++)
		for (uint32_t z = 0; z < 8; z++)
			m_Fugure.push_back(ToVector3(plane, y, z));
}

void CEffect3D::PlaneY(uint32_t plane)
{
	ClearFigure();

	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t z = 0; z < 8; z++)
			m_Fugure.push_back(ToVector3(x, plane, z));
}

void CEffect3D::PlaneZ(uint32_t plane)
{
	ClearFigure();

	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t y = 0; y < 8; y++)
			m_Fugure.push_back(ToVector3(x, y, plane));
}

void CEffect3D::Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	ClearFigure();

	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				m_Fugure.push_back(ToVector3(x, y, z));
}

void CEffect3D::CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	ClearFigure();

	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				if (x == xBegin || x == xEnd || y == yBegin || y == yEnd || z == zBegin || z == zEnd)
					m_Fugure.push_back(ToVector3(x, y, z));
}



//
// Private
//
void CEffect3D::ApplyPointToMatrix(const Vector3& Vector)
{
	Vector3 p = Vector;
	p += cOffsetVector;
	p *= 7.0f;
	SET_PIXEL(DEFAUL_ROUND(p.x), DEFAUL_ROUND(p.y), DEFAUL_ROUND(p.z))
}
