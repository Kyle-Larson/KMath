#pragma once

#include "Vector.h"
#include <assert.h>

namespace KEngine
{
	namespace Data
	{
		namespace Storage
		{
			template<typename Type>
			template<size_t arraySize>
			inline Array<Type, arraySize> Vector<Type>::GetDataCopy() const
			{
				assert(arraySize > size());
				Array<Type, arraySize> returnValue;
				std::copy(begin(), end(), returnValue.begin());
				return returnValue;
			}
		}
	}
}