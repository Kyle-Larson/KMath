#pragma once

#include "NormalizedVector.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			inline NormalizedVector<3>::NormalizedVector()
				: m_vector(1.0f, 0.0f, 0.0f) {}
			inline NormalizedVector<3>::NormalizedVector(const Vector<3>& p_vector)
				: m_vector(p_vector.Normalize()) {}

			inline NormalizedVector<3>::operator Vector<3>() const
			{
				return m_vector;
			}

			inline bool NormalizedVector<3>::operator==(const NormalizedVector<3>& p_rhs) const
			{
				return m_vector == p_rhs;
			}
			inline bool NormalizedVector<3>::operator!=(const NormalizedVector<3>& p_rhs) const
			{
				return m_vector != p_rhs;
			}
			inline bool NormalizedVector<3>::operator==(const Vector<3>& p_rhs) const
			{
				return m_vector == p_rhs;
			}
			inline bool NormalizedVector<3>::operator!=(const Vector<3>& p_rhs) const
			{
				return m_vector != p_rhs;
			}

			inline NormalizedVector<3> NormalizedVector<3>::operator-() const
			{
				NormalizedVector<3> returnValue;
				returnValue.m_vector = -m_vector;
				return returnValue;
			}

			inline float NormalizedVector<3>::Magnitude() const
			{
				return 1.0f;
			}

			inline float NormalizedVector<3>::Dot(const Vector<3>& p_vector) const
			{
				return m_vector.Dot(p_vector);
			}

			Data::Storage::Array<float, 3> NormalizedVector<3>::Unload() const
			{
				return m_vector.Unload();
			}
		}
	}
}