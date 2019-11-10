#ifndef __EFFECTSLIBRARY_H
#define __EFFECTSLIBRARY_H

#include <stm32f1xx_hal.h>

#include <Interfaces.h>

void AddEffects(std::shared_ptr<IEffectsCollection> Collection, IMatrixAccess * MatrixAccess);

#endif
