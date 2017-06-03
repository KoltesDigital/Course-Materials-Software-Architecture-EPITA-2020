#pragma once

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <engine/serialization/TypeInfo.hpp>
#include <engine/util/Assert.hpp>

namespace engine
{
	namespace serialization
	{
		class TypeRegistry
		{
		public:
			using CreateFunction = std::function<void *()>;

			struct Info
			{
				CreateFunction create;
				const TypeInfo &typeInfo;
			};

			template <typename T>
			void registerClass()
			{
				auto pair = _infoByNames.insert(std::make_pair(getClassName<T>(), Info
					{
						[]() -> void *
						{
							return new T;
						},
						TypeInfoValue<T *>::value
					}));
				ASSERT(pair.second); // fails if name was already registered
			}

			const Info *getInfo(const std::string &name) const
			{
				auto it = _infoByNames.find(name);
				if (it != std::end(_infoByNames))
				{
					return &it->second;
				}
				return nullptr;
			}

		private:
			std::map<std::string, Info> _infoByNames;
		};
	}
}
