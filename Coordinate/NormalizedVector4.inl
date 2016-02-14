#pragma once

#include "NormalizedVector.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			inline NormalizedVector<4>::NormalizedVector()
				: m_vector(1.0f, 0.0f, 0.0f, 0.0f) {}
			inline NormalizedVector<4>::NormalizedVector(const Vector<4>& p_vector)
				: m_vector(p_vector.Normalize()) {}

			inline NormalizedVector<4>::operator Vector<4>() const
			{
				return m_vector;
			}

			inline bool NormalizedVector<4>::operator==(const NormalizedVector<4>& p_rhs) const
			{
				return m_vector == p_rhs;
			}
			inline bool NormalizedVector<4>::operator!=(const NormalizedVector<4>& p_rhs) const
			{
				return m_vector != p_rhs;
			}
			inline bool NormalizedVector<4>::operator==(const Vector<4>& p_rhs) const
			{
				return m_vector == p_rhs;
			}
			inline bool NormalizedVector<4>::operator!=(const Vector<4>& p_rhs) const
			{
				return m_vector != p_rhs;
			}

			inline NormalizedVector<4> NormalizedVector<4>::operator-() const
			{
				NormalizedVector<4> returnValue;
				returnValue.m_vector = -m_vector;
				return returnValue;
			}

			inline float NormalizedVector<4>::Magnitude() const
			{
				return 1.0f;
			}

			inline float NormalizedVector<4>::Dot(const Vector<4>& p_vector) const
			{
				return m_vector.Dot(p_vector);
			}

			Data::Storage::Array<float, 4> NormalizedVector<4>::Unload() const
			{
				return m_vector.Unload();
			}
		}
	}
}