#pragma once

#include <PolyVoxCore/MaterialDensityPair.h>
#include <PolyVoxCore/LargeVolume.h>

void createSphereInVolume(PolyVox::LargeVolume<PolyVox::MaterialDensityPair44>& volData, float fRadius, uint8_t uValue);
void createCubeInVolume(PolyVox::LargeVolume<PolyVox::MaterialDensityPair44>& volData, PolyVox::Vector3DInt32 lowerCorner, PolyVox::Vector3DInt32 upperCorner, uint8_t uValue);
