#include "shapes.h"

void createShapes(PolyVox::LargeVolume<PolyVox::MaterialDensityPair44>& volData)
{
	int32_t sidelength = 128;
	int32_t minPos = 0;
	int32_t midPos = sidelength / 2;
	int32_t maxPos = sidelength - 1;
	using PolyVox::Vector3DInt32;
	createSphereInVolume(volData, 60, 5);
	createSphereInVolume(volData, 50, 4);
	createSphereInVolume(volData, 40, 3);
	createSphereInVolume(volData, 30, 2);
	createSphereInVolume(volData, 20, 1);

	createCubeInVolume(volData, Vector3DInt32(minPos, minPos, minPos), Vector3DInt32(midPos-1, midPos-1, midPos-1), 0);
	createCubeInVolume(volData, Vector3DInt32(midPos+1, midPos+1, minPos), Vector3DInt32(maxPos, maxPos, midPos-1), 0);
	createCubeInVolume(volData, Vector3DInt32(midPos+1, minPos, midPos+1), Vector3DInt32(maxPos, midPos-1, maxPos), 0);
	createCubeInVolume(volData, Vector3DInt32(minPos, midPos+1, midPos+1), Vector3DInt32(midPos-1, maxPos, maxPos), 0);

	createCubeInVolume(volData, Vector3DInt32(1, midPos-10, midPos-10), Vector3DInt32(maxPos-1, midPos+10, midPos+10), PolyVox::MaterialDensityPair44::getMaxDensity());
	createCubeInVolume(volData, Vector3DInt32(midPos-10, 1, midPos-10), Vector3DInt32(midPos+10, maxPos-1, midPos+10), PolyVox::MaterialDensityPair44::getMaxDensity());
	createCubeInVolume(volData, Vector3DInt32(midPos-10, midPos-10 ,1), Vector3DInt32(midPos+10, midPos+10, maxPos-1), PolyVox::MaterialDensityPair44::getMaxDensity());
}

void createSphereInVolume(PolyVox::LargeVolume<PolyVox::MaterialDensityPair44>& volData, float fRadius, uint8_t uValue)
{
	using namespace PolyVox;
	//This vector hold the position of the center of the volume
	Vector3DInt32 v3dVolCenter = (volData.getEnclosingRegion().getUpperCorner() - volData.getEnclosingRegion().getLowerCorner()) / 2;

	//This three-level for loop iterates over every voxel in the volume
	for (int z = 0; z < volData.getWidth(); z++)
	{
		for (int y = 0; y < volData.getHeight(); y++)
		{
			for (int x = 0; x < volData.getDepth(); x++)
			{
				//Store our current position as a vector...
				Vector3DInt32 v3dCurrentPos(x,y,z);	
				//And compute how far the current position is from the center of the volume
				double fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();

				//If the current voxel is less than 'radius' units from the center
				//then we make it solid, otherwise we make it empty space.
				if(fDistToCenter <= fRadius)
				{
					volData.setVoxelAt(x,y,z, MaterialDensityPair44(uValue, uValue > 0 ? MaterialDensityPair44::getMaxDensity() : MaterialDensityPair44::getMinDensity()));
				}
			}
		}
	}
}

void createCubeInVolume(PolyVox::LargeVolume<PolyVox::MaterialDensityPair44>& volData, PolyVox::Vector3DInt32 lowerCorner, PolyVox::Vector3DInt32 upperCorner, uint8_t uValue)
{
	using namespace PolyVox;
	//This three-level for loop iterates over every voxel between the specified corners
	for (int z = lowerCorner.getZ(); z <= upperCorner.getZ(); z++)
	{
		for (int y = lowerCorner.getY(); y <= upperCorner.getY(); y++)
		{
			for (int x = lowerCorner.getX() ; x <= upperCorner.getX(); x++)
			{
				volData.setVoxelAt(x,y,z, MaterialDensityPair44(uValue, uValue > 0 ? MaterialDensityPair44::getMaxDensity() : MaterialDensityPair44::getMinDensity()));
			}
		}
	}
}
