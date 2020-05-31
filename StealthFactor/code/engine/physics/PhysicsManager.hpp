#pragma once

#include <set>
#include <vector>
#include <ode/common.h>
#include <SFML/System/Vector2.hpp>
#include <engine/physics/CollisionVolumeId.hpp>

namespace engine
{
	namespace gameplay
	{
		class Entity;
	}

	namespace physics
	{
		class Manager
		{
		public:
			bool setUp();
			void tearDown();

			void update();

			CollisionVolumeId createCollisionBox(gameplay::Entity *entity, float width, float height);
			void destroyCollisionVolume(CollisionVolumeId id);

			void setCollisionVolumePosition(CollisionVolumeId id, const sf::Vector2f &position);

			std::set<gameplay::Entity *> getCollisionsWith(CollisionVolumeId id) const;

		private:
			struct Collision
			{
				dGeomID o1;
				dGeomID o2;

				Collision(dGeomID o1, dGeomID o2);
			};

			using Collisions = std::vector<Collision>;

			dSpaceID _spaceId{};
			Collisions _frameCollisions;

			static void nearCallback(void *data, dGeomID o1, dGeomID o2);
		};
	}
}
