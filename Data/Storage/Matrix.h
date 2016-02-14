#pragma once

#include "Array.h"

namespace KEngine
{
	namespace Data
	{
		namespace Storage
		{
			template<typename Type, size_t rows, size_t columns>
			using Matrix = Array<Array<Type, columns>, rows>;
		}
	}
}