#pragma once

#include <engine/graphics/ShapeListId.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/physics/CollisionVolumeId.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Character : public Entity
			{
			public:
				Character(EntityContext &context);
				virtual ~Character();

				void propagateTransform();

			protected:
				graphics::ShapeListId _shapeListId;
				physics::CollisionVolumeId _collisionVolumeId;

				bool _isWalking{ false };
			};
		}
	}
}
