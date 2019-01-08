#include "DynamicWorld.h"

// Initialize ColAndreas
ColAndreasWorld::ColAndreasWorld()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	removedManager = new RemovedBuildingManager();
	objectManager = new ObjectManager();
}

btDynamicsWorld* ColAndreasWorld::GetDynamicWorld(int world)
{
	map<int, btDynamicsWorld*>::iterator p;
	p = worlds.find(world);
	if (p != worlds.end())
		return p->second;
	else
	{
		btDynamicsWorld* worldPointer;
		worldPointer = new btDiscreteDynamicsWorld(dispatcher, new btDbvtBroadphase(), solver, collisionConfiguration);
		worlds.insert(pair<int, btDynamicsWorld*>(world, worldPointer));
		return worldPointer;
	}
}


// ColAndreas closed
ColAndreasWorld::~ColAndreasWorld()
{
	if (objectManager != NULL)
		delete removedManager;

	if (removedManager != NULL)
		delete removedManager;

	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	for (std::map<int, btDynamicsWorld*>::iterator itr = worlds.begin(); itr != worlds.end(); itr++){
		delete (itr->second);
	}
	worlds.clear();

	if (mapWaterMesh != NULL)
		delete mapWaterMesh;
}

btScalar ColAndreasWorld::getDist3D(const btVector3& c1, const btVector3& c2)
{
	btScalar dx = c2.getX() - c1.getX();
	btScalar dy = c2.getY() - c1.getY();
	btScalar dz = c2.getZ() - c1.getZ();
	return sqrt((btScalar)(dx * dx + dy * dy + dz * dz));
}

	// Converts GTA rotations to quaternion
void ColAndreasWorld::EulerToQuat(btVector3& rotation, btQuaternion& result)
{
	rotation.setX(rotation.getX() * DEG_TO_RAD);
	rotation.setY(rotation.getY() * DEG_TO_RAD);
	rotation.setZ(rotation.getZ() * DEG_TO_RAD);

	btScalar c1 = cos(rotation.getY() / 2);
	btScalar s1 = sin(rotation.getY() / 2);
	btScalar c2 = cos(rotation.getX() / 2);
	btScalar s2 = sin(rotation.getX() / 2);
	btScalar c3 = cos(rotation.getZ() / 2);
	btScalar s3 = sin(rotation.getZ() / 2);
	btScalar c1c2 = c1*c2;
	btScalar s1s2 = s1*s2;
	result.setW((c1c2*c3 - s1s2*s3));
	result.setZ(c1c2*s3 + s1s2*c3);
	result.setY(s1*c2*c3 + c1*s2*s3);
	result.setX(c1*s2*c3 - s1*c2*s3);
}

void ColAndreasWorld::QuatToEuler(btQuaternion& rotation, btVector3& result)
{
	result.setY((-asin(2 * ((rotation.getX() * rotation.getZ()) + (rotation.getW() * rotation.getY()))) * RADIAN_TO_DEG) );
	result.setX((atan2(2 * ((rotation.getY() * rotation.getZ()) + (rotation.getW() * rotation.getX())), (rotation.getW() * rotation.getW()) - (rotation.getX() * rotation.getX()) - (rotation.getY() * rotation.getY()) + (rotation.getZ() * rotation.getZ())) * RADIAN_TO_DEG) );
	result.setZ((-atan2(2 * ((rotation.getX() * rotation.getY()) + (rotation.getW() * rotation.getZ())), (rotation.getW() * rotation.getW()) + (rotation.getX() * rotation.getX()) - (rotation.getY() * rotation.getY()) - (rotation.getZ() * rotation.getZ())) * RADIAN_TO_DEG) );
}

int ColAndreasWorld::performRayTest(const btVector3& Start, const btVector3& End, btVector3& Result, uint16_t& model, int world)
{
	btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
	btCollisionWorld::ClosestRayResultCallback RayCallback2(Start, End);

	GetDynamicWorld(ALL_WORLDS)->rayTest(Start, End, RayCallback);
	GetDynamicWorld(world)->rayTest(Start, End, RayCallback2);

	btVector3 ResultAllWorlds = End;
	model = 0;
	if (RayCallback.hasHit())
	{
		Result = ResultAllWorlds = RayCallback.m_hitPointWorld;
		model = RayCallback.m_collisionObject->getUserIndex();
	}
	if (RayCallback2.hasHit())
	{
		Result = RayCallback2.m_hitPointWorld;
		if (Start.distance2(Result) > Start.distance2(ResultAllWorlds)) {
			Result = ResultAllWorlds;
		}
		else {
			model = RayCallback2.m_collisionObject->getUserIndex();
		}
	}
	return (model != 0);
}

int ColAndreasWorld::performRayTestExtraID(const btVector3& Start, const btVector3& End, btVector3& Result, const int type, uint16_t& data, int world)
{
	btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
	btCollisionWorld::ClosestRayResultCallback RayCallback2(Start, End);

	GetDynamicWorld(ALL_WORLDS)->rayTest(Start, End, RayCallback);
	GetDynamicWorld(world)->rayTest(Start, End, RayCallback2);

	btVector3 ResultAllWorlds = End;
	
	if (type >= 0 && type < 10) {
		data = 0;
	} else data = -1;
	bool hit = false;

	if (RayCallback.hasHit())
	{
		Result = ResultAllWorlds = RayCallback.m_hitPointWorld;
		if (data == 0)
		{
			ColAndreasObjectTracker* tracker = (ColAndreasObjectTracker*)RayCallback.m_collisionObject->getUserPointer();
			data = tracker->extraData[type];
		}
		hit = true;
	}
	if (RayCallback2.hasHit())
	{
		Result = RayCallback2.m_hitPointWorld;
		if (Start.distance2(Result) > Start.distance2(ResultAllWorlds)) {
			Result = ResultAllWorlds;
		}
		else {
			if (data == 0)
			{
				ColAndreasObjectTracker* tracker = (ColAndreasObjectTracker*)RayCallback2.m_collisionObject->getUserPointer();
				data = tracker->extraData[type];
			}
		}
		hit = true;
	}
	return hit;
}

int ColAndreasWorld::performRayTestID(const btVector3& Start, const btVector3& End, btVector3& Result, uint16_t& index, int world)
{
	btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
	btCollisionWorld::ClosestRayResultCallback RayCallback2(Start, End);

	GetDynamicWorld(ALL_WORLDS)->rayTest(Start, End, RayCallback);
	GetDynamicWorld(world)->rayTest(Start, End, RayCallback2);

	btVector3 ResultAllWorlds = End;
	
	bool hit = false;
	if (RayCallback.hasHit())
	{
		Result = ResultAllWorlds = RayCallback.m_hitPointWorld;
		ColAndreasObjectTracker* tracker = (ColAndreasObjectTracker*)RayCallback.m_collisionObject->getUserPointer();
		if (tracker)
		{
			index = tracker->realIndex;
		}
		else
		{
			index = -1;
		}
		hit = true;
	}
	if (RayCallback2.hasHit())
	{
		Result = RayCallback2.m_hitPointWorld;
		if (Start.distance2(Result) > Start.distance2(ResultAllWorlds)) {
			Result = ResultAllWorlds;
		}
		else {
			ColAndreasObjectTracker* tracker = (ColAndreasObjectTracker*)RayCallback2.m_collisionObject->getUserPointer();
			if (tracker)
			{
				index = tracker->realIndex;
			}
			else
			{
				index = -1;
			}
		}
		hit = true;
	}
	return hit;
}

int ColAndreasWorld::performRayTestEx(const btVector3& Start, const btVector3& End, btVector3& Result, btQuaternion& Rotation, btVector3& Position, uint16_t& model, int world)
{
	btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
	btCollisionWorld::ClosestRayResultCallback RayCallback2(Start, End);

	GetDynamicWorld(ALL_WORLDS)->rayTest(Start, End, RayCallback);
	GetDynamicWorld(world)->rayTest(Start, End, RayCallback2);

	btVector3 ResultAllWorlds = End;
	model = 0;
	if (RayCallback.hasHit())
	{
		Result = ResultAllWorlds = RayCallback.m_hitPointWorld;
		model = RayCallback.m_collisionObject->getUserIndex();
		Rotation = RayCallback.m_collisionObject->getWorldTransform().getRotation();
		Position = RayCallback.m_collisionObject->getWorldTransform().getOrigin();
	}
	if (RayCallback2.hasHit())
	{
		Result = RayCallback2.m_hitPointWorld;
		if (Start.distance2(Result) > Start.distance2(ResultAllWorlds)) {
			Result = ResultAllWorlds;
		}
		else {
			model = RayCallback2.m_collisionObject->getUserIndex();
			Rotation = RayCallback2.m_collisionObject->getWorldTransform().getRotation();
			Position = RayCallback2.m_collisionObject->getWorldTransform().getOrigin();
		}
	}
	return (model != 0);
}


int ColAndreasWorld::performRayTestAngle(const btVector3& Start, const btVector3& End, btVector3& Result, btScalar& RX, btScalar& RY, btScalar& RZ, uint16_t& model, int world)
{
	btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
	btCollisionWorld::ClosestRayResultCallback RayCallback2(Start, End);

	GetDynamicWorld(ALL_WORLDS)->rayTest(Start, End, RayCallback);
	GetDynamicWorld(world)->rayTest(Start, End, RayCallback2);

	btVector3 ResultAllWorlds = End;
	model = 0;
	if (RayCallback.hasHit())
	{
		btVector3 Rotation = RayCallback.m_hitNormalWorld;
		RX = -(asin(Rotation.getY())*RADIAN_TO_DEG);
		RY = asin(Rotation.getX())*RADIAN_TO_DEG;
		// I think there is a way to calculate this not sure how yet
		RZ = 0.0;
		Result = RayCallback.m_hitPointWorld;
		model = RayCallback.m_collisionObject->getUserIndex();
	}
	if (RayCallback2.hasHit())
	{
		Result = RayCallback2.m_hitPointWorld;
		if (Start.distance2(Result) > Start.distance2(ResultAllWorlds)) {
			Result = ResultAllWorlds;
		}
		else {
			btVector3 Rotation = RayCallback2.m_hitNormalWorld;
			RX = -(asin(Rotation.getY())*RADIAN_TO_DEG);
			RY = asin(Rotation.getX())*RADIAN_TO_DEG;
			// I think there is a way to calculate this not sure how yet
			RZ = 0.0;
			model = RayCallback2.m_collisionObject->getUserIndex();
		}
	}
	return (model != 0);
}

int ColAndreasWorld::performRayTestAngleEx(const btVector3& Start, const btVector3& End, btVector3& Result, btScalar& RX, btScalar& RY, btScalar& RZ, btQuaternion& Rotation, btVector3& Position, uint16_t& model, int world)
{
	btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
	btCollisionWorld::ClosestRayResultCallback RayCallback2(Start, End);

	GetDynamicWorld(ALL_WORLDS)->rayTest(Start, End, RayCallback);
	GetDynamicWorld(world)->rayTest(Start, End, RayCallback2);

	btVector3 ResultAllWorlds = End;
	model = 0;
	if (RayCallback.hasHit())
	{
		btVector3 Normal = RayCallback.m_hitNormalWorld;


		RX = -(asin(Normal.getY())*RADIAN_TO_DEG);
		RY = asin(Normal.getX())*RADIAN_TO_DEG;
		// There is a way to calculate this not sure how yet
		RZ = 0.0;
		Result = RayCallback.m_hitPointWorld;


		model = RayCallback.m_collisionObject->getUserIndex();
		Rotation = RayCallback.m_collisionObject->getWorldTransform().getRotation();
		Position = RayCallback.m_collisionObject->getWorldTransform().getOrigin();
	}
	if (RayCallback2.hasHit())
	{
		Result = RayCallback2.m_hitPointWorld;
		if (Start.distance2(Result) > Start.distance2(ResultAllWorlds)) {
			Result = ResultAllWorlds;
		}
		else {
			btVector3 Normal = RayCallback2.m_hitNormalWorld;


			RX = -(asin(Normal.getY())*RADIAN_TO_DEG);
			RY = asin(Normal.getX())*RADIAN_TO_DEG;
			// There is a way to calculate this not sure how yet
			RZ = 0.0;

			model = RayCallback2.m_collisionObject->getUserIndex();
			Rotation = RayCallback2.m_collisionObject->getWorldTransform().getRotation();
			Position = RayCallback2.m_collisionObject->getWorldTransform().getOrigin();
		}
	}
	return (model != 0);
}


int ColAndreasWorld::performRayTestAll(const btVector3& Start, const btVector3& End, btAlignedObjectArray < btVector3 >& Result, int ModelIDs[], int size, int world)
{
	btCollisionWorld::AllHitsRayResultCallback RayCallback(Start, End);
	btCollisionWorld::AllHitsRayResultCallback RayCallback2(Start, End);

	GetDynamicWorld(ALL_WORLDS)->rayTest(Start, End, RayCallback);
	GetDynamicWorld(world)->rayTest(Start, End, RayCallback2);

	int size_ = size;
	if (RayCallback.hasHit())
	{
		if (RayCallback.m_hitPointWorld.size() <= size_)
		{
			for (int i = 0; i < RayCallback.m_hitPointWorld.size(); i++) {
				ModelIDs[i] = RayCallback.m_collisionObjects[i]->getUserIndex();
			}
			Result = RayCallback.m_hitPointWorld;
			size_ -= RayCallback.m_hitPointWorld.size();
		}
	}

	if (RayCallback2.hasHit())
	{
		if (RayCallback2.m_hitPointWorld.size() <= size_)
		{
			for (int i = 0; i < RayCallback2.m_hitPointWorld.size(); i++) {
				int j = i + (size - size_); //merging the previous and current arrays
				ModelIDs[j] = RayCallback2.m_collisionObjects[i]->getUserIndex();
				Result[j] = RayCallback2.m_hitPointWorld[i];
			}
			size_ = 0;
		}
	}
	return (size_ < size);
}

// Return reflection vector 
int ColAndreasWorld::performRayTestReflection(const btVector3& Start, const btVector3& End, btVector3& Position, btVector3& Result, uint16_t& model, int world)
{
	btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
	btCollisionWorld::ClosestRayResultCallback RayCallback2(Start, End);

	GetDynamicWorld(ALL_WORLDS)->rayTest(Start, End, RayCallback);
	GetDynamicWorld(world)->rayTest(Start, End, RayCallback2);

	btVector3 ResultAllWorlds = End;
	model = 0;
	if (RayCallback.hasHit())
	{
		Position = RayCallback.m_hitPointWorld;
		model = RayCallback.m_collisionObject->getUserIndex();

		// Calculates the reflection vector of the given Raycast
		btVector3 Normal = RayCallback.m_hitNormalWorld;
		btScalar Magnitude = this->getDist3D(Start, Position);
		btVector3 UVector = (Position - Start) / btVector3(Magnitude, Magnitude, Magnitude);
		Result = UVector - 2 * UVector.dot(Normal) * Normal;
	}
	if (RayCallback2.hasHit())
	{
		Result = RayCallback2.m_hitPointWorld;
		if (Start.distance2(Result) > Start.distance2(ResultAllWorlds)) {
			Result = ResultAllWorlds;
		}
		else {
			Position = RayCallback2.m_hitPointWorld;
			model = RayCallback2.m_collisionObject->getUserIndex();

			// Calculates the reflection vector of the given Raycast
			btVector3 Normal = RayCallback2.m_hitNormalWorld;
			btScalar Magnitude = this->getDist3D(Start, Position);
			btVector3 UVector = (Position - Start) / btVector3(Magnitude, Magnitude, Magnitude);
		}
	}
	return (model != 0);
}


int ColAndreasWorld::performRayTestNormal(const btVector3& Start, const btVector3& End, btVector3& Result, btVector3& Normal, uint16_t& model, int world)
{
	btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
	btCollisionWorld::ClosestRayResultCallback RayCallback2(Start, End);

	GetDynamicWorld(ALL_WORLDS)->rayTest(Start, End, RayCallback);
	GetDynamicWorld(world)->rayTest(Start, End, RayCallback2);

	btVector3 ResultAllWorlds = End;
	model = 0;
	if (RayCallback.hasHit())
	{
		Normal = RayCallback.m_hitNormalWorld;
		Result = RayCallback.m_hitPointWorld;
		model = RayCallback.m_collisionObject->getUserIndex();
	}
	if (RayCallback2.hasHit())
	{
		Result = RayCallback2.m_hitPointWorld;
		if (Start.distance2(Result) > Start.distance2(ResultAllWorlds)) {
			Result = ResultAllWorlds;
		}
		else {
			Normal = RayCallback2.m_hitNormalWorld;
			model = RayCallback2.m_collisionObject->getUserIndex();
		}
	}
	return (model != 0);
}

int ColAndreasWorld::performContactTest(uint16_t modelid, btVector3& objectPos, btQuaternion& objectRot, int world)
{
	ContactCollisionSensor callback;
	ContactCollisionSensor callback2;
	
	uint16_t colindex = ModelRef[modelid];
	btDefaultMotionState* colMapObjectPosition = new btDefaultMotionState(btTransform(objectRot, objectPos));
	btRigidBody::btRigidBodyConstructionInfo meshRigidBodyCI(0, colMapObjectPosition, colConvex[colindex], btVector3(0, 0, 0));
	btRigidBody* colMapRigidBody = new btRigidBody(meshRigidBodyCI);
	
	GetDynamicWorld(ALL_WORLDS)->contactTest(colMapRigidBody, callback);
	GetDynamicWorld(world)->contactTest(colMapRigidBody, callback2);
	
	delete colMapRigidBody->getMotionState();
	delete colMapRigidBody;
	
	return callback.collided || callback2.collided;
}

void ColAndreasWorld::colandreasInitMap()
{
	// Create water map mesh
	mapWaterMesh = new MapWaterMesh(GetDynamicWorld(ALL_WORLDS));

	// Create all map object
	InitCollisionMap(GetDynamicWorld(ALL_WORLDS), this->removedManager);
}

uint16_t ColAndreasWorld::createColAndreasMapObject(uint16_t addtomanager, uint16_t modelid, const btQuaternion& objectRot, const btVector3& objectPos, int world)
{
	objectManager->g_lock->lock();
	ColAndreasMapObject* mapObject = new ColAndreasMapObject(modelid, objectRot, objectPos, GetDynamicWorld(world));
	objectManager->g_lock->unlock();
	if (addtomanager)
	{
		uint16_t index = 0;
		return this->objectManager->addObjectManager(mapObject);
	}
	return -1;
}

uint16_t ColAndreasWorld::getModelRef(uint16_t model)
{
	return GetModelRef(model);
}
 		 
void ColAndreasWorld::setMyExtraID(uint16_t index, int type, int data)
{
	objectManager->setExtraID(index, type, data);
}

int ColAndreasWorld::getMyExtraID(uint16_t index, int type)
{
	return objectManager->getExtraID(index, type);
}

bool ColAndreasWorld::loadCollisionData()
{
	if (LoadCollisionData())
	{
		return true;
	}
	return false;
}