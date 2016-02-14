#pragma once

#include "Vector.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			constexpr Vector<4>::Vector() : m_vectorArray() {}
			constexpr Vector<4>::Vector(const Data::Storage::Array<float, 4>& p_array) :
				m_vectorArray({ DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(p_array.data())) }) {}
			constexpr Vector<4>::Vector(float fillValue) : m_vectorArray({ DirectX::XMVectorReplicate(fillValue) }) {}
			constexpr Vector<4>::Vector(float p_x, float p_y, float p_z, float p_w) : m_vectorArray({ DirectX::XMVectorSet(p_x, p_y, p_z, p_w) }) {}
			constexpr Vector<4>::Vector(const DirectX::FXMVECTOR p_vector) : m_vectorArray({ p_vector }) {}

			constexpr Vector<4>::operator DirectX::XMVECTOR() const
			{
				return m_vectorArray[0];
			}
			inline Vector<2> Vector<4>::ToVector2() const
			{
				return Vector<2>(m_vectorArray[0]);
			}
			inline Vector<3> Vector<4>::ToVector3() const
			{
				return Vector<3>(m_vectorArray[0]);
			}
			constexpr Vector<4> Vector<4>::operator-() const
			{
				return Vector<4>(DirectX::XMVectorNegate(m_vectorArray[0]));
			}

			inline bool Vector<4>::operator==(const Vector<4>& p_rhs) const
			{
				return DirectX::XMVector4Equal(m_vectorArray[0], p_rhs);
			}
			inline bool Vector<4>::operator!=(const Vector<4>& p_rhs) const
			{
				return DirectX::XMVector4NotEqual(m_vectorArray[0], p_rhs);
			}

			constexpr Vector<4> Vector<4>::operator+(const Vector<4>& p_vector) const
			{
				return Vector<4>(DirectX::XMVectorAdd(*this, p_vector));
			}
			constexpr Vector<4> Vector<4>::operator-(const Vector<4>& p_vector) const
			{
				return Vector<4>(DirectX::XMVectorSubtract(*this, p_vector));
			}
			constexpr Vector<4> Vector<4>::operator*(float p_scale) const
			{
				return Vector<4>(DirectX::XMVectorScale(*this, p_scale));
			}
			constexpr Vector<4> Vector<4>::operator/(float p_scale) const
			{
				return operator*(1.0f / p_scale);
			}

			inline Vector<4>& Vector<4>::operator+=(const Vector<4>& p_rhs)
			{
				m_vectorArray[0] = DirectX::XMVectorAdd(*this, p_rhs);
				return *this;
			}
			inline Vector<4>& Vector<4>::operator-=(const Vector<4>& p_rhs)
			{
				m_vectorArray[0] = DirectX::XMVectorSubtract(*this, p_rhs);
				return *this;
			}
			inline Vector<4>& Vector<4>::operator*=(float p_scale)
			{
				m_vectorArray[0] = DirectX::XMVectorScale(*this, p_scale);
				return *this;
			}
			inline Vector<4>& Vector<4>::operator/=(float p_scale)
			{
				m_vectorArray[0] = DirectX::XMVectorScale(*this, 1.0f / p_scale);
				return *this;
			}

			constexpr Vector<4> Vector<4>::Normalize() const
			{
				return Vector<4>(DirectX::XMVector4Normalize(m_vectorArray[0]));
			}
			constexpr float Vector<4>::Magnitude() const
			{
				return DirectX::XMVectorGetX(DirectX::XMVector4Length(m_vectorArray[0]));
			}
			inline Vector<4> Vector<4>::Orthogonal() const
			{
				return Vector<4>(DirectX::XMVector4Orthogonal(*this));
			}

			inline Vector<4> Vector<4>::ClampLength(float minLength, float maxLength) const
			{
				return Vector<4>(DirectX::XMVector4ClampLength(*this, minLength, maxLength));
			}

			constexpr float Vector<4>::Dot(const Vector<4>& p_v) const
			{
				return DirectX::XMVectorGetX(DirectX::XMVector4Dot(*this, p_v));
			}
			inline Vector<4> Vector<4>::Reflect(const NormalizedVector<4>& p_reflectionNormal) const
			{
				return Vector<4>(DirectX::XMVector4Reflect(*this, static_cast<Vector<4>>(p_reflectionNormal)));
			}
			inline Vector<4> Vector<4>::Refract(const NormalizedVector<4>& p_refractionNormal, float p_refractionIndex) const
			{
				return Vector<4>(DirectX::XMVector4Refract(*this, static_cast<Vector<4>>(p_refractionNormal), p_refractionIndex));
			}

			template<size_t index>
			constexpr float Vector<4>::GetFloatByIndex() const
			{
				static_assert(index < 4, "Invalid index given");
				return DirectX::XMVectorGetByIndex(m_vectorArray[0], index);
			}
			template<size_t index, size_t newVectorLength>
			Vector<newVectorLength> Vector<4>::SplatFloatByIndex() const
			{
				static_assert(index < 4, "Invalid index given");
				Vector<newVectorLength> returnVector;
				DirectX::XMVECTOR splatVector;
				switch (index % 4)
				{
				case 0:
					splatVector = DirectX::XMVectorSplatX(m_vectorArray[0]);
					break;
				case 1:
					splatVector = DirectX::XMVectorSplatY(m_vectorArray[0]);
					break;
				case 2:
					splatVector = DirectX::XMVectorSplatZ(m_vectorArray[0]);
					break;
				case 3:
					splatVector = DirectX::XMVectorSplatW(m_vectorArray[0]);
					break;
				}
				auto& m_vecArrayRef = returnVector.GetXMVectors();
				for (auto& vector : m_vecArrayRef)
				{
					vector = splatVector;
				}
				return returnVector;
			}
			inline auto Vector<4>::GetXMVectors() const
				-> const Data::Storage::Array<DirectX::XMVECTOR, 1>&
			{
				return m_vectorArray;
			}
			inline auto Vector<4>::GetXMVectors()
				-> Data::Storage::Array<DirectX::XMVECTOR, 1>&
			{
				return m_vectorArray;
			}

			inline Vector<4> Vector<4>::MemberwiseMultiply(const Vector<4>& p_rhs) const
			{
				return Vector<4>(DirectX::XMVectorMultiply(*this, p_rhs));
			}

			inline void Vector<4>::Load(const Data::Storage::Array<float, 4>& p_array)
			{
				m_vectorArray[0] = DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(&p_array));
			}
			inline Data::Storage::Array<float, 4> Vector<4>::Unload() const
			{
				Data::Storage::Array<float, 4> returnValue;
				DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&returnValue), m_vectorArray[0]);
				return returnValue;
			}

			inline float Vector<4>::AngleBetween(const NormalizedVector<4>& vectorA, const NormalizedVector<4>& vectorB)
			{
				return DirectX::XMVectorGetX(DirectX::XMVector4AngleBetweenNormals(static_cast<Vector<4>>(vectorA), static_cast<Vector<4>>(vectorB)));
			}
			inline float Vector<4>::AngleBetween(const Vector<4>& vectorA, const Vector<4>& vectorB)
			{
				return DirectX::XMVectorGetX(DirectX::XMVector4AngleBetweenVectors(vectorA, vectorB));
			}
		}
	}
}