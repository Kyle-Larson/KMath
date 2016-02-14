#pragma once

#include <vector>
#include "Array.h"

namespace KEngine
{
	namespace Data
	{
		namespace Storage
		{
			template<typename Type>
			class Vector : public std::vector<Type>
			{
			public:
				using std::vector<Type>::vector;

				template<size_t arraySize>
				Array<Type, arraySize> GetDataCopy() const;
			private:
			};
		}
	}
}

#include "Vector.inl"