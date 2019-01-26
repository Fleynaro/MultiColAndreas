//*********************************************************************************************************//
// ColAndreas by [uL]Pottus & [uL]Chris42O & [uL]Slice ****************************************************//
//*********************************************************************************************************//

#include <string>
#include <vector>

using namespace std;

#include <btBulletDynamicsCommon.h>
#include "ColAndreas.h"
#include "DynamicWorld.h"
#include "Natives.h"
#include <chrono>
#include "NetGame.h"
#include "API.h"

bool colInit = false;
bool colDataLoaded = false;
cell nullAddress = NULL;
void **ppPluginData;
API::ColAndreas *api;

ColAndreasWorld* collisionWorld = NULL;
logprintf_t		logprintf;
extern void *pAMXFunctions;



// Plugin Export
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

// Plugin Load
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	ppPluginData = ppData;
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

	api = new API::ColAndreas();
	return true;
}

extern "C" {

	EXPORT API::ColAndreas *CA_getAPI() {
		return api;
	}

};

// Plugin unload
PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
//	delete collisionWorld;

	logprintf("*********************");
	logprintf("*ColAndreas Unloaded*");
	logprintf("*********************");

	delete api;
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
	{ "CA_FindShelter", ColAndreasNatives::CA_FindShelter },

	// Extended Natives
	{ "CA_RayCastLineEx", ColAndreasNatives::CA_RayCastLineEx },
	{ "CA_RayCastLineAngleEx", ColAndreasNatives::CA_RayCastLineAngleEx },

	//MultiColAndreas
	{ "CA_AddVehicle",		ColAndreasNatives::CA_AddVehicle },
	{ "CA_AddPlayer",		ColAndreasNatives::CA_AddPlayer },
	{ "CA_RemoveVehicle",	ColAndreasNatives::CA_RemoveVehicle },
	{ "CA_RemovePlayer",	ColAndreasNatives::CA_RemovePlayer },
	{ "CA_ExecuteUpdate",	ColAndreasNatives::CA_ExecuteUpdate },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	static bool bFirst = false;
	if (!bFirst && !NetGame::getInstance().isInit()) {
		int(*pfn_GetNetGame)(void) = (int(*)(void))ppPluginData[PLUGIN_DATA_NETGAME];
		NetGame::getInstance().Init(pfn_GetNetGame());

		bFirst = true;
	}
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	//not working for a strange reason. help please who can!

	/*static int ticked = 1;
	logprintf("timer pass!");
	if (ticked == 10) {
		if (NetGame::getInstance().isInit())
		{
			collisionWorld->entityManager->executeUpdate();
		}
		ticked = 0;
	}
	ticked++;*/
}