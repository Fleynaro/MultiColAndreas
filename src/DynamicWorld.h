#ifndef _INCL_DYNWORLD
#define _INCL_DYNWORLD

#include <btBulletDynamicsCommon.h>
#include "ColObject.h"
#include "ColAndreas.h"
#include <map>
#include <mutex>
#include <algorithm>

#define ALL_WORLDS -1

const btScalar DEG_TO_RAD = btScalar(0.0174532925);
const btScalar RADIAN_TO_DEG = btScalar(57.29577951);



template <class DstType, class SrcType> bool IsType(const SrcType* src) {
	return dynamic_cast<const DstType*>(src) != nullptr;
}

#include "Entity.h"
#define MAX_PLAYERS 1000
#define MAX_VEHICLES 2000
class EntityManager
{
public:
	void addEntity(Entity *entity);
	void removeEntity(uint16_t index);
	template <typename T_Entity> void removeEntity(uint16_t id) {
		for (int i = 0; i != this->nextEntityInsert; i++)
		{
			Entity *entity = this->entities[i];

			if (IsType<T_Entity>(entity)) {
				if (entity->getId() == id) {
					this->removeEntity(i);
					return;
				}
			}
		}
	}
	void executeUpdate();
private:
	Entity *entities[MAX_PLAYERS + MAX_VEHICLES];
	uint16_t nextEntityInsert;
};



struct ContactCollisionSensor : public btCollisionWorld::ContactResultCallback //collision sensor callback
{
	int collided;
	ContactCollisionSensor() : btCollisionWorld::ContactResultCallback(), collided(0)
	{
	}

	virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0, int partId0, int index0, const btCollisionObjectWrapper* colObj1, int partId1, int index1)
	{
		collided = 1; //if in contact sets the value to 1 else 0
		return 0;
	}
};


struct ColAndreasMultiData
{
	btVector3 pos = btVector3(0,0,0);
	btScalar dist = 0.0;
	int modelId = 0;
};


class ColAndreasWorld
{
public:
	// Initialize ColAndreas
	ColAndreasWorld();

	// ColAndreas closed
	~ColAndreasWorld();

	RemovedBuildingManager* removedManager;
	ObjectManager* objectManager;
	EntityManager* entityManager;
	
	// Converts GTA rotations to quaternion
	btScalar getDist3D(const btVector3& p1, const btVector3& p2);
	void EulerToQuat(btVector3& rotation, btQuaternion& result);
	void QuatToEuler(btQuaternion& rotation, btVector3& result);
	void setMyExtraID(uint16_t index, int type, int data);
	int getMyExtraID(uint16_t index, int type);
	int performRayTest(const btVector3& Start, const btVector3& End, btVector3& Result, uint16_t& model, int world = 0);
	int performRayTestExtraID(const btVector3& Start, const btVector3& End, btVector3& Result, const int type, uint16_t& data, int world = 0);
	int performRayTestID(const btVector3& Start, const btVector3& End, btVector3& Result, uint16_t& index, int world = 0);
	int performRayTestEx(const btVector3& Start, const btVector3& End, btVector3& Result, btQuaternion& Rotation, btVector3& Position, uint16_t& model, int world = 0);
	int performRayTestAngle(const btVector3& Start, const btVector3& End, btVector3& Result, btScalar& RX, btScalar& RY, btScalar& RZ, uint16_t& model, int world = 0);
	int performRayTestAngleEx(const btVector3& Start, const btVector3& End, btVector3& Result, btScalar& RX, btScalar& RY, btScalar& RZ, btQuaternion& Rotation, btVector3& Position, uint16_t& model, int world = 0);
	int performRayTestAll(const btVector3& Start, const btVector3& End, ColAndreasMultiData *data, int size, int world = 0);
	int performRayTestReflection(const btVector3& Start, const btVector3& End, btVector3& Position, btVector3& Result, uint16_t& model, int world = 0);
	int performRayTestNormal(const btVector3& Start, const btVector3& End, btVector3& Result, btVector3& Normal, uint16_t& model, int world = 0);
	int performContactTest(uint16_t modelid, btVector3& objectPos, btQuaternion& objectRot, int world = 0);
	int findShelter(btVector3& pos1, btVector3 & pos2, btVector3& Result, int world = 0);
	btDynamicsWorld* ColAndreasWorld::GetDynamicWorld(int world);

	uint16_t createColAndreasMapObject(uint16_t addtomanager, uint16_t modelid, const btQuaternion& objectRot, const btVector3& objectPos, int world = 0);
	uint16_t getModelRef(uint16_t model);
	void colandreasInitMap();
	bool loadCollisionData();

private:
	MapWaterMesh* mapWaterMesh;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;

	map <int, btDynamicsWorld*> worlds;
};

extern ColAndreasWorld* collisionWorld;

#endif