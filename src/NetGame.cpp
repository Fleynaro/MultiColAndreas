#include "NetGame.h"

void NetGame::Init(int netGame)
{
	//address offsets has been taken from YSF plugin
	this->vehArrayOffset = *(DWORD_*)(netGame + 12) + 16212;
	this->vehWorldArrayOffset = *(DWORD_*)(netGame + 12) + 212;

	this->playerArrayOffset = *(DWORD_*)(netGame + 8) + 154012;
	this->playerWorldArrayOffset = *(DWORD_*)(netGame + 8) + 0;
	this->playerConnectedArrayOffset = *(DWORD_*)(netGame + 8) + 150012;
	this->init = true;
}

NetGame::Vehicle NetGame::getVehicle(int id)
{
	return NetGame::Vehicle(
		this->vehArrayOffset + id * sizeof(DWORD_),
		(int*)(this->vehWorldArrayOffset + id * sizeof(int))
	);
}

NetGame::Player NetGame::getPlayer(int id)
{
	return NetGame::Player(
		this->playerArrayOffset + id * sizeof(DWORD_),
		(int*)(this->playerWorldArrayOffset + id * sizeof(int))
	);
}

bool NetGame::isPlayerConnected(int id)
{
	return *(int *)(this->playerConnectedArrayOffset + id * sizeof(int));
}


int NetGame::Vehicle::getModelId()
{
	return *(int *)(*(DWORD_*)this->vehOffset + 130);
}

int NetGame::Vehicle::getVirtualWorld()
{
	return 0;
}

int NetGame::Vehicle::getLastDriverId()
{
	return *(WORD_*)(*(DWORD_*)this->vehOffset + 106);
}

bool NetGame::Vehicle::hasDriver()
{
	int playerId = this->getLastDriverId();
	if (playerId == PLAYER_INVALID_ID || !NetGame::getInstance().isPlayerConnected(playerId)) return false;
	NetGame::Player player = NetGame::getInstance().getPlayer(playerId);
	return player.getVehicleId() == this->getVehicleId();
}

bool NetGame::Vehicle::wasOccupiedEver()
{
	return this->getLastDriverId() != PLAYER_INVALID_ID;
}

float NetGame::Vehicle::getSpawnedAngleZ()
{
	return *(float *)(*(DWORD_*)this->vehOffset + 146);
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

//from i_quat.inc
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

//from MTA
btQuaternion NetGame::Vehicle::getRotationQuatFixed2()
{
	MATRIX4X4 matrix = *this->getMatrix4X4();
	float fQuaternion[4];
	GetQuaternionFromMatrix(matrix, fQuaternion);
	return btQuaternion(
		-fQuaternion[1],
		-fQuaternion[2],
		-fQuaternion[3],
		fQuaternion[0]
	);
}

CVector *NetGame::Vehicle::getVelocity()
{
	return (CVector *)(*(DWORD_*)this->vehOffset + 76);
}

CVector * NetGame::Vehicle::getTurnSpeed()
{
	return (CVector *)(*(DWORD_*)this->vehOffset + 88);
}

float CMath_Max(const float a, const float b)
{
	return a > b ? a : b;
}
void GetQuaternionFromMatrix(const MATRIX4X4 &m, float *fQuaternion)
{
	fQuaternion[0] = sqrt(CMath_Max((float)0, 1.0f + m.right.x + m.up.y + m.at.z)) * 0.5f;
	fQuaternion[1] = sqrt(CMath_Max((float)0, 1.0f + m.right.x - m.up.y - m.at.z)) * 0.5f;
	fQuaternion[2] = sqrt(CMath_Max((float)0, 1.0f - m.right.x + m.up.y - m.at.z)) * 0.5f;
	fQuaternion[3] = sqrt(CMath_Max((float)0, 1.0f - m.right.x - m.up.y + m.at.z)) * 0.5f;

	fQuaternion[1] = static_cast <float> (copysign(fQuaternion[1], m.at.y - m.up.z));
	fQuaternion[2] = static_cast <float> (copysign(fQuaternion[2], m.right.z - m.at.x));
	fQuaternion[3] = static_cast <float> (copysign(fQuaternion[3], m.up.x - m.right.y));
}




int NetGame::Player::getSkinId()
{
	return 1;
}

int NetGame::Player::getVirtualWorld()
{
	return *this->playerWorld;
}

int NetGame::Player::getVehicleId()
{
	return *(WORD_ *)(*(DWORD_*)this->playerOffset + 11314);
}

CVector * NetGame::Player::getPos()
{
	return (CVector *)(*(DWORD_*)this->playerOffset + 10517);
}

CVector * NetGame::Player::getVelocity()
{
	return (CVector *)(*(DWORD_*)this->playerOffset + 10557);
}

btQuaternion NetGame::Player::getRotation()
{
	DWORD_ offset = (*(DWORD_*)this->playerOffset + 10537);
	float
		x = *(float*)(offset + 4),
		y = *(float*)(offset + 8),
		z = *(float*)(offset + 12),
		w = *(float*)(offset + 0);
	if (x + y + z + w == 0.0) {
		DWORD_ offset = (*(DWORD_*)this->playerOffset + 126 + 18);
		x = *(float*)(offset + 4),
		y = *(float*)(offset + 8),
		z = *(float*)(offset + 12),
		w = *(float*)(offset + 0);
	}
	return btQuaternion(x, y, z, w);
}
