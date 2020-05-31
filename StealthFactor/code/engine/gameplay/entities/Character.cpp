#include "Character.hpp"

#include <cassert>
#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Character::Character(EntityContext &context)
				: Entity{ context }
			{
				_collisionVolumeId = _context.physicsManager.createCollisionBox(this, gameplay::Manager::CELL_SIZE * 0.9f, gameplay::Manager::CELL_SIZE * 0.9f);
				assert(_collisionVolumeId);
			}

			Character::~Character()
			{
				_context.graphicsManager.destroyShapeListInstance(_shapeListId);
				_context.physicsManager.destroyCollisionVolume(_collisionVolumeId);
			}

			void Character::propagateTransform()
			{
				_context.graphicsManager.setShapeListInstanceTransform(_shapeListId, getTransform());
				_context.physicsManager.setCollisionVolumePosition(_collisionVolumeId, getPosition());
			}
		}
	}
}
