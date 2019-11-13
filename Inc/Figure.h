#ifndef __FIGURE_H
#define __FIGURE_H

#include <Interfaces.h>
#include <vector>

#include "../Src/Math/vector3.h"

class CFugure3D
{
public:
	CFugure3D();

	void                                   			Clear();
	void                                            AddPoint(uint8_t x, uint8_t y, uint8_t z); // matrix points (from 0 to 7)
	void                                            AddPoint(const Vector3& Point); // converted vector (from -0.5f to 0.5f)
	const std::vector<Vector3>&                     GetPoints() const;
	size_t                                          GetPointCount() const;
	Vector3                                         GetConvertedPoint(const Matrix4& Matrix, size_t Index) const;

	void                                            ModifyData(const Matrix4& Matrix);

private:
	Vector3                                			ToVector3(uint8_t x, uint8_t y, uint8_t z) const;

private:
	std::vector<Vector3>                    		m_Points;

	const float                             		cMultiplyValue = 7.0f;
	const Vector3                           		cOffsetVector = Vector3(0.5f, 0.5f, 0.5f);
};

#endif
