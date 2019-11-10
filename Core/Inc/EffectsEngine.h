#ifndef __EFFECTSENGINE_H
#define __EFFECTSENGINE_H

#include <stm32f1xx_hal.h>
#include <vector>

#include <Interfaces.h>


//
// CEffect
//
class CEffect
		: public IEffect
{
public:
	CEffect();
	CEffect(EFrameFuncPeriod FramePeriod, uint32_t Lenght, IMatrixAccess * MatrixAccess);

	// IEffect
	virtual void									FuncInit() override;
	virtual void									FuncFrame(uint32_t Frame) override;
	void                                            InvokeFuncFrame(EFrameFuncPeriod FramePeriod, uint32_t Frame);
	EFrameFuncPeriod                                GetFramePeriod() const override;
	uint32_t                                        GetLenght() const override;
	bool                                            IsNeedClearBeforeInit() const override;
	bool                                            IsNeedClearBeforeFrame() const override;

protected:
	void 											PlaneX(uint32_t plane);
	void 											PlaneY(uint32_t plane);
	void 											PlaneZ(uint32_t plane);
	void 											Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd);
	void 											CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd);

#define SET_PIXEL(x, y, z)     (m_MatrixAccess->SetPixel(x, y, z));
#define CLEAR_PIXEL(x, y, z)   (m_MatrixAccess->ClearPixel(x, y, z));
#define TOGGLE_PIXEL(x, y, z)  (m_MatrixAccess->TogglePixel(x, y, z));
#define GET_PIXEL(x, y, z)     (m_MatrixAccess->GetPixel(x, y, z))

private:
	EFrameFuncPeriod								m_FramePeriod;

	bool											m_CleanCubeBeforeInit;
	bool											m_CleanCubeBeforeFrame;

	uint32_t										m_Lenght;

protected:
	IMatrixAccess *									m_MatrixAccess;
};


//
// CEffectsCollection
//
class CEffectsCollection
	: public IEffect
	, public IEffectsCollection
{
public:
	CEffectsCollection(IMatrixAccess * MatrixAccess);

	// IEffect
	void											FuncInit() override;
	void											FuncFrame(uint32_t Frame) override;
	void                                            InvokeFuncFrame(EFrameFuncPeriod FramePeriod, uint32_t Frame);
	EFrameFuncPeriod                          		GetFramePeriod() const override;
	uint32_t                                        GetLenght() const override;
	bool                                            IsNeedClearBeforeInit() const override;
	bool                                            IsNeedClearBeforeFrame() const override;

	// IEffectsCollection
	void											AddEffect(std::shared_ptr<IEffect> Effect) override;
	size_t                                          GetCurrentEffectNumber() const override;
	const std::shared_ptr<IEffect>&                 GetCurrentEffect() const override;
	void 											PlayEffect(size_t EffectNumber) override;
	void 											PlayNextEffect() override;

private:
	std::vector<std::shared_ptr<IEffect>>			m_Effects;

	uint32_t                                        m_CurrentEffectFrame;
	size_t											m_CurrentEffectIndex;

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
	void											InvokeFuncFrame(EFrameFuncPeriod FramePeriod);

private: // Variables
	std::shared_ptr<CEffectsCollection>             m_RootCollection;

	IMatrixAccess *									m_MatrixAccess;
};

#endif
