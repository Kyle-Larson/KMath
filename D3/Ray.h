#pragma once

#include <DirectXMath.h>
#include "Coordinate/Vector.h"
#include "Coordinate/NormalizedVector.h"

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			class Ray
			{
			public:
				Ray();
				constexpr Ray(const Coordinate::Vector<3>& p_origin, const Coordinate::NormalizedVector<3>& p_rayDirection);
				Ray(const Coordinate::Vector<3>& p_origin, const Coordinate::Vector<3>& p_pointOnRay);

				const Coordinate::Vector<3>& GetOrigin() const;
				Coordinate::Vector<3>& GetOrigin();

				const Coordinate::NormalizedVector<3>& GetDirection() const;
				Coordinate::NormalizedVector<3>& GetDirection();
			private:
				Coordinate::Vector<3> m_origin;
				Coordinate::NormalizedVector<3> m_rayDirection;
			};
		}
	}
}

#include "Ray.inl"