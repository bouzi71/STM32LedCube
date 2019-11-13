
// General
#include <EffectsLibrary.h>

// Additional
#include <Effect.h>
#include <Effect3D.h>
#include <EffectsCollection.h>

#include "Math/matrix4x4.h"
#include <cmath>

class CTestEffect : public CEffect3D
{
public:
	CTestEffect(ICubeController * CubeController)
		: CEffect3D(CubeController)
	{
		SetFramePeriod(EFrameFuncPeriod_3);
		SetLenght(25);

		PlaneY(4);
	}

	bool FuncFrame3D(uint32_t Frame) override final
	{
		const float rotYValue = (3.14f / 25.0f) * float(Frame);

		//Matrix4 trMat;
		//Matrix4::Translation(Vector3(0.0f, 0.0f, 0.0f), trMat);

		Matrix4 rotMatX;
		Matrix4::RotationX(rotYValue, rotMatX);

		//Matrix4 rotMatZ;
		//Matrix4::RotationZ(rotYValue, rotMatZ);

		//Matrix4 scaleMat;
		//Matrix4::Scaling(Vector3(0.7f, 1.0f, 0.7f), scaleMat);

		m_WorldMatrix = rotMatX;

		return true;
	}
};


//
// SNAKE
//
class CEffectSnake : public CEffect
{
public:
	CEffectSnake(ICubeController * CubeController)
		: CEffect(CubeController)
	{
		SetFramePeriod(EFrameFuncPeriod_3);
		SetLenght(65);
	}

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

			for (uint8_t z = 0; z < 7; z++)
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
	CEffectSpiral(ICubeController * CubeController)
		: CEffect(CubeController)
	{
		SetFramePeriod(EFrameFuncPeriod_3);
		SetLenght(79);
	}

	void FuncInit() override final
	{
		napr = NAPRAVLENIE_UP;

		minX = 0;
		minY = 0;

		maxX = 7;
		maxY = 7;

		posX = minX;
		posY = minY;

		SetClearBeforeInit(true);
		SetClearBeforeFrame(false);
	}

	void FuncFrame(uint32_t Frame) override final
	{
		for (uint32_t z = 0; z < 8; z++)
			SET_PIXEL(posX, posY, z);

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
	CEffectPlanes(ICubeController * CubeController)
		: CEffect(CubeController)
	{
		SetFramePeriod(EFrameFuncPeriod_5);
		SetLenght(16);
	}

	void FuncFrame(uint32_t Frame) override final
	{
		uint32_t t = Frame % 16;

		if (t == 15)
			return;

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
	CEffectExpandCubeToBorder(ICubeController * CubeController)
		: CEffect(CubeController)
	{
		SetFramePeriod(EFrameFuncPeriod_5);
		SetLenght(4);
	}

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
	CEffectCollapseCubeTo777(ICubeController * CubeController)
		: CEffect(CubeController)
	{
		SetFramePeriod(EFrameFuncPeriod_5);
		SetLenght(8);
	}

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
	CEffectExpandCubeFrom777To000(ICubeController * CubeController)
		: CEffect(CubeController)
	{
		SetFramePeriod(EFrameFuncPeriod_5);
		SetLenght(8);
	}

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
	CEffectCollapseCubeFrom777To000(ICubeController * CubeController)
		: CEffect(CubeController)
	{
		SetFramePeriod(EFrameFuncPeriod_5);
		SetLenght(8);
	}

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
	CEffectExpandCubeFrom000To777(ICubeController * CubeController)
		: CEffect(CubeController)
	{
		SetFramePeriod(EFrameFuncPeriod_5);
		SetLenght(8);
	}

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
	CEffectCollapseCubeFromToCenter(ICubeController * CubeController)
		: CEffect(CubeController)
	{
		SetFramePeriod(EFrameFuncPeriod_5);
		SetLenght(4);
	}

	void FuncFrame(uint32_t Frame) override final
	{
		uint32_t t = 3 - (Frame % 4);
		CubeOutline(3 - t, 4 + t, 3 - t, 4 + t, 3 - t, 4 + t);
	}
};

// -------------------------------------------------------------------

void AddEffects(IEffectsCollection* Collection, ICubeController * CubeController)
{
	Collection->AddEffect(new CTestEffect(CubeController));


	/*CEffectsCollection* cubeEffectCollection = new CEffectsCollection(CubeController);
	cubeEffectCollection->AddEffect(new CEffectExpandCubeToBorder(CubeController));
	cubeEffectCollection->AddEffect(new CEffectCollapseCubeTo777(CubeController));
	cubeEffectCollection->AddEffect(new CEffectExpandCubeFrom777To000(CubeController));
	cubeEffectCollection->AddEffect(new CEffectCollapseCubeFrom777To000(CubeController));
	cubeEffectCollection->AddEffect(new CEffectExpandCubeFrom000To777(CubeController));
	cubeEffectCollection->AddEffect(new CEffectCollapseCubeFromToCenter(CubeController));
	Collection->AddEffect(cubeEffectCollection);

	Collection->AddEffect(new CEffectPlanes(CubeController));
	Collection->AddEffect(new CEffectSpiral(CubeController));
	Collection->AddEffect(new CEffectSnake(CubeController));*/
}
