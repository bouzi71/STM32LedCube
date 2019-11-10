
// General
#include <EffectsEngine.h>

// Additional
#include <EffectsLibrary.h>
#include <string.h>


//
// CEffect
//
CEffect::CEffect()
{}

CEffect::CEffect(EFrameFuncPeriod FramePeriod, uint32_t Lenght, IMatrixAccess * MatrixAccess)
	: m_FramePeriod(FramePeriod)
	, m_CleanCubeBeforeInit(false)
	, m_CleanCubeBeforeFrame(true)
	, m_Lenght(Lenght)
	, m_MatrixAccess(MatrixAccess)
{}


// IEffect
void CEffect::FuncInit()
{}

void CEffect::FuncFrame(uint32_t /*Frame*/)
{}

void CEffect::InvokeFuncFrame(EFrameFuncPeriod /*FramePeriod*/, uint32_t Frame)
{
	FuncFrame(Frame);
}

EFrameFuncPeriod CEffect::GetFramePeriod() const
{
	return m_FramePeriod;
}

uint32_t CEffect::GetLenght() const
{
	return m_Lenght;
}

bool CEffect::IsNeedClearBeforeInit() const
{
	return m_CleanCubeBeforeInit;
}

bool CEffect::IsNeedClearBeforeFrame() const
{
	return m_CleanCubeBeforeFrame;
}



//
// Protected
//
void CEffect::PlaneX(uint32_t plane)
{
	for (uint32_t y = 0; y < 8; y++)
		for (uint32_t z = 0; z < 8; z++)
			SET_PIXEL(plane, y, z);
}

void CEffect::PlaneY(uint32_t plane)
{
	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t z = 0; z < 8; z++)
			SET_PIXEL(x, plane, z);
}

void CEffect::PlaneZ(uint32_t plane)
{
	for (uint32_t x = 0; x < 8; x++)
		for (uint32_t y = 0; y < 8; y++)
			SET_PIXEL(x, y, plane);
}

void CEffect::Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				SET_PIXEL(x, y, z);
}

void CEffect::CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd)
{
	for (uint32_t x = xBegin; x <= xEnd; x++)
		for (uint32_t y = yBegin; y <= yEnd; y++)
			for (uint32_t z = zBegin; z <= zEnd; z++)
				if (x == xBegin || x == xEnd || y == yBegin || y == yEnd || z == zBegin || z == zEnd)
					SET_PIXEL(x, y, z);
}



//
// CEffectsCollection
//
CEffectsCollection::CEffectsCollection(IMatrixAccess* MatrixAccess)
    : m_CurrentEffectFrame(0)
	, m_CurrentEffectIndex(0)
	, m_MatrixAccess(MatrixAccess)
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
		m_MatrixAccess->Clear();

	GetCurrentEffect()->InvokeFuncFrame(FramePeriod, m_CurrentEffectFrame);
	m_CurrentEffectFrame += 1;

	if (m_CurrentEffectFrame >= GetCurrentEffect()->GetLenght())
		PlayNextEffect();
}

EFrameFuncPeriod CEffectsCollection::GetFramePeriod() const
{
	return GetCurrentEffect()->GetFramePeriod();
}

uint32_t CEffectsCollection::GetLenght() const
{
	uint32_t lenght = 0;
	for (const auto& e : m_Effects)
		lenght += e->GetLenght();
	return lenght;
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

	m_CurrentEffectFrame = 0;
	m_CurrentEffectIndex = EffectNumber;

	if (GetCurrentEffect()->IsNeedClearBeforeInit())
		m_MatrixAccess->Clear();

	GetCurrentEffect()->FuncInit();
}

void CEffectsCollection::PlayNextEffect()
{
	PlayEffect(m_CurrentEffectIndex + 1);
}


//
// CEffectsEngine
//
CEffectsEngine::CEffectsEngine(IMatrixAccess * MatrixAccess)
	: m_MatrixAccess(MatrixAccess)
{
	m_RootCollection = std::make_shared<CEffectsCollection>(m_MatrixAccess);

	AddEffects(m_RootCollection, m_MatrixAccess);

	m_RootCollection->FuncInit();
}

// Public
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
