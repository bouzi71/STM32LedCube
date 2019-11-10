
// General
#include <EffectsEngine.h>

// Additional
#include <string.h>


//
// SNAKE
//
class CEffectSnake : public CEffect
{
public:
	CEffectSnake(IMatrixAccess * MatrixAccess)
		: CEffect(EFrameFuncPeriod_3, 65, MatrixAccess)
	{}

	void FuncFrame(uint32_t Frame) override final
	{
		uint32_t t = Frame % 65;

		uint8_t beginVal = 0;
		if (t > cSnakeLenght)
			beginVal = t - cSnakeLenght;

		for (uint8_t i = beginVal; i < t; i++)
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

private:
	const uint32_t cSnakeLenght = 5;
};



//
// SPIRAL
//
class CEffectSpiral : public CEffect
{
public:
	CEffectSpiral(IMatrixAccess * MatrixAccess)
		: CEffect(EFrameFuncPeriod_3, 79, MatrixAccess)
	{}

	void FuncInit() override final
	{
		napr = NAPRAVLENIE_UP;

		minX = 0;
		minY = 0;

		maxX = 7;
		maxY = 7;

		posX = minX;
		posY = minY;
	}

	void FuncFrame(uint32_t Frame) override final
	{
		for (uint32_t z = 0; z < 8; z++)
			m_MatrixAccess->SetPixel(posX, posY, z);

		switch (napr)
		{
			case NAPRAVLENIE_UP:
			{
				if (posY + 1 >= (maxY + 1) || (GET_PIXEL(posX, posY + 1, 0) == 1))
				{
					napr = NAPRAVLENIE_RIGHT;
					return;
				}

				posY += 1;
			}
			break;

			case NAPRAVLENIE_RIGHT:
			{
				if ((posX + 1) >= (maxX + 1) || (GET_PIXEL(posX + 1, posY, 0) == 1))
				{
					napr = NAPRAVLENIE_DOWN;
					return;
				}

				posX += 1;
			}
			break;

			case NAPRAVLENIE_DOWN:
			{
				if (posY == minY || (GET_PIXEL(posX, posY - 1, 0) == 1))
				{
					napr = NAPRAVLENIE_LEFT;
					return;
				}

				posY -= 1;
			}
			break;

			case NAPRAVLENIE_LEFT:
			{
				if (posX == minX || (GET_PIXEL(posX - 1, posY, 0) == 1))
				{
					napr = NAPRAVLENIE_UP;
					return;
				}

				posX -= 1;
			}
			break;
		}
	}

private:
	enum ESpiralNapravlenie
	{
		NAPRAVLENIE_UP = 0,
		NAPRAVLENIE_RIGHT,
		NAPRAVLENIE_DOWN,
		NAPRAVLENIE_LEFT
	};

	ESpiralNapravlenie								napr;
	uint8_t											posX;
	uint8_t											posY;

	uint8_t											minX;
	uint8_t											minY;

	uint8_t											maxX;
	uint8_t											maxY;
};



//
// PLANES
//
class CEffectPlanes : public CEffect
{
public:
	CEffectPlanes(IMatrixAccess * MatrixAccess)
		: CEffect(EFrameFuncPeriod_5, 16, MatrixAccess)
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
		: CEffect(EFrameFuncPeriod_5, 4, MatrixAccess)
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
		: CEffect(EFrameFuncPeriod_5, 8, MatrixAccess)
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
		: CEffect(EFrameFuncPeriod_5, 8, MatrixAccess)
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
		: CEffect(EFrameFuncPeriod_5, 8, MatrixAccess)
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
		: CEffect(EFrameFuncPeriod_5, 8, MatrixAccess)
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
		: CEffect(EFrameFuncPeriod_5, 4, MatrixAccess)
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

CEffect::CEffect(EFrameFuncPeriod FramePeriod, uint32_t Lenght, IMatrixAccess * MatrixAccess)
	: m_FramePeriod(FramePeriod)
	, m_CleanCubeBeforeInit(false)
	, m_CleanCubeBeforeFrame(true)
	, m_Lenght(Lenght)
	, m_MatrixAccess(MatrixAccess)
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

uint32_t CEffect::GetLenght() const
{
	return m_Lenght;
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



//
// CEffectsCollection
//
CEffectsCollection::CEffectsCollection(IMatrixAccess* MatrixAccess)
    : m_CurrentEffectFrame(0)
	, m_CurrentEffectIndex(0)
	, m_MatrixAccess(MatrixAccess)
{}


// IEffect
void CEffectsCollection::FuncInit()
{
	PlayEffect(0);
}

void CEffectsCollection::FuncFrame(uint32_t Frame)
{

}

void CEffectsCollection::InvokeFuncFrame(EFrameFuncPeriod FramePeriod, uint32_t /*Frame*/)
{
	if (FramePeriod != (GetCurrentEffect()->GetFramePeriod()))
		return;

	if (GetCurrentEffect()->IsNeedClearBeforeFrame())
		m_MatrixAccess->Clear();

	GetCurrentEffect()->InvokeFuncFrame(FramePeriod, m_CurrentEffectFrame);
	m_CurrentEffectFrame += 1;

	if (m_CurrentEffectFrame >= GetCurrentEffect()->GetLenght())
		PlayNextEffect();
}

EFrameFuncPeriod CEffectsCollection::GetFramePeriod() const
{
	return GetCurrentEffect()->GetFramePeriod();
}

uint32_t CEffectsCollection::GetLenght() const
{
	uint32_t lenght = 0;
	for (const auto& e : m_Effects)
		lenght += e->GetLenght();
	return lenght;
}

bool CEffectsCollection::IsNeedClearBeforeInit() const
{
	return GetCurrentEffect()->IsNeedClearBeforeInit();
}

bool CEffectsCollection::IsNeedClearBeforeFrame() const
{
	return GetCurrentEffect()->IsNeedClearBeforeFrame();
}


// IEffectsCollection
void CEffectsCollection::AddEffect(std::shared_ptr<IEffect> Effect)
{
	m_Effects.push_back(Effect);
}

size_t CEffectsCollection::GetCurrentEffectNumber() const
{
	return m_CurrentEffectIndex;
}

const std::shared_ptr<IEffect>& CEffectsCollection::GetCurrentEffect() const
{
	return m_Effects[m_CurrentEffectIndex];
}

void CEffectsCollection::PlayEffect(size_t EffectNumber)
{
	if (EffectNumber >= m_Effects.size())
		EffectNumber = 0;

	m_CurrentEffectFrame = 0;
	m_CurrentEffectIndex = EffectNumber;

	if (GetCurrentEffect()->IsNeedClearBeforeInit())
		m_MatrixAccess->Clear();

	GetCurrentEffect()->FuncInit();
}

void CEffectsCollection::PlayNextEffect()
{
	PlayEffect(m_CurrentEffectIndex + 1);
}


//
// CEffectsEngine
//
CEffectsEngine::CEffectsEngine(IMatrixAccess * MatrixAccess)
	: m_MatrixAccess(MatrixAccess)
{
	m_RootCollection = std::make_shared<CEffectsCollection>(m_MatrixAccess);

	std::shared_ptr<CEffectsCollection> cubeEffectCollection = std::make_shared<CEffectsCollection>(m_MatrixAccess);
	cubeEffectCollection->AddEffect(std::make_shared<CEffectExpandCubeToBorder>(m_MatrixAccess));
	cubeEffectCollection->AddEffect(std::make_shared<CEffectCollapseCubeTo777>(m_MatrixAccess));
	cubeEffectCollection->AddEffect(std::make_shared<CEffectExpandCubeFrom777To000>(m_MatrixAccess));
	cubeEffectCollection->AddEffect(std::make_shared<CEffectCollapseCubeFrom777To000>(m_MatrixAccess));
	cubeEffectCollection->AddEffect(std::make_shared<CEffectExpandCubeFrom000To777>(m_MatrixAccess));
	cubeEffectCollection->AddEffect(std::make_shared<CEffectCollapseCubeFromToCenter>(m_MatrixAccess));
	m_RootCollection->AddEffect(cubeEffectCollection);

	m_RootCollection->AddEffect(std::make_shared<CEffectPlanes>(m_MatrixAccess));
	m_RootCollection->AddEffect(std::make_shared<CEffectSpiral>(m_MatrixAccess));
	m_RootCollection->AddEffect(std::make_shared<CEffectSnake>(m_MatrixAccess));

	m_RootCollection->FuncInit();
}

// Public
void CEffectsEngine::RepeatCurrentEffect()
{
	m_RootCollection->PlayEffect(m_RootCollection->GetCurrentEffectNumber());
}

void CEffectsEngine::NextEffect()
{
	m_RootCollection->PlayNextEffect();
}

void CEffectsEngine::InvokeFuncFrame(EFrameFuncPeriod FramePeriod)
{
	m_RootCollection->InvokeFuncFrame(FramePeriod, UINT32_MAX);
}
