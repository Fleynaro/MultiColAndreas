#include "NetGame.h"

void NetGame::Init(int netGame)
{
	this->vehArrayOffset = *(DWORD_*)(netGame + 12) + 16212;
}

NetGame::Vehicle NetGame::getVehicle(int id)
{
	return Vehicle(this->vehArrayOffset + id * sizeof(DWORD_));
}


int NetGame::Vehicle::getModelId()
{
	return *(int *)(*(DWORD_*)this->vehOffset + 130);
}

CVector *NetGame::Vehicle::getPos()
{
	return (CVector *)(*(DWORD_*)this->vehOffset + 0);
}

MATRIX4X4 *NetGame::Vehicle::getMatrix4X4()
{
	return (MATRIX4X4 *)(*(DWORD_*)this->vehOffset + 12);
}

btMatrix3x3 * NetGame::Vehicle::getMatrix()
{
	return nullptr;
}

btQuaternion NetGame::Vehicle::getRotationQuatFixed()
{
	MATRIX4X4 matrix = *this->getMatrix4X4();

	if (abs(matrix.at.x) < 0.00001 && abs(matrix.at.y) < 0.00001 && abs(matrix.at.z) < 0.00001)
	{
		matrix.at.x = matrix.right.y * matrix.up.z - matrix.right.z * matrix.up.y;
		matrix.at.y = matrix.right.z * matrix.up.x - matrix.right.x * matrix.up.z;
		matrix.at.z = matrix.right.x * matrix.up.y - matrix.right.y * matrix.up.x;
	}

	btScalar
		w = sqrt(1 + matrix.right.x + matrix.up.y + matrix.at.z) / 2,
		x = (matrix.at.y - matrix.up.z) / (4 * w),
		y = (matrix.right.z - matrix.at.x) / (4 * w),
		z = (matrix.up.x - matrix.right.y) / (4 * w);
	return btQuaternion(x, y, z, w);
}

CVector *NetGame::Vehicle::getVelocity()
{
	return (CVector *)(*(DWORD_*)this->vehOffset + 76);
}

CVector * NetGame::Vehicle::getTurnSpeed()
{
	return (CVector *)(*(DWORD_*)this->vehOffset + 88);
}
