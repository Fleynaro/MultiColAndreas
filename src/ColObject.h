#ifndef _INCL_COLOBJECT
#define _INCL_COLOBJECT

#include <btBulletDynamicsCommon.h>
#include "ColAndreasDatabaseReader.h"
#include "ColAndreas.h"
#include "LodArray.h"
#include <shared_mutex>
#include <mutex>

#define MAX_MAP_OBJECTS 65000

struct removeBuildingData
{
	uint16_t r_Model;
	float r_X;
	float r_Y;
	float r_Z;
	float r_Radius;
};

static uint16_t colindex = 0;
 		 
// Data structure to track in-game objects with respect to their colindex
struct ColAndreasObjectTracker
{
public:
	int32_t realIndex;
    int32_t extraData[10];

    ColAndreasObjectTracker(){
        realIndex = -1;
        for(int i = 0; i < 10; i++)
            extraData[i] = -1;
    }
    ~ColAndreasObjectTracker() {
        realIndex = -1;
        for(int i = 0; i < 10; i++)
            extraData[i] = -1;
    }
};

// Collision Objects
class ColAndreasColObject
{
public:
	ColAndreasColObject() {};
	ColAndreasColObject(uint16_t colindex, bool thirdparty) {
		createMesh(colindex, thirdparty);
	}
	~ColAndreasColObject();

	void createMesh(uint16_t colindex, bool thirdparty);
	void createSkinMesh(uint16_t skinid);
	btCompoundShape* getCompoundShape();
private:
	// Object Data
	btCompoundShape* colMapObject;

	// Mesh
	btTriangleMesh* trimesh;
	btTriangleMeshShape* meshshape;
	std::vector <btSphereShape*> spheres;
	std::vector <btBoxShape*> boxes;
};

// Map Objects
class ColAndreasMapObject
{
public:
	ColAndreasMapObject(uint16_t modelid, const btQuaternion& objectRot, const btVector3& objectPos, btDynamicsWorld* world);
	~ColAndreasMapObject();
	void setMapObjectPosition(btVector3& position);
	void setMapObjectRotation(btQuaternion& rotation);
	void attachToMapObject(ColAndreasMapObject *object, btVector3& position, btQuaternion& rotation);
	void makeOtherShapeForAttaching();
	void makeGenShape();
	void detach();
	bool isAttched();
	ColAndreasObjectTracker* tracker;

	btRigidBody* getRigidBody() {
		return this->colMapRigidBody;
	}
private:
	// Object Data
	btRigidBody* colMapRigidBody;
	btCompoundShape* colMapCompoundShape;
	btDefaultMotionState* colMapObjectPosition;
	btDynamicsWorld* collisionWorld;
	ColAndreasMapObject* colMapAttachObject;
	bool colMapAttach = false;
};


class MapWaterMesh
{
public:
	MapWaterMesh(btDynamicsWorld* world);
	~MapWaterMesh();
private:
	btTriangleMesh* trimesh;
	btBvhTriangleMeshShape* meshshape;
	btDefaultMotionState* meshposition;
	btRigidBody* meshRigidBody;
	btDynamicsWorld* collisionWorld;
};


class ObjectManager
{
public:
	shared_mutex *g_lock;
	ObjectManager();
	int addObjectManager(ColAndreasMapObject* mapObject);
	int removeObjectManager(const uint16_t index);
	int validObjectManager(const uint16_t index);
	int setObjectPosition(const uint16_t index, btVector3& position);
	int setObjectRotation(const uint16_t index, btQuaternion& rotation);
	int getBoundingSphere(uint16_t modelid, btVector3& center, btScalar& radius);
	int getBoundingBox(uint16_t modelid, btVector3& min, btVector3& max);	      
	int setExtraID(const uint16_t index, int type, int data);
	int getExtraID(const uint16_t index, int type);
	int attachObjectToObject(const uint16_t index1, const uint16_t index2, btVector3& position, btQuaternion& rotation);
	int detach(const uint16_t index);
private:
	bool slotUsed[MAX_MAP_OBJECTS];
	ColAndreasMapObject* mapObjects[MAX_MAP_OBJECTS];
};


class RemovedBuildingManager
{
public:
	RemovedBuildingManager();
	bool isRemoved(uint16_t model, Vector position);
	void addBuilding(removeBuildingData removeData);
private:
	std::vector <removeBuildingData> removedBuildings;
};

bool LoadCollisionData();
void InitCollisionMap(btDynamicsWorld* collisionWorld, RemovedBuildingManager* removeManager);
uint16_t GetModelRef(uint16_t model);

// Pointer reference
extern std::vector <ColAndreasColObject*> colObjects;
extern std::vector <btCompoundShape*> colConvex; //for the sake of contact tests

typedef struct {
	btVector3 pos;
	btScalar dist;
} btMultiCast;
#endif