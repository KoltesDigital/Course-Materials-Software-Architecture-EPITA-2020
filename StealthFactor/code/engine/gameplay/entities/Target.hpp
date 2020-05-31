#pragma once

#include <ode/collision.h>
#include <engine/graphics/ShapeListId.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/physics/CollisionVolumeId.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Target : public Entity
			{
			public:
				Target(EntityContext &context);
				~Target();

				virtual void update() override;

				void propagateTransform();

			private:
				graphics::ShapeListId _shapeListId;
				physics::CollisionVolumeId _collisionVolumeId;
			};
		}
	}
}
