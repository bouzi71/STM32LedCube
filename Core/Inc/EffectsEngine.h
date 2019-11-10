#ifndef __EFFECTSENGINE_H
#define __EFFECTSENGINE_H

#include <stm32f1xx_hal.h>

#include <Interfaces.h>
#include <EffectsCollection.h>


//
// CEffectsEngine
//
class CEffectsEngine
{
public:
	CEffectsEngine(ICubeController * CubeController);

	void											RepeatCurrentEffect();
	void											NextEffect();
	void											InvokeFuncFrame(EFrameFuncPeriod FramePeriod);

private: // Variables
	std::shared_ptr<CEffectsCollection>             m_RootCollection;

	ICubeController *								m_CubeController;
};

#endif
