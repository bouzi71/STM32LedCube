#ifndef __MATRIXACCESS_H
#define __MATRIXACCESS_H

#include <stm32f1xx_hal.h>

class IMatrixAccess
{
public:
	virtual void Clear() = 0;
	virtual void Fill() = 0;
	virtual void SetPixel(uint8_t x, uint8_t y, uint8_t z) = 0;
	virtual void ClearPixel(uint8_t x, uint8_t y, uint8_t z) = 0;
	virtual void TogglePixel(uint8_t x, uint8_t y, uint8_t z) = 0;
	virtual bool GetPixel(uint8_t x, uint8_t y, uint8_t z) const = 0;
};

#endif
