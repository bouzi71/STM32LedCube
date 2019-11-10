
// General
#include <EffectsEngine.h>

// Additional
#include <string.h>

/*

void DrawSnakeT(uint8_t maxVal)
{
	uint8_t beginVal = 0;
	if (maxVal > 1)
		beginVal = maxVal - 1;

	for (uint8_t i = beginVal; i < maxVal; i++)
	{
		uint8_t x = i / 8;
		uint8_t y = i % 8;


		for (uint8_t z = 0; z < 1; z++)
		{
			if (x % 2 == 0)
			{
				TOGGLE_PIXEL(x, y, z);
			}
			else
			{
				TOGGLE_PIXEL(x, 7 - y, z);
			}
		}
	}
}




void DrawSnake111(uint32_t frame)
{
	DrawSnakeT(frame % 65);
}



#define NAPRAVLENIE_UP 0
#define NAPRAVLENIE_RIGHT 1
#define NAPRAVLENIE_DOWN 2
#define NAPRAVLENIE_LEFT 3

uint8_t napr; // 0-up 1-right 2-down 3-left
uint8_t posX;
uint8_t posY;

uint8_t minX;
uint8_t minY;

uint8_t maxX;
uint8_t maxY;

void InitSpiral()
{
	napr = NAPRAVLENIE_UP;

	minX = 0;
	minY = 0;

	maxX = 7;
	maxY = 7;

	posX = minX;
	posY = minY;
}

void FrameSpiral(uint32_t frame)
{
	for (uint32_t z = 0; z < 8; z++)
		SET_PIXEL(posX, posY, z);
	//SET_PIXEL(posX, posY, maxX);

	//SET_PIXEL(posX, minX, posY);
	//SET_PIXEL(posX, maxX, posY);

	//SET_PIXEL(minX, posX, posY);
	//SET_PIXEL(maxX, posX, posY);

	if (napr == NAPRAVLENIE_UP)
	{
		if (posY + 1 >= (maxY + 1) || (GET_PIXEL(posX, posY + 1, 0) == 1))
		{
			napr = NAPRAVLENIE_RIGHT;
			return;
		}

		posY += 1;

	}
	else if (napr == NAPRAVLENIE_RIGHT)
	{
		if ((posX + 1) >= (maxX + 1) || (GET_PIXEL(posX + 1, posY, 0) == 1))
		{
			napr = NAPRAVLENIE_DOWN;
			return;
		}

		posX += 1;
	}
	else if (napr == NAPRAVLENIE_DOWN)
	{
		if (posY == minY || (GET_PIXEL(posX, posY - 1, 0) == 1))
		{
			napr = NAPRAVLENIE_LEFT;
			return;
		}

		posY -= 1;
	}
	else if (napr == NAPRAVLENIE_LEFT)
	{
		if (posX == minX || (GET_PIXEL(posX - 1, posY, 0) == 1))
		{
			napr = NAPRAVLENIE_UP;
			return;
		}

		posX -= 1;
	}
}

*/



// Planes -------------------------------------------------------------

class CEffectPlanes : public CEffect
{
public:
	CEffectPlanes(IMatrixAccess * MatrixAccess)
		: CEffect(EFrameFuncType5, 16, MatrixAccess)
	{}

	void FuncFrame(uint32_t Frame) override final
	{
		uint32_t t = Frame % 16;
		if (t >= 8)
			t = 14 - t;

		PlaneX(t);
		PlaneY(t);
		PlaneZ(t);
	}
};



// CUBES -------------------------------------------------------------

class CEffectExpandCubeToBorder : public CEffect
{
public:
	CEffectExpandCubeToBorder(IMatrixAccess * MatrixAccess)
		: CEffect(EFrameFuncType5, 4, MatrixAccess)
	{}

	void FuncFrame(uint32_t Frame) override final
	{
		uint32_t t = Frame % 4;
		CubeOutline(3 - t, 4 + t, 3 - t, 4 + t, 3 - t, 4 + t);
	}
};

// -------------------------------------------------------------------

class CEffectCollapseCubeTo777 : public CEffect
{
public:
	CEffectCollapseCubeTo777(IMatrixAccess * MatrixAccess)
		: CEffect(EFrameFuncType5, 8, MatrixAccess)
	{}

	void FuncFrame(uint32_t Frame) override final
	{
		uint32_t t = Frame % 8;
		CubeOutline(t, 7, t, 7, t, 7);
	}
};

// -------------------------------------------------------------------

class CEffectExpandCubeFrom777To000 : public CEffect
{
public:
	CEffectExpandCubeFrom777To000(IMatrixAccess * MatrixAccess)
		: CEffect(EFrameFuncType5, 8, MatrixAccess)
	{}

	void FuncFrame(uint32_t Frame) override final
	{
		uint32_t t = Frame % 8;
		CubeOutline(7 - t, 7, 7 - t, 7, 7 - t, 7);
	}
};

// -------------------------------------------------------------------

class CEffectCollapseCubeFrom777To000 : public CEffect
{
public:
	CEffectCollapseCubeFrom777To000(IMatrixAccess * MatrixAccess)
		: CEffect(EFrameFuncType5, 8, MatrixAccess)
	{}

	void FuncFrame(uint32_t Frame) override final
	{
		uint32_t t = Frame % 8;
		CubeOutline(0, 7 - t , 0, 7 - t, 0, 7 - t);
	}
};

// -------------------------------------------------------------------

class CEffectExpandCubeFrom000To777 : public CEffect
{
public:
	CEffectExpandCubeFrom000To777(IMatrixAccess * MatrixAccess)
		: CEffect(EFrameFuncType5, 8, MatrixAccess)
	{}

	void FuncFrame(uint32_t Frame) override final
	{
		uint32_t t = Frame % 8;
		CubeOutline(0, t, 0, t, 0, t);
	}
};

// -------------------------------------------------------------------

class CEffectCollapseCubeFromToCenter : public CEffect
{
public:
	CEffectCollapseCubeFromToCenter(IMatrixAccess * MatrixAccess)
		: CEffect(EFrameFuncType5, 4, MatrixAccess)
	{}

	void FuncFrame(uint32_t Frame) override final
	{
		uint32_t t = 3 - (Frame % 4);
		CubeOutline(3 - t, 4 + t, 3 - t, 4 + t, 3 - t, 4 + t);
	}
};

// -------------------------------------------------------------------



//
// CEffect
//
CEffect::CEffect()
{}

CEffect::CEffect(EFrameFuncType FrameFuncType, uint32_t Lenght, IMatrixAccess * MatrixAccess)
	: m_FrameFuncType(FrameFuncType)
	, m_CleanCubeBeforeInit(false)
	, m_CleanCubeBeforeFrame(true)
	, m_CurrentFrame(0)
	, m_Lenght(Lenght)
	, m_MatrixAccess(MatrixAccess)
{}

void CEffect::FuncInit()
{

}

void CEffect::FuncFrame(uint32_t /*Frame*/)
{

}

void CEffect::Reset()
{
	m_CurrentFrame = 0;
}


void CEffect::IncCurrentFrame()
{
	m_CurrentFrame += 1;
}

EFrameFuncType CEffect::GetFrameFuncType() const
{
	return m_FrameFuncType;
}


uint32_t CEffect::GetCurrentFrame() const
{
	return m_CurrentFrame;
}

uint32_t CEffect::GetLenght() const
{
	return m_Lenght;
}

bool CEffect::IsPlaying() const
{
	return m_CurrentFrame < m_Lenght;
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
			m_MatrixAccess->SetPixel(plane, y, z);
}

void CEffect::PlaneY(uint32_t plane)
{
	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t z = 0; z < 8; z++)
			m_MatrixAccess->SetPixel(x, plane, z);
}

void CEffect::PlaneZ(uint32_t plane)
{
	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t y = 0; y < 8; y++)
			m_MatrixAccess->SetPixel(x, y, plane);
}

void CEffect::Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				m_MatrixAccess->SetPixel(x, y, z);
}

void CEffect::CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				if (x == xBegin || x == xEnd || y == yBegin || y == yEnd || z == zBegin || z == zEnd)
					m_MatrixAccess->SetPixel(x, y, z);
}



//
// CEffectsEngine
//
CEffectsEngine::CEffectsEngine(IMatrixAccess * MatrixAccess)
	: m_MatrixAccess(MatrixAccess)
{
	m_Effects.push_back(std::make_shared<CEffectExpandCubeToBorder>(m_MatrixAccess));
	m_Effects.push_back(std::make_shared<CEffectCollapseCubeTo777>(m_MatrixAccess));
	m_Effects.push_back(std::make_shared<CEffectExpandCubeFrom777To000>(m_MatrixAccess));
	m_Effects.push_back(std::make_shared<CEffectCollapseCubeFrom777To000>(m_MatrixAccess));
	m_Effects.push_back(std::make_shared<CEffectExpandCubeFrom000To777>(m_MatrixAccess));
	m_Effects.push_back(std::make_shared<CEffectCollapseCubeFromToCenter>(m_MatrixAccess));
	m_Effects.push_back(std::make_shared<CEffectPlanes>(m_MatrixAccess));

	PlayEffect(0);
}

// Public
void CEffectsEngine::RepeatCurrentEffect()
{
	PlayEffect(m_CurrentEffectIndex);
}

void CEffectsEngine::NextEffect()
{
	ForceShowNextEffect();
}

void CEffectsEngine::CallFrameFunc(uint32_t NFrame)
{
	if (NFrame != (uint32_t)(GetCurrentEffect()->GetFrameFuncType()))
		return;

	if (GetCurrentEffect()->IsNeedClearBeforeFrame())
		m_MatrixAccess->Clear();

	GetCurrentEffect()->FuncFrame(GetCurrentEffect()->GetCurrentFrame());
	GetCurrentEffect()->IncCurrentFrame();

	TryShowNextEffect();
}

// Private
void CEffectsEngine::PlayEffect(size_t EffectNumber)
{
	if (EffectNumber >= m_Effects.size())
		return;

	m_CurrentEffectIndex = EffectNumber;
	GetCurrentEffect()->Reset();

	if (GetCurrentEffect()->IsNeedClearBeforeInit())
		m_MatrixAccess->Clear();

	GetCurrentEffect()->FuncInit();
}

/*
 * Break current effect and show next
 */
void CEffectsEngine::ForceShowNextEffect()
{
	size_t nextEffectNumber = m_CurrentEffectIndex + 1;
	if (nextEffectNumber >= m_Effects.size())
		nextEffectNumber = 0;

	PlayEffect(nextEffectNumber);
}

/*
 * If current effect ended, then show next effect
 */
void CEffectsEngine::TryShowNextEffect()
{
	if (GetCurrentEffect()->IsPlaying())
		return;

	ForceShowNextEffect();
}

const std::shared_ptr<CEffect>& CEffectsEngine::GetCurrentEffect() const
{
	return m_Effects[m_CurrentEffectIndex];
}

