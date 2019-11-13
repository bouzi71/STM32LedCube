
// General
#include <LedMatrix.h>

CLedMatrix::CLedMatrix()
{
	m_Matrix = new uint8_t*[8];
	for (size_t i = 0; i < 8; i++)
		m_Matrix[i] = new uint8_t[8];

	Clear();
}


//
// IMatrixAccess
//
void CLedMatrix::Clear()
{
	for (size_t i = 0; i < 8; i++)
		memset(m_Matrix[i], 0x00, 8);
}

void CLedMatrix::Fill()
{
	for (size_t i = 0; i < 8; i++)
		memset(m_Matrix[i], 0xFF, 8);
}

void CLedMatrix::SetPixel(uint8_t x, uint8_t y, uint8_t z)
{
	if (x > 7 || y > 7 || z > 7)
		return;

	m_Matrix[y][z] |=  (0x01 << x);
}

void CLedMatrix::ClearPixel(uint8_t x, uint8_t y, uint8_t z)
{
	if (x > 7 || y > 7 || z > 7)
		return;

	m_Matrix[y][z] &= ~(0x01 << x);
}

void CLedMatrix::TogglePixel(uint8_t x, uint8_t y, uint8_t z)
{
	if (x > 7 || y > 7 || z > 7)
		return;

	m_Matrix[y][z] ^=  (0x01 << x);
}

bool CLedMatrix::GetPixel(uint8_t x, uint8_t y, uint8_t z) const
{
	if (x > 7 || y > 7 || z > 7)
		return false;

	return (m_Matrix[y][z] & (0x01 << x)) == (0x01 << x);
}

void CLedMatrix::Apply(uint8_t** PtrToData)
{
	for (size_t i = 0; i < 8; i++)
		memcpy(m_Matrix[i], PtrToData[i], 8);
}

uint8_t** CLedMatrix::GetPtr() const
{
	return m_Matrix;
}
