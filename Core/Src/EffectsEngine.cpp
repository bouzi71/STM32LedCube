
// General
#include <EffectsEngine.h>
#include <string.h>

// Defines
#define EFFECT_COUNT   7
#define SET_PIXEL(x, y, z)     (m_Matrix[y][z] |=  (0x01 << (x)));
#define CLEAR_PIXEL(x, y, z)   (m_Matrix[y][z] &= ~(0x01 << (x)));
#define TOGGLE_PIXEL(x, y, z)  (m_Matrix[y][z] ^=  (0x01 << (x)));
#define GET_PIXEL(x, y, z)     ((m_Matrix[y][z] & (0x01 << (x))) == (0x01 << (x)))


// Effect engine
SEffectDescription g_AllEffects[EFFECT_COUNT];
uint32_t g_CurrentEffectNumber = 0;
SEffectDescription* g_CurrentEffect = NULL;

void Fill(uint8_t value)
{
	memset(&m_Matrix[0][0], value, 64);
}

void PlaneX(uint32_t plane)
{
	for (uint32_t y = 0; y < 8; y++)
		for (uint32_t z = 0; z < 8; z++)
			SET_PIXEL(plane, y, z);
}

void PlaneY(uint32_t plane)
{
	for (int x = 0; x < 8; x++)
		for (uint32_t z = 0; z < 8; z++)
			SET_PIXEL(x, plane, z);
}

void PlaneZ(uint32_t plane)
{
	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t y = 0; y < 8; y++)
			SET_PIXEL(x, y, plane);
}

void Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				SET_PIXEL(x, y, z);
}


void CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				if (x == xBegin || x == xEnd || y == yBegin || y == yEnd || z == zBegin || z == zEnd)
					SET_PIXEL(x, y, z);
}


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


void DrawLines111(uint32_t frame)
{
	uint32_t t = frame % 16;
	if (t >= 8)
		t = 14 - t;

	PlaneX(t);
	PlaneY(t);
	PlaneZ(t);
}

void DrawSnake111(uint32_t frame)
{
	DrawSnakeT(frame % 65);
}



// Cube BEGIN
void DrawCubeFromCenterToBorder(uint32_t frame)
{
	uint32_t t = frame % 4;
	CubeOutline(3 - t, 4 + t, 3 - t, 4 + t, 3 - t, 4 + t);
}

void DrawCubeFromBorderToCenter(uint32_t frame)
{
	uint32_t t = frame % 4;
	t = 3 - t;

	CubeOutline(3 - t, 4 + t, 3 - t, 4 + t, 3 - t, 4 + t);
}

void DrawCube222(uint32_t frame)
{
	uint32_t t = frame % 8;
	CubeOutline(0, t, 0, t, 0, t);
}

void DrawCube333(uint32_t frame)
{
	uint32_t t = frame % 8;
	CubeOutline(t, 7, t, 7, t, 7);
}

void DrawCube444(uint32_t frame)
{
	uint32_t t = frame % 8;
	CubeOutline(7 - t, 7, 7 - t, 7, 7 - t, 7);
}

void DrawCube555(uint32_t frame)
{
	uint32_t t = frame % 8;
	CubeOutline(0, 7 - t , 0, 7 - t, 0, 7 - t);
}
// Cube END



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


//
// Private
//

void PlayEffect(uint32_t EffectNumber)
{
	if (EffectNumber >= EFFECT_COUNT)
		return;

	g_CurrentEffectNumber = EffectNumber;
	g_CurrentEffect = &g_AllEffects[g_CurrentEffectNumber];
	g_CurrentEffect->CurrentFrame = 0;

	if (g_CurrentEffect->CleanCubeBeforeInit)
		Fill(0x00);

	if (g_CurrentEffect->FuncInit != NULL)
		(g_CurrentEffect->FuncInit)();
}

/*
 * Break current effect and show next
 */
void ForceShowNextEffect()
{
	uint32_t nextEffectNumber = g_CurrentEffectNumber + 1;
	if (nextEffectNumber >= EFFECT_COUNT)
		nextEffectNumber = 0;

	PlayEffect(nextEffectNumber);
}

/*
 * If current effect ended, then show next effect
 */
void TryShowNextEffect()
{
	if (IsEffectPlaying(g_CurrentEffect))
		return;

	ForceShowNextEffect();
}



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

bool CEffect::IsPlaying() const
{
	return CurrentFrame < Lenght;
}


//
// CEffectsEngine
//
CEffectsEngine::CEffectsEngine(IMatrixAccess * MatrixAccess)
	: m_MatrixAccess(MatrixAccess)
{
	CEffect effect;

	// From center borders
	effect = CEffect(EFrameFuncType5, 4, m_MatrixAccess);
	effect.FuncFrame = DrawCubeFromCenterToBorder;
	m_Effects.push_back(effect);

	// From borders to 777
	effect = CEffect(EFrameFuncType5, 8, m_MatrixAccess);
	effect.FuncFrame = DrawCube333;
	m_Effects.push_back(effect);

	// From 777 to 000
	effect = CEffect(EFrameFuncType5, 8, m_MatrixAccess);
	effect.FuncFrame = DrawCube444;
	m_Effects.push_back(effect);

	effect = CEffect(EFrameFuncType5, 8, m_MatrixAccess);
	effect.FuncFrame = DrawCube555;
	m_Effects.push_back(effect);

	effect = CEffect(EFrameFuncType5, 8, m_MatrixAccess);
	effect.FuncFrame = DrawCube222;
	m_Effects.push_back(effect);

	effect = CEffect(EFrameFuncType5, 4, m_MatrixAccess);
	effect.FuncFrame = DrawCubeFromBorderToCenter;
	m_Effects.push_back(effect);

	effect = CEffect(EFrameFuncType5, 16, m_MatrixAccess);
	effect.FuncFrame = DrawLines111;
	m_Effects.push_back(effect);

	PlayEffect(0);
}



//
// Public
//

void CEffectsEngine::RepeatCurrentEffect()
{
	PlayEffect(g_CurrentEffectNumber);
}

void CEffectsEngine::NextEffect()
{
	ForceShowNextEffect();
}

void CEffectsEngine::CallFrameFunc(CEffect* Effect)
{
	if (Effect->CleanCubeBeforeFrame)
		m_MatrixAccess->Clear();

	(Effect->FuncFrame)(g_CurrentEffect->CurrentFrame);
	g_CurrentEffect->CurrentFrame += 1;

	TryShowNextEffect();
}


