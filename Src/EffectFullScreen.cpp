
// General
#include "EffectFullScreen.h"

CEffectFullScreen::CEffectFullScreen(ICubeController* CubeController)
	: CEffect(CubeController)
{
	SetFramePeriod(EFrameFuncPeriod_1);
	SetLenght(64);
	SetClearBeforeInit(false);
	SetClearBeforeFrame(false);
}



void CEffectFullScreen::FuncInit()
{
	m_X = 0;
	m_Y = 0;
	m_Z = 0;

	for (uint8_t x = 0; x < 8; x++)
		for (uint8_t y = 0; y < 8; y++)
			for (uint8_t z = 0; z < 8; z++)
				m_Points[x][y][z] = m_CubeController->GetMatrix()->GetPixel(x, y,z);
}

void CEffectFullScreen::FuncFrame(uint32_t Frame)
{
	for (uint8_t x = 0; x < 8; x++)
		FuncFrameFullScreen(Frame, x, m_Y, m_Z);

	//if (m_X < 7)
	//{
	//	m_X++;
	//}
	//else
	//{
	//	m_X = 0;


		if (m_Z < 7)
		{
			m_Z++;
		}
		else
		{
			m_Z = 0;


			if (m_Y < 7)
			{
				m_Y++;
			}
			else
			{
				m_Y = 0;
				printf("");
			}
		}
	//}
}

bool CEffectFullScreen::FuncFrameFullScreen(uint32_t Frame, uint8_t X, uint8_t Y, uint8_t Z)
{
	if (GET_PIXEL(X, Y, Z))
	{
		CLEAR_PIXEL(X, Y, Z);

		if ((Y + 1) < 8)
			SET_PIXEL(X, Y + 1, Z);
	}
}
