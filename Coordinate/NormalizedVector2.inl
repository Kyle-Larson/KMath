#pragma once

#include "NormalizedVector.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			inline NormalizedVector<2>::NormalizedVector()
				: m_vector(1.0f, 0.0f) {}
			inline NormalizedVector<2>::NormalizedVector(const Vector<2>& p_vector)
				: m_vector(p_vector.Normalize()) {}

			inline NormalizedVector<2>::operator Vector<2>() const
			{
				return m_vector;
			}

			inline bool NormalizedVector<2>::operator==(const NormalizedVector<2>& p_rhs) const
			{
				return m_vector == p_rhs;
			}
			inline bool NormalizedVector<2>::operator!=(const NormalizedVector<2>& p_rhs) const
			{
				return m_vector != p_rhs;
			}
			inline bool NormalizedVector<2>::operator==(const Vector<2>& p_rhs) const
			{
				return m_vector == p_rhs;
			}
			inline bool NormalizedVector<2>::operator!=(const Vector<2>& p_rhs) const
			{
				return m_vector != p_rhs;
			}

			inline NormalizedVector<2> NormalizedVector<2>::operator-() const
			{
				NormalizedVector<2> returnValue;
				returnValue.m_vector = -m_vector;
				return returnValue;
			}

			inline float NormalizedVector<2>::Magnitude() const
			{
				return 1.0f;
			}
			inline NormalizedVector<2> NormalizedVector<2>::Perpendicular() const
			{
				NormalizedVector<2> returnVector;
				returnVector.m_vector = m_vector.Orthogonal();
				return returnVector;
			}

			inline float NormalizedVector<2>::Dot(const Vector<2>& p_vector) const
			{
				return m_vector.Dot(p_vector);
			}

			Data::Storage::Array<float, 2> NormalizedVector<2>::Unload() const
			{
				return m_vector.Unload();
			}
		}
	}
}