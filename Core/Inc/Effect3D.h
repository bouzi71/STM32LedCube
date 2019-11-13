#ifndef __EFFECT3D_H
#define __EFFECT3D_H

#include <Interfaces.h>
#include <Effect.h>
#include <Figure.h>

#include "../Src/Math/matrix4x4.h"
#include <vector>

class CEffect3D : public CEffect
{
public:
	enum EDrawMode
	{
		EDrawMode_Set = 0,
		EDrawMode_Clear,
		EDrawMode_Toggle
	};

public:
	CEffect3D(ICubeController * CubeController);

	// IEffect
	void                                   			FuncFrame(uint32_t Frame) override final;
	bool                                            IsNeedClearBeforeInit() const override final;
	bool                                            IsNeedClearBeforeFrame() const override final;

protected:
	float                                  			GetLenghtFloat() const;
	virtual bool                           			FuncFrame3D(uint32_t FrameUint, float FrameFloat);

protected:
	virtual void                                   	SetClearBeforeInit(bool Value) override final;
	virtual void                                    SetClearBeforeFrame(bool Value) override final;
	void                                            SetDrawMode(EDrawMode DrawMode);

protected:
	void 											LineX(uint32_t planeY, uint32_t planeZ) override final;
	void 											LineY(uint32_t planeX, uint32_t planeZ) override final;
	void 											LineZ(uint32_t planeX, uint32_t planeY) override final;
	void 											PlaneX(uint32_t plane) override final;
	void 											PlaneY(uint32_t plane) override final;
	void 											PlaneZ(uint32_t plane) override final;
	void 											Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd) override final;
	void 											CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd) override final;

private:
	void                                    		ApplyPointToMatrix(const Vector3& Vector);

private:
	EDrawMode                                       m_DrawMode;
	bool                                            m_Effect3DIsNeedCleadBeforeFrame;

protected:
	Matrix4                                 		m_WorldMatrix;
	CFugure3D                    		            m_Fugure;
};

#endif
