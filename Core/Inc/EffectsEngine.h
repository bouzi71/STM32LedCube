#ifndef __EFFECTSENGINE_H
#define __EFFECTSENGINE_H

#include <stm32f1xx_hal.h>
#include <memory>
#include <vector>

#include <MatrixAccess.h>

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

	void                                            Reset();
	void                                            IncCurrentFrame();

	EFrameFuncType                                  GetFrameFuncType() const;
	uint32_t                                        GetCurrentFrame() const;
	uint32_t                                        GetLenght() const;

	bool											IsPlaying() const;
	bool                                            IsNeedClearBeforeInit() const;
	bool                                            IsNeedClearBeforeFrame() const;

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
	void 											PlayEffect(size_t EffectNumber);
	void 											ForceShowNextEffect();
	void 											TryShowNextEffect();

	const std::shared_ptr<CEffect>&                 GetCurrentEffect() const;

private: // Variables
	std::vector<std::shared_ptr<CEffect>>			m_Effects;
	size_t											m_CurrentEffectIndex;
	IMatrixAccess *									m_MatrixAccess;
};

#endif
