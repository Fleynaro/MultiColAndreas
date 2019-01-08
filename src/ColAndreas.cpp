<<<<<<< HEAD
//*********************************************************************************************************//
// ColAndreas by [uL]Pottus & [uL]Chris42O & [uL]Slice ****************************************************//
//*********************************************************************************************************//

#include <string>
#include <vector>

#include <thread>
#include <mutex>
void testFunct();

using namespace std;

#include <btBulletDynamicsCommon.h>
#include "ColAndreas.h"
#include "DynamicWorld.h"
#include "Natives.h"
#include <chrono>

bool colInit = false;
bool colDataLoaded = false;
cell nullAddress = NULL;

ColAndreasWorld* collisionWorld;

logprintf_t				logprintf;

extern void *pAMXFunctions;

// Plugin Load
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("*********************");
	logprintf("** Created By:     **");
	logprintf("** [uL]Chris42O    **");
	logprintf("** [uL]Slice       **");
	logprintf("** [uL]Pottus      **");
	logprintf("** [uL]Fleynaro    **");
	logprintf("*********************");

	collisionWorld = new ColAndreasWorld();

	if (collisionWorld->loadCollisionData())
	{
		logprintf("Loaded collision data.");
		colDataLoaded = true;
	}
	else
	{
		logprintf("No collision data found.");
	}

	logprintf("*********************");
	logprintf("  ColAndreas Loaded");
	logprintf("   " CA_VERSION);
	logprintf("*********************");

	//collisionWorld->colandreasInitMap();


	//test
	/*collisionWorld->colandreasInitMap();
	int begin = GetTickCount();
	uint16_t Model;
	btVector3 result;
	for (int i = 0; i < 1; i++) {
		collisionWorld->performRayTest(btVector3(-2136.5, -2475.6, 100.5), btVector3(-2136.5, -2375.6, 0.5), result, Model);
	}
	logprintf("------------- complete for %i ms (%i) %f,%f,%f model= %i", GetTickCount() - begin, GetTickCount(), result.getX(), result.getY(), result.getZ(), Model);




	int ca_obj = collisionWorld->createColAndreasMapObject(true, 2320, btQuaternion(0,0,0,1), btVector3(-2436.5, -2375.6, 0.5), 0);
	thread th(testFunct);

	while (true) {
		logprintf("MAIN THREAD");
		for (int i = 0; i < 200; i++) {
			collisionWorld->performRayTest(btVector3(-2136.5, -2475.6, 100.5), btVector3(-2136.5, -2375.6, 0.5), result, Model);
			collisionWorld->objectManager->setObjectPosition(ca_obj, btVector3(-2136.5, -2475.6, 100.5 - i / 1000.0));
			if (Model == 0) {
				logprintf("--- Model = 0");
			}
		}
		this_thread::sleep_for(chrono::milliseconds(600));
	}

	th.join();*/
	return true;
}
void testFunct()
{
	while (true) {
		logprintf("SEPARETE THREAD");
		uint16_t Model;
		btVector3 result;
		for (int i = 0; i < 100; i++) {
			collisionWorld->performRayTest(btVector3(-2136.5, -2475.6, 100.5), btVector3(-2136.5, -2375.6, 0.5), result, Model);
			if (Model == 0) {
				logprintf("--- Model = 0");
			}
		}
		this_thread::sleep_for(chrono::milliseconds(400));
	}
}

//Function export for other plugins(for example PathFinderCA)
extern "C" {
	EXPORT mutex *CA_GetMutex()
	{
		return collisionWorld->objectManager->g_lock;
	}

	EXPORT int CA_RayCastLine(float x1, float y1, float z1, float x2, float y2, float z2, float &x3, float &y3, float &z3, int world)
	{
		uint16_t Model = 0;
		btVector3 Result;
		CA_GetMutex()->lock();
		collisionWorld->performRayTest(btVector3(x1, y1, z1), btVector3(x2, y2, z2), Result, Model, world);
		CA_GetMutex()->unlock();
		x3 = Result.getX();
		y3 = Result.getY();
		z3 = Result.getZ();
		return Model;
	}
}

// Plugin unload
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
//	delete collisionWorld;

	logprintf("*********************");
	logprintf("*ColAndreas Unloaded*");
	logprintf("*********************");

}

// Function list
AMX_NATIVE_INFO PluginNatives[] =
{
	// Standard Natives
	{ "CA_Init", ColAndreasNatives::CA_Init },
	{ "CA_RayCastLine", ColAndreasNatives::CA_RayCastLine },
	{ "CA_RayCastLineExtraID", ColAndreasNatives::CA_RayCastLineExtraID },
	{ "CA_RayCastLineID", ColAndreasNatives::CA_RayCastLineID },
	{ "CA_RayCastLineAngle", ColAndreasNatives::CA_RayCastLineAngle },
	{ "CA_RayCastMultiLine", ColAndreasNatives::CA_RayCastMultiLine },
	{ "CA_RayCastReflectionVector", ColAndreasNatives::CA_RayCastReflectionVector },
	{ "CA_RayCastLineNormal", ColAndreasNatives::CA_RayCastLineNormal },
	{ "CA_ContactTest", ColAndreasNatives::CA_ContactTest },
	{ "CA_CreateObject", ColAndreasNatives::CA_CreateObject },
	{ "CA_DestroyObject", ColAndreasNatives::CA_DestroyObject },
	{ "CA_IsValidObject", ColAndreasNatives::CA_IsValidObject },
	{ "CA_AttachObjectToObject", ColAndreasNatives::CA_AttachObjectToObject },
	{ "CA_DetachObject", ColAndreasNatives::CA_DetachObject },
	{ "CA_EulerToQuat", ColAndreasNatives::CA_EulerToQuat },
	{ "CA_QuatToEuler", ColAndreasNatives::CA_QuatToEuler },
	{ "CA_RemoveBuilding", ColAndreasNatives::CA_RemoveBuilding },
	{ "CA_SetObjectPos", ColAndreasNatives::CA_SetObjectPos },
	{ "CA_SetObjectRot", ColAndreasNatives::CA_SetObjectRot },
	{ "CA_GetModelBoundingSphere", ColAndreasNatives::CA_GetModelBoundingSphere },
	{ "CA_GetModelBoundingBox", ColAndreasNatives::CA_GetModelBoundingBox },
	{ "CA_SetObjectExtraID", ColAndreasNatives::CA_SetObjectExtraID },
	{ "CA_GetObjectExtraID", ColAndreasNatives::CA_GetObjectExtraID },

	// Extended Natives
	{ "CA_RayCastLineEx", ColAndreasNatives::CA_RayCastLineEx },
	{ "CA_RayCastLineAngleEx", ColAndreasNatives::CA_RayCastLineAngleEx },
	{ 0, 0 }
};

// Plugin Export
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}


PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
=======
//*********************************************************************************************************//
// ColAndreas by [uL]Pottus & [uL]Chris42O & [uL]Slice ****************************************************//
//*********************************************************************************************************//

#include <string>
#include <vector>

#include <thread>
#include <mutex>
void testFunct();

using namespace std;

#include <btBulletDynamicsCommon.h>
#include "ColAndreas.h"
#include "DynamicWorld.h"
#include "Natives.h"
#include <chrono>

bool colInit = false;
bool colDataLoaded = false;
cell nullAddress = NULL;

ColAndreasWorld* collisionWorld;

logprintf_t				logprintf;

extern void *pAMXFunctions;

// Plugin Load
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf("*********************");
	logprintf("** Created By:     **");
	logprintf("** [uL]Chris42O    **");
	logprintf("** [uL]Slice       **");
	logprintf("** [uL]Pottus      **");
	logprintf("** [uL]Fleynaro    **");
	logprintf("*********************");

	collisionWorld = new ColAndreasWorld();

	if (collisionWorld->loadCollisionData())
	{
		logprintf("Loaded collision data.");
		colDataLoaded = true;
	}
	else
	{
		logprintf("No collision data found.");
	}

	logprintf("*********************");
	logprintf("  ColAndreas Loaded");
	logprintf("   " CA_VERSION);
	logprintf("*********************");

	collisionWorld->colandreasInitMap();


	//test
	/*collisionWorld->colandreasInitMap();
	int begin = GetTickCount();
	uint16_t Model;
	btVector3 result;
	for (int i = 0; i < 1; i++) {
		collisionWorld->performRayTest(btVector3(-2136.5, -2475.6, 100.5), btVector3(-2136.5, -2375.6, 0.5), result, Model);
	}
	logprintf("------------- complete for %i ms (%i) %f,%f,%f model= %i", GetTickCount() - begin, GetTickCount(), result.getX(), result.getY(), result.getZ(), Model);




	int ca_obj = collisionWorld->createColAndreasMapObject(true, 2320, btQuaternion(0,0,0,1), btVector3(-2436.5, -2375.6, 0.5), 0);
	thread th(testFunct);

	while (true) {
		logprintf("MAIN THREAD");
		for (int i = 0; i < 200; i++) {
			collisionWorld->performRayTest(btVector3(-2136.5, -2475.6, 100.5), btVector3(-2136.5, -2375.6, 0.5), result, Model);
			collisionWorld->objectManager->setObjectPosition(ca_obj, btVector3(-2136.5, -2475.6, 100.5 - i / 1000.0));
			if (Model == 0) {
				logprintf("--- Model = 0");
			}
		}
		this_thread::sleep_for(chrono::milliseconds(600));
	}

	th.join();*/
	return true;
}
void testFunct()
{
	while (true) {
		logprintf("SEPARETE THREAD");
		uint16_t Model;
		btVector3 result;
		for (int i = 0; i < 100; i++) {
			collisionWorld->performRayTest(btVector3(-2136.5, -2475.6, 100.5), btVector3(-2136.5, -2375.6, 0.5), result, Model);
			if (Model == 0) {
				logprintf("--- Model = 0");
			}
		}
		this_thread::sleep_for(chrono::milliseconds(400));
	}
}

//Function export for other plugins(for example PathFinderCA)
extern "C" {
	EXPORT mutex *CA_GetMutex()
	{
		return collisionWorld->objectManager->g_lock;
	}

	EXPORT int CA_RayCastLine(float x1, float y1, float z1, float x2, float y2, float z2, float &x3, float &y3, float &z3, int world)
	{
		uint16_t Model = 0;
		btVector3 Result;
		CA_GetMutex()->lock();
		collisionWorld->performRayTest(btVector3(x1, y1, z1), btVector3(x2, y2, z2), Result, Model, world);
		CA_GetMutex()->unlock();
		x3 = Result.getX();
		y3 = Result.getY();
		z3 = Result.getZ();
		return Model;
	}
}

// Plugin unload
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
//	delete collisionWorld;

	logprintf("*********************");
	logprintf("*ColAndreas Unloaded*");
	logprintf("*********************");

}

// Function list
AMX_NATIVE_INFO PluginNatives[] =
{
	// Standard Natives
	{ "CA_Init", ColAndreasNatives::CA_Init },
	{ "CA_RayCastLine", ColAndreasNatives::CA_RayCastLine },
	{ "CA_RayCastLineExtraID", ColAndreasNatives::CA_RayCastLineExtraID },
	{ "CA_RayCastLineID", ColAndreasNatives::CA_RayCastLineID },
	{ "CA_RayCastLineAngle", ColAndreasNatives::CA_RayCastLineAngle },
	{ "CA_RayCastMultiLine", ColAndreasNatives::CA_RayCastMultiLine },
	{ "CA_RayCastReflectionVector", ColAndreasNatives::CA_RayCastReflectionVector },
	{ "CA_RayCastLineNormal", ColAndreasNatives::CA_RayCastLineNormal },
	{ "CA_ContactTest", ColAndreasNatives::CA_ContactTest },
	{ "CA_CreateObject", ColAndreasNatives::CA_CreateObject },
	{ "CA_DestroyObject", ColAndreasNatives::CA_DestroyObject },
	{ "CA_IsValidObject", ColAndreasNatives::CA_IsValidObject },
	{ "CA_AttachObjectToObject", ColAndreasNatives::CA_AttachObjectToObject },
	{ "CA_DetachObject", ColAndreasNatives::CA_DetachObject },
	{ "CA_EulerToQuat", ColAndreasNatives::CA_EulerToQuat },
	{ "CA_QuatToEuler", ColAndreasNatives::CA_QuatToEuler },
	{ "CA_RemoveBuilding", ColAndreasNatives::CA_RemoveBuilding },
	{ "CA_SetObjectPos", ColAndreasNatives::CA_SetObjectPos },
	{ "CA_SetObjectRot", ColAndreasNatives::CA_SetObjectRot },
	{ "CA_GetModelBoundingSphere", ColAndreasNatives::CA_GetModelBoundingSphere },
	{ "CA_GetModelBoundingBox", ColAndreasNatives::CA_GetModelBoundingBox },
	{ "CA_SetObjectExtraID", ColAndreasNatives::CA_SetObjectExtraID },
	{ "CA_GetObjectExtraID", ColAndreasNatives::CA_GetObjectExtraID },

	// Extended Natives
	{ "CA_RayCastLineEx", ColAndreasNatives::CA_RayCastLineEx },
	{ "CA_RayCastLineAngleEx", ColAndreasNatives::CA_RayCastLineAngleEx },
	{ 0, 0 }
};

// Plugin Export
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}


PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
>>>>>>> d7537e9c90cf6bd17408e3a71e7f8db631f3cd78
