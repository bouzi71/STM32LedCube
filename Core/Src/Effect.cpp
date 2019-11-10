
// General
#include <Effect.h>



//
// CEffect
//
CEffect::CEffect()
{}

CEffect::CEffect(ICubeController * CubeController)
	: m_FramePeriod(EFrameFuncPeriod::EFrameFuncPeriod_10)
	, m_Lenght(1)
    , m_RepeatCnt(1)
	, m_CleanCubeBeforeInit(false)
	, m_CleanCubeBeforeFrame(true)
	, m_CubeController(CubeController)
{}


// IEffect
void CEffect::FuncInit()
{}

void CEffect::FuncFrame(uint32_t /*Frame*/)
{}

void CEffect::InvokeFuncFrame(EFrameFuncPeriod /*FramePeriod*/, uint32_t Frame)
{
	FuncFrame(Frame);
}

EFrameFuncPeriod CEffect::GetFramePeriod() const
{
	return m_FramePeriod;
}

void CEffect::SetFramePeriod(EFrameFuncPeriod Period)
{
	m_FramePeriod = Period;
}

uint32_t CEffect::GetLenght() const
{
	return m_Lenght;
}

void CEffect::SetLenght(uint32_t Value)
{
	m_Lenght = Value;
}

uint32_t CEffect::GetRepeatCount() const
{
	return m_RepeatCnt;
}

void CEffect::SetRepeatCount(uint32_t Value)
{
	m_RepeatCnt = Value;
}

bool CEffect::IsNeedClearBeforeInit() const
{
	return m_CleanCubeBeforeInit;
}

bool CEffect::IsNeedClearBeforeFrame() const
{
	return m_CleanCubeBeforeFrame;
}



//
// Protected
//
void CEffect::PlaneX(uint32_t plane)
{
	for (uint32_t y = 0; y < 8; y++)
		for (uint32_t z = 0; z < 8; z++)
			SET_PIXEL(plane, y, z);
}

void CEffect::PlaneY(uint32_t plane)
{
	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t z = 0; z < 8; z++)
			SET_PIXEL(x, plane, z);
}

void CEffect::PlaneZ(uint32_t plane)
{
	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t y = 0; y < 8; y++)
			SET_PIXEL(x, y, plane);
}

void CEffect::Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				SET_PIXEL(x, y, z);
}

void CEffect::CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				if (x == xBegin || x == xEnd || y == yBegin || y == yEnd || z == zBegin || z == zEnd)
					SET_PIXEL(x, y, z);
}

void CEffect::SetClearBeforeInit(bool Value)
{
	m_CleanCubeBeforeInit = Value;
}

void CEffect::SetClearBeforeFrame(bool Value)
{
	m_CleanCubeBeforeFrame = Value;
}

