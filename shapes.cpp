#include "shapes.h"


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
