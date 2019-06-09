#pragma once

#include <algorithm>
#include <memory>
#include <set>
#include <engine/gameplay/Component.hpp>
#include <engine/util/Assert.hpp>

namespace engine
{
	namespace gameplay
	{
		struct EntityContext;

		class Entity
		{
		public:
			Entity(EntityContext &context);
			virtual ~Entity() = default;

			void update();
			void onTransformChange();

			EntityContext &getContext();
			const EntityContext &getContext() const;

			template <typename Component>
			Component &addComponent();

			template <typename Component>
			Component *getComponent() const;

		private:
			using ComponentPtr = std::unique_ptr<Component>;
			using ComponentSet = std::set<ComponentPtr>;

			EntityContext &_context;

			ComponentSet _components;
		};

		template <typename Component>
		inline Component &Entity::addComponent()
		{
			ASSERT(getComponent<Component>() == nullptr);
			auto component{ new Component(*this) };
			_components.insert(ComponentPtr{ component });
			return *component;
		}

		template <typename Component>
		inline Component *Entity::getComponent() const
		{
			auto it = std::find_if(
				std::begin(_components),
				std::end(_components),
				[](const ComponentPtr &component)
			{
				return dynamic_cast<Component *>(component.get()) != nullptr;
			});

			if (it != std::end(_components))
			{
				return reinterpret_cast<Component *>(it->get());
			}

			return nullptr;
		}
	}
}
