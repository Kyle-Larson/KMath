#pragma once

#include "NormalizedVector.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			template<size_t vectorLength>
			inline NormalizedVector<vectorLength>::NormalizedVector()
				: m_vector()
			{
				m_vector.GetXMVectors()[0] = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
			}
			template<size_t vectorLength>
			inline NormalizedVector<vectorLength>::NormalizedVector(const Vector<vectorLength>& p_vector)
				: m_vector(p_vector.Normalize()) {}

			template<size_t vectorLength>
			inline NormalizedVector<vectorLength>::operator Vector<vectorLength>() const
			{
				return m_vector;
			}

			template<size_t vectorLength>
			inline bool NormalizedVector<vectorLength>::operator==(const NormalizedVector<vectorLength>& p_rhs) const
			{
				return m_vector == p_rhs;
			}
			template<size_t vectorLength>
			inline bool NormalizedVector<vectorLength>::operator!=(const NormalizedVector<vectorLength>& p_rhs) const
			{
				return m_vector != p_rhs;
			}
			template<size_t vectorLength>
			inline bool NormalizedVector<vectorLength>::operator==(const Vector<vectorLength>& p_rhs) const
			{
				return m_vector == p_rhs;
			}
			template<size_t vectorLength>
			inline bool NormalizedVector<vectorLength>::operator!=(const Vector<vectorLength>& p_rhs) const
			{
				return m_vector != p_rhs;
			}

			template<size_t vectorLength>
			inline NormalizedVector<vectorLength> NormalizedVector<vectorLength>::operator-() const
			{
				NormalizedVector<vectorLength> returnValue;
				returnValue.m_vector = -m_vector;
				return returnValue;
			}

			template<size_t vectorLength>
			inline float NormalizedVector<vectorLength>::Magnitude() const
			{
				return 1.0f;
			}

			template<size_t vectorLength>
			inline float NormalizedVector<vectorLength>::Dot(const Vector<vectorLength>& p_vector) const
			{
				return m_vector.Dot(p_vector);
			}

			template<size_t vectorLength>
			Data::Storage::Array<float, vectorLength> NormalizedVector<vectorLength>::Unload() const
			{
				return m_vector.Unload();
			}
		}
	}
}