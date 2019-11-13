
// General
#include <EffectsEngine.h>

// Additional
#include <EffectsLibrary.h>



//
// CEffectsEngine
//
CEffectsEngine::CEffectsEngine(ICubeController * CubeController)
	: m_CubeController(CubeController)
{
	m_RootCollection =  new CEffectsCollection(m_CubeController);

	AddEffects(m_RootCollection, m_CubeController);

	m_RootCollection->FuncInit();
}

void CEffectsEngine::RepeatCurrentEffect()
{
	m_RootCollection->PlayEffect(m_RootCollection->GetCurrentEffectNumber());
}

void CEffectsEngine::NextEffect()
{
	m_RootCollection->PlayNextEffect();
}

void CEffectsEngine::InvokeFuncFrame(EFrameFuncPeriod FramePeriod)
{
	m_RootCollection->InvokeFuncFrame(FramePeriod, UINT32_MAX);
}

