#include "Entity.h"
#include "DynamicWorld.h"


//GENERAL
void Entity::update()
{
	this->updateState();

	collisionWorld->objectManager->g_lock->lock();
	setMapObjectPosition(this->pos);
	setMapObjectRotation(this->rot);
	collisionWorld->objectManager->g_lock->unlock();
}

void Entity::setMapObjectPosition(btVector3& position)
{
	this->colMap->getRigidBody()->setWorldTransform(btTransform(this->colMap->getRigidBody()->getWorldTransform().getRotation(), position));
	collisionWorld->GetDynamicWorld(this->oldWorld)->removeRigidBody(this->colMap->getRigidBody());
	collisionWorld->GetDynamicWorld(this->world)->addRigidBody(this->colMap->getRigidBody());
}

void Entity::setMapObjectRotation(btQuaternion& rotation)
{
	this->colMap->getRigidBody()->setWorldTransform(btTransform(rotation, this->colMap->getRigidBody()->getWorldTransform().getOrigin()));
	collisionWorld->GetDynamicWorld(this->oldWorld)->removeRigidBody(this->colMap->getRigidBody());
	collisionWorld->GetDynamicWorld(this->world)->addRigidBody(this->colMap->getRigidBody());
}




//VEHICLES
void Entity::Vehicle::createColObject()
{
	collisionWorld->objectManager->g_lock->lock();
	this->colMap = new ColAndreasMapObject(
		this->vehicle.getModelId(),
		this->rot,
		this->pos,
		collisionWorld->GetDynamicWorld(this->world)
	);
	ColAndreasObjectTracker *tracker = (ColAndreasObjectTracker *)this->colMap->getRigidBody()->getUserPointer();
	tracker->extraData[0] = this->getId();
	collisionWorld->objectManager->g_lock->unlock();
}

void Entity::Vehicle::updateState()
{
	CVector *pos = this->vehicle.getPos();
	this->setPos(&btVector3(pos->x, pos->y, pos->z));

	CVector *vel = this->vehicle.getVelocity();
	this->setVel(&btVector3(vel->x, vel->y, vel->z));

	btQuaternion rot = this->vehicle.getRotationQuatFixed();
	this->setRot(&rot);

	this->oldWorld = this->world;
	this->world = this->vehicle.getVirtualWorld();
}




//PLAYERS
void Entity::Player::createColObject()
{
	collisionWorld->objectManager->g_lock->lock();
	this->colMap = new ColAndreasMapObject(
		this->player.getSkinId(),
		this->rot,
		this->pos,
		collisionWorld->GetDynamicWorld(this->world)
	);
	ColAndreasObjectTracker *tracker = (ColAndreasObjectTracker *)this->colMap->getRigidBody()->getUserPointer();
	tracker->extraData[0] = this->getId();
	collisionWorld->objectManager->g_lock->unlock();
}

void Entity::Player::updateState()
{
	CVector *pos = this->player.getPos();
	this->setPos(&btVector3(pos->x, pos->y, pos->z));

	CVector *vel = this->player.getVelocity();
	this->setVel(&btVector3(vel->x, vel->y, vel->z));

	btQuaternion rot = this->player.getRotation();
	this->setRot(&rot);

	this->oldWorld = this->world;
	this->world = this->player.getVirtualWorld();
}
