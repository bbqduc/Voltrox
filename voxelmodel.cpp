#include "voxelmodel.h"

template <typename T>
void VoxelModel<T>::destroyBuffers()
{
	glDeleteBuffers(1, vertexBuffer);
	glDeleteBuffers(1, indexBuffer);
}

template <typename T>
{
}