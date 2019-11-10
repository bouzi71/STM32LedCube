#ifndef __EFFECTSCOLLECTION_H
#define __EFFECTSCOLLECTION_H

#include <stm32f1xx_hal.h>
#include <vector>

#include <Interfaces.h>


//
// CEffectsCollection
//
class CEffectsCollection
	: public IEffect
	, public IEffectsCollection
{
public:
	CEffectsCollection(ICubeController * CubeController);

	// IEffect
	void											FuncInit() override;
	void											FuncFrame(uint32_t Frame) override;
	void                                            InvokeFuncFrame(EFrameFuncPeriod FramePeriod, uint32_t Frame);

	EFrameFuncPeriod                          		GetFramePeriod() const override;
	void             								SetFramePeriod(EFrameFuncPeriod Period) override;
	uint32_t                                        GetLenght() const override;
	virtual void                                    SetLenght(uint32_t Value) override;
	uint32_t                                        GetRepeatCount() const override;
	virtual void                                    SetRepeatCount(uint32_t Value) override;
	bool                                            IsNeedClearBeforeInit() const override;
	bool                                            IsNeedClearBeforeFrame() const override;

	// IEffectsCollection
	void											AddEffect(std::shared_ptr<IEffect> Effect) override;
	size_t                                          GetCurrentEffectNumber() const override;
	const std::shared_ptr<IEffect>&                 GetCurrentEffect() const override;
	void 											PlayEffect(size_t EffectNumber) override;
	void 											PlayNextEffect() override;

private:
	uint32_t                                        m_RepeatCnt;

	std::vector<std::shared_ptr<IEffect>>			m_Effects;

	uint32_t                                        m_CurrentEffectFrame;
	size_t											m_CurrentEffectIndex;

	ICubeController *								m_CubeController;

};

#endif
