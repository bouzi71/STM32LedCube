#ifndef __INTERFACES_H
#define __INTERFACES_H

#include <stm32f1xx_hal.h>

#include <memory>

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

/*
 * Period in frames (1 sec = 60 frames)
 */
enum EFrameFuncPeriod
{
	EFrameFuncPeriod_1 = 1,
	EFrameFuncPeriod_3 = 3,
	EFrameFuncPeriod_5 = 5,
	EFrameFuncPeriod_10 = 10,
	EFrameFuncPeriod_60 = 60
};

class IEffect
{
public:
	/*
	 * Invoke when effect starts playing
	 */
	virtual void 									FuncInit() = 0;

	/*
	 * Invoke every frame, that corresponde to "FrameType" (every 3 frames, every 60 frames, etc...)
	 * Param 'Frame': number from 0 to FrameType value
	 */
	virtual void 									FuncFrame(uint32_t Frame) = 0;

	virtual void 									InvokeFuncFrame(EFrameFuncPeriod FramePeriod, uint32_t Frame) = 0;

	virtual EFrameFuncPeriod 						GetFramePeriod() const  = 0;
	virtual uint32_t 								GetLenght() const = 0;
	virtual bool 									IsNeedClearBeforeInit() const = 0;
	virtual bool 									IsNeedClearBeforeFrame() const = 0;
};


class IEffectsCollection
{
public:
	virtual void AddEffect(std::shared_ptr<IEffect> Effect) = 0;
	virtual size_t GetCurrentEffectNumber() const = 0;
	virtual const std::shared_ptr<IEffect>& GetCurrentEffect() const = 0;
	virtual void PlayEffect(size_t EffectNumber) = 0;
	virtual void PlayNextEffect() = 0;
};

#endif
