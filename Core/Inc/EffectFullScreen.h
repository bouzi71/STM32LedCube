#ifndef __EFFECTFULLSCREEN_H
#define __EFFECTFULLSCREEN_H

#include <Interfaces.h>
#include <Effect.h>
#include <vector>

struct SPoint
{
	uint8_t x, y, z;
};

class CEffectFullScreen : public CEffect
{
public:
	CEffectFullScreen(ICubeController * CubeController);

	// IEffect
	virtual void									FuncInit() override;
	void                                   			FuncFrame(uint32_t Frame) override final;

protected:
	virtual bool                           			FuncFrameFullScreen(uint32_t Frame, uint8_t X, uint8_t Y, uint8_t Z);

protected:
	bool                                		    m_Points[8][8][8];
	uint8_t                                         m_X, m_Y, m_Z;
};

#endif
