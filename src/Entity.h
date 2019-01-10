#pragma once


#include "ColAndreas.h"
#include "ColObject.h"
#include "NetGame.h"

class Entity
{
public:
	Entity() {};
	~Entity() {
		delete this->colMap;
	}
	void update();
	virtual void updateState() = 0;
	virtual bool isValid() = 0;
	virtual void createColObject() = 0;
	void setId(uint16_t id) {
		this->id = id;
	}
	uint16_t getId() {
		return this->id;
	}
	void setPos(btVector3 *pos) {
		this->pos = *pos;
	}
	btVector3 *getPos() {
		return &this->pos;
	}
	void setRot(btQuaternion *rot) {
		this->rot = *rot;
	}
	btQuaternion *getRot() {
		return &this->rot;
	}
	void setVel(btVector3 *vel) {
		this->speed = *vel;
	}
	btVector3 *getVel() {
		return &this->speed;
	}
	
	ColAndreasMapObject* colMap = NULL;
	void setMapObjectPosition(btVector3& position);
	void setMapObjectRotation(btQuaternion& rotation);

	class Vehicle;
	class Player;
private:
	uint16_t id;
	btVector3 pos;
	btQuaternion rot;
	btVector3 speed;
	int world = 0;
	int oldWorld = 0;
};



class Entity::Vehicle : public ::Entity
{
public:
	Vehicle(int id) {
		this->setId(id);
		this->vehicle = NetGame::getInstance().getVehicle(id);
		this->updateState();
		this->createColObject();
	};
	~Vehicle() {};
	void createColObject() override;
	void updateState() override;
	bool isValid() {
		return vehicle.isValid();
	}

	NetGame::Vehicle vehicle;
};


class Entity::Player : public ::Entity
{
public:
	Player(int id) {
		this->setId(id);
		this->player = NetGame::getInstance().getPlayer(id);
		this->updateState();
		this->createColObject();
	};
	~Player() {};
	void createColObject() override;
	void updateState() override;
	bool isValid() {
		return player.isValid();
	}


	NetGame::Player player;
};