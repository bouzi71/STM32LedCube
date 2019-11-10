#ifndef __CUBECONTROLLER_H
#define __CUBECONTROLLER_H

#include <stm32f1xx_hal.h>

#include <Interfaces.h>
#include <EffectsEngine.h>


class CCubeController
		: public IMatrixAccess
{
public:
	void                                            Initialize();
	void 											Update();

	// IMatrixAccess
	void 											Clear() override;
	void 											Fill() override;
	void 											SetPixel(uint8_t x, uint8_t y, uint8_t z) override;
	void 											ClearPixel(uint8_t x, uint8_t y, uint8_t z) override;
	void 											TogglePixel(uint8_t x, uint8_t y, uint8_t z) override;
	bool 											GetPixel(uint8_t x, uint8_t y, uint8_t z) const override;

protected:
	void 											BtnYellowClick();
	void 											BtnBlueClick();

private: // Methods
	void 											WaitNextFrame();
	bool 											NextFramePresent() const;

	void                                            ProcessInput();
	void 											ProcessFrame();
	void 											DrawMatrix();

private: // Variables
	uint8_t 										m_Matrix[8][8];

	bool                                            m_BtnYellowPressed;
	bool                                            m_BtnBluePressed;

	// Delay between frames
	uint32_t 										m_DelayEnd;

	// Frame processor
	uint32_t 										m_Frame;
	uint32_t 										m_Next3FramesEventCntr;
	uint32_t 										m_Next5FramesEventCntr;
	uint32_t 										m_Next10FramesEventCntr;
	uint32_t 										m_Next60FramesEventCntr;

	std::shared_ptr<CEffectsEngine> 				m_EffectsEngine;
};

#endif
