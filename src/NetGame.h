#pragma once

#include <btBulletDynamicsCommon.h>

typedef int				DWORD_;
typedef unsigned short int				WORD_;

typedef struct {
	float x, y, z;
} CVector;
static_assert(sizeof(CVector) == 12, "Invalid CVector size");

typedef struct _MATRIX4X4
{
	CVector right;
	DWORD_  flags;
	CVector up;
	float  pad_u;
	CVector at;
	float  pad_a;
	CVector pos;
	float  pad_p;
} MATRIX4X4, *PMATRIX4X4;
static_assert(sizeof(_MATRIX4X4) == 64, "Invalid _MATRIX4X4 size");

void GetQuaternionFromMatrix(const MATRIX4X4 &m, float *fQuaternion);

#define PLAYER_INVALID_ID 65535






class NetGame
{
public:
	NetGame() {};
	~NetGame() {};
	void Init(int netGame);

	static NetGame& getInstance() {
		static NetGame  instance;
		return instance;
	}

	bool isInit() {
		return this->init;
	}

	class Vehicle
	{
	public:
		Vehicle() {};
		Vehicle(DWORD_ vehOffset, int *vehWorld) : vehOffset(vehOffset), vehWorld(vehWorld){};
		~Vehicle() {};
		
		int getVehicleId() {
			return ((int)vehOffset - NetGame::getInstance().vehArrayOffset) / sizeof(DWORD_);
		}
		bool isValid() {
			return *(DWORD_*)this->vehOffset != 0;
		}
		int getModelId();
		int getVirtualWorld();
		int getLastDriverId();
		bool hasDriver();
		bool wasOccupiedEver();
		float getSpawnedAngleZ();
		CVector *getPos();
		CVector *getVelocity();
		CVector *getTurnSpeed();
		MATRIX4X4 *getMatrix4X4();
		btMatrix3x3 *getMatrix();
		btQuaternion getRotationQuatFixed();
		btQuaternion getRotationQuatFixed2();
	private:
		DWORD_ vehOffset;
		int * vehWorld;
	};
	NetGame::Vehicle getVehicle(int id);



	class Player
	{
	public:
		Player() {};
		Player(DWORD_ playerOffset, int *playerWorld) : playerOffset(playerOffset), playerWorld(playerWorld){};
		~Player() {};

		bool isValid() {
			return *(DWORD_*)this->playerOffset != 0;
		}
		int getSkinId();
		int getVirtualWorld();
		int getVehicleId();
		CVector *getPos();
		CVector *getVelocity();
		btQuaternion getRotation();
	private:
		DWORD_ playerOffset;
		int * playerWorld;
	};
	NetGame::Player getPlayer(int id);
	bool isPlayerConnected(int id);

	int vehArrayOffset;
	int vehWorldArrayOffset;
	int playerArrayOffset;
	int playerWorldArrayOffset;
	int playerConnectedArrayOffset;
private:
	bool init = false;
};

