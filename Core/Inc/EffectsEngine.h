#ifndef __EFFECTSENGINE_H
#define __EFFECTSENGINE_H

#include "stm32f1xx_hal.h"

#include "MatrixAccess.h"
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

class CEffect
{
public:
	CEffect();
	CEffect(EFrameFuncType FrameFuncType, uint32_t Lenght, IMatrixAccess * MatrixAccess);

	virtual void									FuncInit();
	virtual void									FuncFrame(uint32_t Frame);

	bool											IsPlaying() const;

private:
	EFrameFuncType									m_FrameFuncType;

	bool											m_CleanCubeBeforeInit;
	bool											m_CleanCubeBeforeFrame;

	uint32_t										m_CurrentFrame;
	uint32_t										m_Lenght;

	IMatrixAccess *									m_MatrixAccess;
};


class CEffectsEngine
{
public:
	CEffectsEngine(IMatrixAccess * MatrixAccess);

	void											RepeatCurrentEffect();
	void											NextEffect();
	void											CallFrameFunc(CEffect* Effect);

private: // Methods


private: // Variables
	std::vector<CEffect>							m_Effects;
	size_t											m_CurrentEffect;
	IMatrixAccess *									m_MatrixAccess;
};

#endif
