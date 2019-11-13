#ifndef __EFFECTSENGINE_H
#define __EFFECTSENGINE_H

#include <Interfaces.h>
#include <EffectsCollection.h>

class CEffectsEngine
{
public:
	CEffectsEngine(ICubeController * CubeController);

	void											RepeatCurrentEffect();
	void											NextEffect();
	void											InvokeFuncFrame(EFrameFuncPeriod FramePeriod);

private:
	CEffectsCollection *                            m_RootCollection;
	ICubeController *								m_CubeController;
};

#endif
