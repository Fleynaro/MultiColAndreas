#include "Entity.h"
#include "DynamicWorld.h"


//GENERAL
void Entity::update()
{
	this->updateState();

	std::unique_lock<std::shared_mutex> lock(*collisionWorld->objectManager->g_lock);
	setMapObjectPosition(this->pos);
	setMapObjectRotation(this->rot);
}

void Entity::setMapObjectPosition(btVector3& position)
{
	this->colMap->getRigidBody()->setWorldTransform(btTransform(this->colMap->getRigidBody()->getWorldTransform().getRotation(), position));
	collisionWorld->getDynamicWorld(this->oldWorld)->removeRigidBody(this->colMap->getRigidBody());
	collisionWorld->getDynamicWorld(this->world)->addRigidBody(this->colMap->getRigidBody());
}

void Entity::setMapObjectRotation(btQuaternion& rotation)
{
	this->colMap->getRigidBody()->setWorldTransform(btTransform(rotation, this->colMap->getRigidBody()->getWorldTransform().getOrigin()));
	collisionWorld->getDynamicWorld(this->oldWorld)->removeRigidBody(this->colMap->getRigidBody());
	collisionWorld->getDynamicWorld(this->world)->addRigidBody(this->colMap->getRigidBody());
}




//VEHICLES
Entity::Vehicle::Vehicle(int id) {
	this->setId(id);
	this->vehicle = NetGame::getInstance().getVehicle(id);
	this->updateState();
	if (!vehicle.wasOccupiedEver()) {
		collisionWorld->EulerToQuat(btVector3(0, 0, vehicle.getSpawnedAngleZ()), this->rot);
	}
	this->createColObject();
}

void Entity::Vehicle::createColObject()
{
	std::unique_lock<std::shared_mutex> lock(*collisionWorld->objectManager->g_lock);
	this->colMap = new ColAndreasMapObject(
		this->vehicle.getModelId(),
		this->rot,
		this->pos,
		collisionWorld->getDynamicWorld(this->world)
	);
	ColAndreasObjectTracker *tracker = (ColAndreasObjectTracker *)this->colMap->getRigidBody()->getUserPointer();
	tracker->extraData[0] = this->getId();
}

void Entity::Vehicle::updateState()
{
	CVector *pos = this->vehicle.getPos();
	this->setPos(&btVector3(pos->x, pos->y, pos->z));

	CVector *vel = this->vehicle.getVelocity();
	this->setVel(&btVector3(vel->x, vel->y, vel->z));

	if (this->vehicle.hasDriver()) {
		btQuaternion rot = this->vehicle.getRotationQuatFixed2();
		this->setRot(&rot);
	}
	this->oldWorld = this->world;
	this->world = this->vehicle.getVirtualWorld();
}





//PLAYERS
Entity::Player::Player(int id) {
	this->setId(id);
	this->player = NetGame::getInstance().getPlayer(id);
	this->updateState();
	this->createColObject();
}

void Entity::Player::createColObject()
{
	std::unique_lock<std::shared_mutex> lock(*collisionWorld->objectManager->g_lock);
	this->colMap = new ColAndreasMapObject(
		this->player.getSkinId(),
		this->rot,
		this->pos,
		collisionWorld->getDynamicWorld(this->world)
	);
	ColAndreasObjectTracker *tracker = (ColAndreasObjectTracker *)this->colMap->getRigidBody()->getUserPointer();
	tracker->extraData[0] = this->getId();
}

void Entity::Player::updateState()
{
	CVector *pos = this->player.getPos();
	this->setPos(&btVector3(pos->x, pos->y, pos->z));

	CVector *vel = this->player.getVelocity();
	this->setVel(&btVector3(vel->x, vel->y, vel->z));

	btQuaternion rot = this->player.getRotation();
	this->setRot(&rot);
	/*btVector3 getAngle;
	collisionWorld->QuatToEuler(rot, getAngle);*/

	this->oldWorld = this->world;
	this->world = this->player.getVirtualWorld();
}
