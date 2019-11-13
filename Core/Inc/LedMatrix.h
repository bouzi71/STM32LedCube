#ifndef __LEDMATRIX_H
#define __LEDMATRIX_H

#include <Interfaces.h>

class CLedMatrix
	: public IMatrixAccess
{
public:
	CLedMatrix();

	// IMatrixAccess
	void 											Clear() override;
	void 											Fill() override;
	void 											SetPixel(uint8_t x, uint8_t y, uint8_t z) override;
	void 											ClearPixel(uint8_t x, uint8_t y, uint8_t z) override;
	void 											TogglePixel(uint8_t x, uint8_t y, uint8_t z) override;
	bool 											GetPixel(uint8_t x, uint8_t y, uint8_t z) const override;
	void                                            Apply(uint8_t ** PtrToData);
	uint8_t **                                		GetPtr() const;

private:
	uint8_t** 										m_Matrix;
};

#endif
