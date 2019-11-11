#ifndef __CUBECONTROLLER_H
#define __CUBECONTROLLER_H

#include <stm32f1xx_hal.h>

#include <Interfaces.h>
#include <LedMatrix.h>
#include <EffectsEngine.h>


class CCubeController
	: public ICubeController
{
public:
	void                                            Initialize();
	void 											Update();

	// ICubeController
	void                                            BlinkYellowLed() override;
	void                                            BlinkBlueLed() override;
	void                                            GoToErrorState() override;
	IMatrixAccess *                                 GetMatrix() override;

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
	CLedMatrix                                      m_LedMatrix;

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

	CEffectsEngine* 								m_EffectsEngine;
};

#endif
