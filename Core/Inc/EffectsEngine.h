#ifndef __EFFECTSENGINE_H
#define __EFFECTSENGINE_H

#include <stm32f1xx_hal.h>

#include <MatrixAccess.h>
#include <vector>

//
// Types
//

enum EFrameFuncType
{
	EFrameFuncType1 = 1,
	EFrameFuncType3 = 3,
	EFrameFuncType5 = 5,
	EFrameFuncType10 = 10,
	EFrameFuncType60 = 60
};



//
// CEffect
//
class CEffect
{
public:
	CEffect();
	CEffect(EFrameFuncType FrameFuncType, uint32_t Lenght, IMatrixAccess * MatrixAccess);

	virtual void									FuncInit();
	virtual void									FuncFrame(uint32_t Frame);

	bool											IsPlaying() const;


protected:
	void 											PlaneX(uint32_t plane);
	void 											PlaneY(uint32_t plane);
	void 											PlaneZ(uint32_t plane);
	void 											Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd);
	void 											CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd);

private:
	EFrameFuncType									m_FrameFuncType;

	bool											m_CleanCubeBeforeInit;
	bool											m_CleanCubeBeforeFrame;

	uint32_t										m_CurrentFrame;
	uint32_t										m_Lenght;

	IMatrixAccess *									m_MatrixAccess;
};



//
// CEffectsEngine
//
class CEffectsEngine
{
public:
	CEffectsEngine(IMatrixAccess * MatrixAccess);

	void											RepeatCurrentEffect();
	void											NextEffect();
	void											CallFrameFunc(uint32_t NFrame);

private: // Methods


private: // Variables
	std::vector<CEffect>							m_Effects;
	size_t											m_CurrentEffect;
	IMatrixAccess *									m_MatrixAccess;
};

#endif
