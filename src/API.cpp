#include "API.h"

using namespace API;

ColAndreas::ColAndreas()
{
	this->mutex = collisionWorld->objectManager->g_lock;
}

shared_mutex * ColAndreas::getMutex() {
	return this->mutex;
}

int ColAndreas::performRayTest(API::Vector& pos1, API::Vector& pos2, API::Vector& pos, int world)
{
	uint16_t Model = 0;
	btVector3 Result;

	{
		std::shared_lock<std::shared_mutex> lock(*this->getMutex());
		collisionWorld->performRayTest(pos1.getBtVector3(), pos2.getBtVector3(), Result, Model, world);
	}

	pos.setBtVector3(Result);
	return Model;
}

int ColAndreas::performRayTestExtraID(API::Vector& pos1, API::Vector& pos2, API::Vector& pos, int type, uint32_t& data, uint16_t& model, int world)
{
	btVector3 Result;
	
	{
		std::shared_lock<std::shared_mutex> lock(*this->getMutex());
		collisionWorld->performRayTestExtraID(pos1.getBtVector3(), pos2.getBtVector3(), Result, type, data, model, world);
	}

	pos.setBtVector3(Result);
	return 1;
}

int ColAndreas::performRayTestID(API::Vector & pos1, API::Vector & pos2, API::Vector & pos, uint32_t & index, int world)
{
	btVector3 Result;

	{
		std::shared_lock<std::shared_mutex> lock(*this->getMutex());
		collisionWorld->performRayTestID(pos1.getBtVector3(), pos2.getBtVector3(), Result, index, world);
	}

	pos.setBtVector3(Result);
	return 0;
}

int ColAndreas::performRayTestAll(API::Vector & pos1, API::Vector & pos2, hitPoint * data, int size, int world)
{
	ColAndreasMultiData *Data = new ColAndreasMultiData[size];
	{
		std::shared_lock<std::shared_mutex> lock(*this->getMutex());
		collisionWorld->performRayTestAll(pos1.getBtVector3(), pos2.getBtVector3(), Data, size, world);
	}

	uint16_t size_ = 0;
	while (size_ < size && Data[size_].modelId != 0)
	{
		data[size_].modelId = Data[size_].modelId;
		data[size_].pos.setBtVector3(Data[size_].pos);
		size_++;
	}
	return 0;
}
