#pragma once

#include <KMathConstants.h>
#include "Coordinate/Vector.h"

namespace KEngine
{
	namespace Math
	{
		namespace D2
		{
			class Ray
			{
			public:
				Ray();
				constexpr Ray(const Coordinate::Vector<2>& p_origin, const Coordinate::NormalizedVector<2>& p_rayDirection);
				Ray(const Coordinate::Vector<2>& p_origin, const Coordinate::Vector<2>& p_pointOnRay);

				const Coordinate::Vector<2>& GetOrigin() const;
				Coordinate::Vector<2>& GetOrigin();

				const Coordinate::NormalizedVector<2>& GetDirection() const;
				Coordinate::NormalizedVector<2>& GetDirection();
			private:
				Coordinate::Vector<2> m_origin;
				Coordinate::NormalizedVector<2> m_rayDirection;
			};
		}
	}
}