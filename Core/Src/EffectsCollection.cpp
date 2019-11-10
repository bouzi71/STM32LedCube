
// General
#include <EffectsCollection.h>


//
// CEffectsCollection
//
CEffectsCollection::CEffectsCollection(ICubeController * CubeController)
    : m_RepeatCnt(1)
	, m_CurrentEffectFrame(0)
	, m_CurrentEffectIndex(0)
	, m_CubeController(CubeController)
{}


// IEffect
void CEffectsCollection::FuncInit()
{
	PlayEffect(0);
}

void CEffectsCollection::FuncFrame(uint32_t Frame)
{

}

void CEffectsCollection::InvokeFuncFrame(EFrameFuncPeriod FramePeriod, uint32_t /*Frame*/)
{
	if (FramePeriod != (GetCurrentEffect()->GetFramePeriod()))
		return;

	if (GetCurrentEffect()->IsNeedClearBeforeFrame())
		m_CubeController->GetMatrix()->Clear();

	GetCurrentEffect()->InvokeFuncFrame(FramePeriod, m_CurrentEffectFrame);
	m_CurrentEffectFrame += 1;

	if (m_CurrentEffectFrame >= GetCurrentEffect()->GetLenght())
		PlayNextEffect();
}

EFrameFuncPeriod CEffectsCollection::GetFramePeriod() const
{
	return GetCurrentEffect()->GetFramePeriod();
}

void CEffectsCollection::SetFramePeriod(EFrameFuncPeriod Period)
{
	for (const auto& e : m_Effects)
		e->SetFramePeriod(Period);
}

uint32_t CEffectsCollection::GetLenght() const
{
	uint32_t lenght = 0;
	for (const auto& e : m_Effects)
		lenght += e->GetLenght();
	return lenght;
}


void CEffectsCollection::SetLenght(uint32_t /*Value*/)
{
	// Do nothing because every effect has own lenght
}

uint32_t CEffectsCollection::GetRepeatCount() const
{
	return m_RepeatCnt;
}

void CEffectsCollection::SetRepeatCount(uint32_t Value)
{
	m_RepeatCnt = Value;
}

bool CEffectsCollection::IsNeedClearBeforeInit() const
{
	return GetCurrentEffect()->IsNeedClearBeforeInit();
}

bool CEffectsCollection::IsNeedClearBeforeFrame() const
{
	return GetCurrentEffect()->IsNeedClearBeforeFrame();
}


// IEffectsCollection
void CEffectsCollection::AddEffect(std::shared_ptr<IEffect> Effect)
{
	m_Effects.push_back(Effect);
}

size_t CEffectsCollection::GetCurrentEffectNumber() const
{
	return m_CurrentEffectIndex;
}

const std::shared_ptr<IEffect>& CEffectsCollection::GetCurrentEffect() const
{
	return m_Effects[m_CurrentEffectIndex];
}

void CEffectsCollection::PlayEffect(size_t EffectNumber)
{
	if (EffectNumber >= m_Effects.size())
		EffectNumber = 0;

	m_CubeController->BlinkBlueLed();

	m_CurrentEffectFrame = 0;
	m_CurrentEffectIndex = EffectNumber;

	if (GetCurrentEffect()->IsNeedClearBeforeInit())
		m_CubeController->GetMatrix()->Clear();

	GetCurrentEffect()->FuncInit();
}

void CEffectsCollection::PlayNextEffect()
{
	PlayEffect(m_CurrentEffectIndex + 1);
}
