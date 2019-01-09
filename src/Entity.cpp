#include "Entity.h"
#include "DynamicWorld.h"



void Entity::update()
{
	this->updateState();

	setMapObjectPosition(this->pos);
	setMapObjectRotation(this->rot);
}

void Entity::setMapObjectPosition(btVector3& position)
{
	colMapRigidBody->setWorldTransform(btTransform(colMapRigidBody->getWorldTransform().getRotation(), position));
	collisionWorld->GetDynamicWorld(0)->removeRigidBody(colMapRigidBody);
	collisionWorld->GetDynamicWorld(0)->addRigidBody(colMapRigidBody);
}

void Entity::setMapObjectRotation(btQuaternion& rotation)
{
	colMapRigidBody->setWorldTransform(btTransform(rotation, colMapRigidBody->getWorldTransform().getOrigin()));
	collisionWorld->GetDynamicWorld(0)->removeRigidBody(colMapRigidBody);
	collisionWorld->GetDynamicWorld(0)->addRigidBody(colMapRigidBody);
}



void Entity::Vehicle::createColObject()
{
	collisionWorld->objectManager->g_lock->lock();
	this->colMapRigidBody = (new ColAndreasMapObject(
		this->vehicle.getModelId(),
		this->rot,
		this->pos,
		collisionWorld->GetDynamicWorld(0)
	))->getRigidBody();
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
}




void Entity::Player::updateState()
{

}
