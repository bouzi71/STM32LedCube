
// General
#include <CubeController.h>

// Additional
#include <string.h>
#include <main.h>
#include <spi.h>

// Defines
#define ONE_FRAME_TIME (1000 / 60)


//
// CCubeController
//
void CCubeController::Initialize()
{
	Clear();

	m_BtnYellowPressed = false;
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);

	m_BtnBluePressed = false;
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);

	m_DelayEnd = 0;

	m_Frame = 0;
	m_Next3FramesEventCntr = 0;
	m_Next5FramesEventCntr = 0;
	m_Next10FramesEventCntr = 0;
	m_Next60FramesEventCntr = 0;

	m_EffectsEngine = std::make_shared<CEffectsEngine>(this);
}

void CCubeController::Update()
{
	ProcessInput();

	if (NextFramePresent())
	{
		ProcessFrame();
		WaitNextFrame();
	}

	DrawMatrix();
}



//
// ICubeController
//
void CCubeController::BlinkYellowLed()
{
	if (HAL_GPIO_ReadPin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin) == GPIO_PIN_SET)
		return;

	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
}

void CCubeController::BlinkBlueLed()
{
	if (HAL_GPIO_ReadPin(LED_BLUE_GPIO_Port, LED_BLUE_Pin) == GPIO_PIN_SET)
		return;

	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
}


void CCubeController::GoToErrorState()
{
	while(true)
	{
		HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
		HAL_Delay(200);
		HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);
	}
}

IMatrixAccess* CCubeController::GetMatrix()
{
	return this;
}


//
// IMatrixAccess
//
void CCubeController::Clear()
{
	memset(&m_Matrix[0][0], 0x00, sizeof(m_Matrix));
}

void CCubeController::Fill()
{
	memset(&m_Matrix[0][0], 0xFF, sizeof(m_Matrix));
}

void CCubeController::SetPixel(uint8_t x, uint8_t y, uint8_t z)
{
	m_Matrix[y][z] |=  (0x01 << x);
}

void CCubeController::ClearPixel(uint8_t x, uint8_t y, uint8_t z)
{
	m_Matrix[y][z] &= ~(0x01 << x);
}

void CCubeController::TogglePixel(uint8_t x, uint8_t y, uint8_t z)
{
	m_Matrix[y][z] ^=  (0x01 << x);
}

bool CCubeController::GetPixel(uint8_t x, uint8_t y, uint8_t z) const
{
	return (m_Matrix[y][z] & (0x01 << x)) == (0x01 << x);
}


//
// Protected
//
void CCubeController::BtnYellowClick()
{
	//HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);

	m_EffectsEngine->RepeatCurrentEffect();
}

void CCubeController::BtnBlueClick()
{
	//HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);

	m_EffectsEngine->NextEffect();
}


//
// Private
//
void CCubeController::WaitNextFrame()
{
	m_DelayEnd = HAL_GetTick() + ONE_FRAME_TIME;
}

bool CCubeController::NextFramePresent() const
{
	return m_DelayEnd < HAL_GetTick();
}

void CCubeController::ProcessInput()
{
	bool btnYellowPressed = (HAL_GPIO_ReadPin(BTN_YELLOW_GPIO_Port, BTN_YELLOW_Pin) == GPIO_PIN_RESET);
	bool btnBluePressed   = (HAL_GPIO_ReadPin(BTN_BLUE_GPIO_Port,   BTN_BLUE_Pin  ) == GPIO_PIN_RESET);

	if (m_BtnYellowPressed != btnYellowPressed)
	{
		if (btnYellowPressed)
		{
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
		}

		if (!btnYellowPressed)
		{
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);

			BtnYellowClick();
			HAL_Delay(100);
		}
	}

	if (m_BtnBluePressed != btnBluePressed)
	{
		if (btnBluePressed)
		{
			HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_SET);
		}

		if (!btnBluePressed)
		{
			HAL_GPIO_WritePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin, GPIO_PIN_RESET);

			BtnBlueClick();
			HAL_Delay(100);
		}
	}

	m_BtnYellowPressed = btnYellowPressed;
	m_BtnBluePressed = btnBluePressed;
}

void CCubeController::ProcessFrame()
{
	// On 1 frame
	m_EffectsEngine->InvokeFuncFrame(EFrameFuncPeriod::EFrameFuncPeriod_1);

	// On 3 frames
	if (m_Frame >= m_Next3FramesEventCntr)
	{
		m_EffectsEngine->InvokeFuncFrame(EFrameFuncPeriod::EFrameFuncPeriod_3);
		m_Next3FramesEventCntr += 3;
	}

	// On 5 frames
	if (m_Frame >= m_Next5FramesEventCntr)
	{
		m_EffectsEngine->InvokeFuncFrame(EFrameFuncPeriod::EFrameFuncPeriod_5);
		m_Next5FramesEventCntr += 5;
	}

	// On 10 frames
	if (m_Frame >= m_Next10FramesEventCntr)
	{
		m_EffectsEngine->InvokeFuncFrame(EFrameFuncPeriod::EFrameFuncPeriod_10);
		m_Next10FramesEventCntr += 10;
	}

	// On 60 frames
	if (m_Frame >= m_Next60FramesEventCntr)
	{
		m_EffectsEngine->InvokeFuncFrame(EFrameFuncPeriod::EFrameFuncPeriod_60);
		m_Next60FramesEventCntr += 60;
	}

	m_Frame++;
}

void CCubeController::DrawMatrix()
{
	for (uint32_t i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(CUBE_CS_GPIO_Port, CUBE_CS_Pin, GPIO_PIN_RESET);

		uint8_t data = (0x01 << i);
		HAL_SPI_Transmit(&hspi1, &data, 1, 1);

		for (uint32_t j = 0; j < 8; j++)
			HAL_SPI_Transmit(&hspi1, &m_Matrix[i][j], 1, 1);

		HAL_GPIO_WritePin(CUBE_CS_GPIO_Port, CUBE_CS_Pin, GPIO_PIN_SET);
	}
}
