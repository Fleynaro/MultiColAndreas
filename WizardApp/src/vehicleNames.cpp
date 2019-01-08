#include "vehicleNames.h"

vehicleDFFnames *vehName;

vehicleDFFnames::vehicleDFFnames()
{
}

uint16_t vehicleDFFnames::getModelId(std::string name) {
	name = name.substr(0, name.size() - 4);
	auto it = std::find(this->names.begin(), this->names.end(), name);
	if (it == this->names.end()) return 0;
	return std::distance(this->names.begin(), it) + 400;
}

bool vehicleDFFnames::isVehicleModel(std::string name) {
	return this->getModelId(name) != 0;
}

bool vehicleDFFnames::isVehicle(uint16_t model)
{
	return model >= 400 && model <= 611;
}
