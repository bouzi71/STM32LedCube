
// General
#include <EffectsLibrary.h>

// Additional
#include <EffectsEngine.h>

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

void AddEffects(std::shared_ptr<IEffectsCollection> Collection, IMatrixAccess * MatrixAccess)
{
	std::shared_ptr<CEffectsCollection> cubeEffectCollection = std::make_shared<CEffectsCollection>(MatrixAccess);
	cubeEffectCollection->AddEffect(std::make_shared<CEffectExpandCubeToBorder>(MatrixAccess));
	cubeEffectCollection->AddEffect(std::make_shared<CEffectCollapseCubeTo777>(MatrixAccess));
	cubeEffectCollection->AddEffect(std::make_shared<CEffectExpandCubeFrom777To000>(MatrixAccess));
	cubeEffectCollection->AddEffect(std::make_shared<CEffectCollapseCubeFrom777To000>(MatrixAccess));
	cubeEffectCollection->AddEffect(std::make_shared<CEffectExpandCubeFrom000To777>(MatrixAccess));
	cubeEffectCollection->AddEffect(std::make_shared<CEffectCollapseCubeFromToCenter>(MatrixAccess));
	Collection->AddEffect(cubeEffectCollection);

	Collection->AddEffect(std::make_shared<CEffectPlanes>(MatrixAccess));
	Collection->AddEffect(std::make_shared<CEffectSpiral>(MatrixAccess));
	Collection->AddEffect(std::make_shared<CEffectSnake>(MatrixAccess));
}
