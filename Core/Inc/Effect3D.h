#ifndef __EFFECT3D_H
#define __EFFECT3D_H

#include <Interfaces.h>
#include <Effect.h>

#include "../Src/Math/matrix4x4.h"
#include <vector>

class CEffect3D : public CEffect
{
public:
	CEffect3D(ICubeController * CubeController);

	void                                   FuncFrame(uint32_t Frame) override final;

protected:
	void                                   ClearFigure();
	Vector3                                ToVector3(uint8_t x, uint8_t y, uint8_t z) const;
	virtual bool                           FuncFrame3D(uint32_t Frame);

protected:
	void 									PlaneX(uint32_t plane) override final;
	void 									PlaneY(uint32_t plane) override final;
	void 									PlaneZ(uint32_t plane) override final;
	void 									Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd) override final;
	void 									CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd) override final;

private:
	void                                    ApplyPointToMatrix(const Vector3& Vector);

protected:
	Matrix4                                 m_WorldMatrix;
	std::vector<Vector3>                    m_Fugure;

private:
	const float                             cMultiplyValue = 7.0f;
	const Vector3                           cOffsetVector = Vector3(0.5f, 0.5f, 0.5f);
};

#endif
