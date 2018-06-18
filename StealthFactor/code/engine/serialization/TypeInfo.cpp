#include "TypeInfo.hpp"

namespace engine
{
	namespace serialization
	{
		template <>
		TypeInfo TypeInfoValue<unsigned char>::value = TypeInfo{ Type::UnsignedChar };

		template <>
		TypeInfo TypeInfoValue<int>::value = TypeInfo{ Type::Int };

		template <>
		TypeInfo TypeInfoValue<float>::value = TypeInfo{ Type::Float };

		template <>
		TypeInfo TypeInfoValue<std::string>::value = TypeInfo{ Type::String };

	}
}
