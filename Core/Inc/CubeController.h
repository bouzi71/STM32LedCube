#ifndef __CUBECONTROLLER_H
#define __CUBECONTROLLER_H

#include <stm32f1xx_hal.h>

#include <MatrixAccess.h>
#include <EffectsEngine.h>

class CCubeController : public IMatrixAccess
{
public:
	CCubeController();

	void 											Update();
	void 											BtnYellowClick();
	void 											BtnBlueClick();

	// IMatrixAccess
	void 											Clear() override;
	void 											Fill() override;
	void 											SetPixel(uint8_t x, uint8_t y, uint8_t z) override;
	void 											ClearPixel(uint8_t x, uint8_t y, uint8_t z) override;
	void 											TogglePixel(uint8_t x, uint8_t y, uint8_t z) override;
	bool 											GetPixel(uint8_t x, uint8_t y, uint8_t z) const override;

private: // Methods
	void 											WaitNextFrame();
	bool 											NextFramePresent();

	void 											ProcessFrame();
	void 											DrawMatrix();

private: // Variables
	uint8_t 										m_Matrix[8][8];

	// Frame processor
	uint32_t 										m_Frame;
	uint32_t 										m_Next3FramesEventCntr;
	uint32_t 										m_Next5FramesEventCntr;
	uint32_t 										m_Next10FramesEventCntr;
	uint32_t 										m_Next60FramesEventCntr;

	// Delay between frames
	uint32_t 										m_DelayEnd;

	CEffectsEngine 									m_EffectsEngine;
};

#endif
