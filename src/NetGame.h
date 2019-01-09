#pragma once

#include <btBulletDynamicsCommon.h>

typedef int				DWORD_;

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

	class Vehicle
	{
	public:
		Vehicle() {};
		Vehicle(DWORD_ vehOffset) : vehOffset(vehOffset) {};
		~Vehicle() {};
		
		bool isValid() {
			return *(DWORD_*)this->vehOffset != 0;
		}
		int getModelId();
		CVector *getPos();
		CVector *getVelocity();
		CVector *getTurnSpeed();
		MATRIX4X4 *getMatrix4X4();
		btMatrix3x3 *getMatrix();
		btQuaternion getRotationQuatFixed();
	private:
		DWORD_ vehOffset;
	};
	NetGame::Vehicle getVehicle(int id);


	class Player
	{
	public:
		Player() {};
		~Player() {};

	};
private:
	int vehArrayOffset;
};

