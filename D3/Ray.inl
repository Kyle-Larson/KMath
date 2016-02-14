#pragma once

#include "Ray.h"

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			inline Ray::Ray() : m_origin(), m_rayDirection() {}
			constexpr Ray::Ray(const Coordinate::Vector<3>& p_origin, const Coordinate::NormalizedVector<3>& p_rayDirection)
				: m_origin(p_origin), m_rayDirection(p_rayDirection) {}
			inline Ray::Ray(const Coordinate::Vector<3>& p_origin, const Coordinate::Vector<3>& p_pointOnRay)
				: m_origin(p_origin), m_rayDirection(p_pointOnRay - p_origin) {}

			inline const Coordinate::Vector<3>& Ray::GetOrigin() const
			{
				return m_origin;
			}
			inline Coordinate::Vector<3>& Ray::GetOrigin()
			{
				return m_origin;
			}

			inline const Coordinate::NormalizedVector<3>& Ray::GetDirection() const
			{
				return m_rayDirection;
			}
			inline Coordinate::NormalizedVector<3>& Ray::GetDirection()
			{
				return m_rayDirection;
			}
		}
	}
}