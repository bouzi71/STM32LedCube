#ifndef __EFFECT_H
#define __EFFECT_H

#include <Interfaces.h>

#define SET_PIXEL(x, y, z)     (m_CubeController->GetMatrix()->SetPixel(x, y, z));
#define CLEAR_PIXEL(x, y, z)   (m_CubeController->GetMatrix()->ClearPixel(x, y, z));
#define TOGGLE_PIXEL(x, y, z)  (m_CubeController->GetMatrix()->TogglePixel(x, y, z));
#define GET_PIXEL(x, y, z)     (m_CubeController->GetMatrix()->GetPixel(x, y, z))

class CEffect
	: public IEffect
{
public:
	CEffect();
	CEffect(ICubeController * CubeController);

	// IEffect
	virtual void									FuncInit() override;
	virtual void									FuncFrame(uint32_t Frame) override;
	void                                            InvokeFuncFrame(EFrameFuncPeriod FramePeriod, uint32_t Frame);

	EFrameFuncPeriod                                GetFramePeriod() const override;
	void             								SetFramePeriod(EFrameFuncPeriod Period) override;
	uint32_t                                        GetLenght() const override;
	virtual void                                    SetLenght(uint32_t Value) override;
	uint32_t                                        GetRepeatCount() const override;
	virtual void                                    SetRepeatCount(uint32_t Value) override;
	bool                                            IsNeedClearBeforeInit() const override;
	bool                                            IsNeedClearBeforeFrame() const override;

protected:
	virtual void 									PlaneX(uint32_t plane);
	virtual void 									PlaneY(uint32_t plane);
	virtual void 									PlaneZ(uint32_t plane);
	virtual void 									Cube(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd);
	virtual void 									CubeOutline(uint32_t xBegin, uint32_t xEnd, uint32_t yBegin, uint32_t yEnd, uint32_t zBegin, uint32_t zEnd);

protected:
	void                                    		SetClearBeforeInit(bool Value);
	void                                    		SetClearBeforeFrame(bool Value);

private:
	EFrameFuncPeriod								m_FramePeriod;
	uint32_t										m_Lenght;
	uint32_t                                        m_RepeatCnt;

	bool											m_CleanCubeBeforeInit;
	bool											m_CleanCubeBeforeFrame;

protected:
	ICubeController *								m_CubeController;
};




#endif