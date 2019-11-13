
// General
#include "Effect3D.h"

// Additonal
#include <cmath>

#define SLOW_ROUND(x) ::round(x)
#define FAST_ROUND(x) (uint8_t)(x + 0.5f)
#define DEFAUL_ROUND(x) FAST_ROUND(x)

CEffect3D::CEffect3D(ICubeController * CubeController)
	: CEffect(CubeController)
	, m_DrawMode(EDrawMode::EDrawMode_Set)
    , m_Effect3DIsNeedCleadBeforeFrame(true)
{
	SetClearBeforeInit(false);
}

void CEffect3D::FuncFrame(uint32_t Frame)
{
	if (!FuncFrame3D(Frame, float(Frame) / float(GetLenght())))
		return;

	// Do redraw fugure
	if (m_Effect3DIsNeedCleadBeforeFrame)
		m_CubeController->GetMatrix()->Clear();

	for (size_t i = 0; i < m_Fugure.GetPointCount(); i++)
	{
		ApplyPointToMatrix(m_Fugure.GetConvertedPoint(m_WorldMatrix, i));
	}
}


bool CEffect3D::IsNeedClearBeforeInit() const
{
	return CEffect::IsNeedClearBeforeInit();
}

bool CEffect3D::IsNeedClearBeforeFrame() const
{
	return false;
}


//
// Public
//
float CEffect3D::GetLenghtFloat() const
{
	return float(GetLenght());
}


//
// Protected
//
bool CEffect3D::FuncFrame3D(uint32_t FrameUint, float FrameFloat)
{
	return true;
}


void CEffect3D::SetClearBeforeInit(bool Value)
{
	CEffect::SetClearBeforeInit(Value);
}

void CEffect3D::SetClearBeforeFrame(bool Value)
{
	m_Effect3DIsNeedCleadBeforeFrame = Value;
}


void CEffect3D::SetDrawMode(EDrawMode DrawMode)
{
	m_DrawMode = DrawMode;
}

//
// Virtual protected
//
void CEffect3D::LineX(uint32_t planeY, uint32_t planeZ)
{
	for (uint32_t x = 0; x < 8; x++)
		m_Fugure.AddPoint(x, planeY, planeZ);
}

void CEffect3D::LineY(uint32_t planeX, uint32_t planeZ)
{
	for (uint32_t y = 0; y < 8; y++)
		m_Fugure.AddPoint(planeX, y, planeZ);
}

void CEffect3D::LineZ(uint32_t planeX, uint32_t planeY)
{
	for (uint32_t z = 0; z < 8; z++)
		m_Fugure.AddPoint(planeX, planeY, z);
}

void CEffect3D::PlaneX(uint32_t plane)
{
	for (uint32_t y = 0; y < 8; y++)
		for (uint32_t z = 0; z < 8; z++)
			m_Fugure.AddPoint(plane, y, z);
}

void CEffect3D::PlaneY(uint32_t plane)
{
	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t z = 0; z < 8; z++)
			m_Fugure.AddPoint(x, plane, z);
}

void CEffect3D::PlaneZ(uint32_t plane)
{
	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t y = 0; y < 8; y++)
			m_Fugure.AddPoint(x, y, plane);
}

void CEffect3D::Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				m_Fugure.AddPoint(x, y, z);
}

void CEffect3D::CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				if (x == xBegin || x == xEnd || y == yBegin || y == yEnd || z == zBegin || z == zEnd)
					m_Fugure.AddPoint(x, y, z);
}


//
// Private
//
void CEffect3D::ApplyPointToMatrix(const Vector3& Vector)
{
	switch (m_DrawMode)
	{
		case EDrawMode_Set:
			SET_PIXEL(DEFAUL_ROUND(Vector.x), DEFAUL_ROUND(Vector.y), DEFAUL_ROUND(Vector.z))
		break;

		case EDrawMode_Clear:
			CLEAR_PIXEL(DEFAUL_ROUND(Vector.x), DEFAUL_ROUND(Vector.y), DEFAUL_ROUND(Vector.z))
		break;

		case EDrawMode_Toggle:
			TOGGLE_PIXEL(DEFAUL_ROUND(Vector.x), DEFAUL_ROUND(Vector.y), DEFAUL_ROUND(Vector.z))
		break;
	}
}
