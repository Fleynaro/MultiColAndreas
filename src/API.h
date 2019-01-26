#pragma once


#include <thread>
#include <shared_mutex>
#include <mutex>
#include "ColAndreas.h"
#include "DynamicWorld.h"


namespace API
{
	struct Vector {
	public:
		float x = 0.0, y = 0.0, z = 0.0;
		btVector3 getBtVector3() {
			return btVector3(x, y, z);
		}
		void setBtVector3(btVector3 &vector) {
			x = vector.getX();
			y = vector.getY();
			z = vector.getZ();
		}
	};

	struct hitPoint
	{
		Vector pos;
		int modelId = 0;
	};

	class IEColAndreas
	{
	public:
		virtual std::shared_mutex *getMutex() = 0;
		virtual int performRayTest(Vector& pos1, Vector& pos2, Vector& pos, int world) = 0;
		virtual int performRayTestExtraID(Vector& pos1, Vector& pos2, Vector& pos, int type, uint32_t& data, uint16_t& model, int world = 0) = 0;
		virtual int performRayTestID(Vector& pos1, Vector& pos2, Vector& pos, uint32_t& index, int world = 0) = 0;
		virtual int performRayTestAll(Vector& pos1, Vector& pos2, hitPoint *data, int size, int world = 0) = 0;
	};

	class EXPORT ColAndreas : public IEColAndreas
	{
	public:
		ColAndreas();
		std::shared_mutex *getMutex() override;
		int performRayTest(Vector& pos1, Vector& pos2, Vector& pos, int world) override;
		int performRayTestExtraID(Vector& pos1, Vector& pos2, Vector& pos, int type, uint32_t& data, uint16_t& model, int world = 0) override;
		int performRayTestID(Vector& pos1, Vector& pos2, Vector& pos, uint32_t& index, int world = 0) override;
		int performRayTestAll(Vector& pos1, Vector& pos2, hitPoint *data, int size, int world = 0) override;
	private:
		shared_mutex *mutex;
	};
};