
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
CCubeController::CCubeController()
{
	Clear();

	m_Frame = 0;
	m_Next3FramesEventCntr = 0;
	m_Next5FramesEventCntr = 0;
	m_Next10FramesEventCntr = 0;
	m_Next60FramesEventCntr = 0;

	m_DelayEnd = 0;

	m_EffectsEngine = std::make_shared<CEffectsEngine>(this);
}



//
// Public
//
void CCubeController::Update()
{
	if (NextFramePresent())
	{
		ProcessFrame();
		WaitNextFrame();
	}

	DrawMatrix();
}

void CCubeController::BtnYellowClick()
{
	HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);

	m_EffectsEngine->RepeatCurrentEffect();
}

void CCubeController::BtnBlueClick()
{
	HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);

	m_EffectsEngine->NextEffect();
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
// Private
//
void CCubeController::WaitNextFrame()
{
	m_DelayEnd = HAL_GetTick() + ONE_FRAME_TIME;
}

bool CCubeController::NextFramePresent()
{
	return m_DelayEnd < HAL_GetTick();
}

void CCubeController::ProcessFrame()
{
	// On 1 frame
	m_EffectsEngine->CallFrameFunc(1);

	// On 3 frames
	if (m_Frame >= m_Next3FramesEventCntr)
	{
		m_EffectsEngine->CallFrameFunc(3);
		m_Next3FramesEventCntr += 3;
	}

	// On 5 frames
	if (m_Frame >= m_Next5FramesEventCntr)
	{
		m_EffectsEngine->CallFrameFunc(5);
		m_Next5FramesEventCntr += 5;
	}

	// On 10 frames
	if (m_Frame >= m_Next10FramesEventCntr)
	{
		m_EffectsEngine->CallFrameFunc(10);
		m_Next10FramesEventCntr += 10;
	}

	// On 60 frames
	if (m_Frame >= m_Next60FramesEventCntr)
	{
		m_EffectsEngine->CallFrameFunc(60);
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
