#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <engine/util/Assert.hpp>

namespace engine
{
	namespace util
	{
		template <typename BaseType>
		class Factory
		{
		public:
			using Ptr = std::unique_ptr<BaseType>;

			template <typename SpeType>
			void registerClass(const std::string &name)
			{
				auto pair = _createFunctionByNames.insert(std::make_pair(name, []()
				{
					return new SpeType();
				}));
				ASSERT(pair.second); // fails if name was already registered
			}

			Ptr create(const std::string &name) const
			{
				auto it = _createFunctionByNames.find(name);
				if (it != std::end(_createFunctionByNames))
				{
					return Ptr{ it->second() };
				}
				return Ptr{};
			}

		private:
			using CreateFunction = std::function<BaseType*()>;

			std::map<std::string, CreateFunction> _createFunctionByNames;
		};
	}
}