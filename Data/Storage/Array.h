#pragma once

#include <array>

namespace KEngine
{
	namespace Data
	{
		namespace Storage
		{
			template<typename Type, size_t size>
			using Array = std::array<Type, size>;
		}
	}
}