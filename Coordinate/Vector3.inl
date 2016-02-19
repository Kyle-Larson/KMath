#pragma once

#include "Vector.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			inline Vector<3>::Vector() : m_vectorArray() {}
			inline Vector<3>::Vector(const Data::Storage::Array<float, 3>& p_array) :
				m_vectorArray({ DirectX::XMLoadFloat3(reinterpret_cast<const DirectX::XMFLOAT3*>(p_array.data())) }) {}
			inline Vector<3>::Vector(float fillValue) : m_vectorArray({ DirectX::XMVectorReplicate(fillValue) }) {}
			inline Vector<3>::Vector(float p_x, float p_y, float p_z) : m_vectorArray({ DirectX::XMVectorSet(p_x, p_y, p_z, 1.0f) }) {}
			inline Vector<3>::Vector(const DirectX::FXMVECTOR p_vector) : m_vectorArray({ p_vector }) {}
			inline Vector<3>::operator DirectX::XMVECTOR() const
			{
				return m_vectorArray[0];
			}
			inline Vector<2> Vector<3>::ToVector2() const
			{
				return Vector<2>(m_vectorArray[0]);
			}
			inline Vector<4> Vector<3>::ToVector4(float p_W) const
			{
				DirectX::XMVECTOR newVec = m_vectorArray[0];
				DirectX::XMVectorSetW(newVec, p_W);
				return Vector<4>(newVec);
			}

			inline Vector<3> Vector<3>::operator-() const
			{
				return Vector<3>(DirectX::XMVectorNegate(m_vectorArray[0]));
			}

			inline bool Vector<3>::operator==(const Vector<3>& p_rhs) const
			{
				return DirectX::XMVector3Equal(m_vectorArray[0], p_rhs);
			}
			inline bool Vector<3>::operator!=(const Vector<3>& p_rhs) const
			{
				return DirectX::XMVector3NotEqual(m_vectorArray[0], p_rhs);
			}

			inline Vector<3> Vector<3>::operator+(const Vector<3>& p_vector) const
			{
				return Vector<3>(DirectX::XMVectorAdd(*this, p_vector));
			}
			inline Vector<3> Vector<3>::operator-(const Vector<3>& p_vector) const
			{
				return Vector<3>(DirectX::XMVectorSubtract(*this, p_vector));
			}
			inline Vector<3> Vector<3>::operator*(float p_scale) const
			{
				return Vector<3>(DirectX::XMVectorScale(*this, p_scale));
			}
			inline Vector<3> Vector<3>::operator/(float p_scale) const
			{
				return operator*(1.0f / p_scale);
			}

			inline Vector<3>& Vector<3>::operator+=(const Vector<3>& p_rhs)
			{
				m_vectorArray[0] = DirectX::XMVectorAdd(*this, p_rhs);
				return *this;
			}
			inline Vector<3>& Vector<3>::operator-=(const Vector<3>& p_rhs)
			{
				m_vectorArray[0] = DirectX::XMVectorSubtract(*this, p_rhs);
				return *this;
			}
			inline Vector<3>& Vector<3>::operator*=(float p_scale)
			{
				m_vectorArray[0] = DirectX::XMVectorScale(*this, p_scale);
				return *this;
			}
			inline Vector<3>& Vector<3>::operator/=(float p_scale)
			{
				m_vectorArray[0] = DirectX::XMVectorScale(*this, 1.0f / p_scale);
				return *this;
			}

			inline Vector<3> Vector<3>::Normalize() const
			{
				return Vector<3>(DirectX::XMVector3Normalize(m_vectorArray[0]));
			}
			inline float Vector<3>::Magnitude() const
			{
				return DirectX::XMVectorGetX(DirectX::XMVector3Length(m_vectorArray[0]));
			}
			inline Vector<3> Vector<3>::Orthogonal() const
			{
				return Vector<3>(DirectX::XMVector3Orthogonal(*this));
			}

			inline Vector<3> Vector<3>::ClampLength(float minLength, float maxLength) const
			{
				return Vector<3>(DirectX::XMVector3ClampLength(*this, minLength, maxLength));
			}

			inline float Vector<3>::Dot(const Vector<3>& p_v) const
			{
				return DirectX::XMVectorGetX(DirectX::XMVector3Dot(*this, p_v));
			}
			inline Vector<3> Vector<3>::Cross(const Vector<3>& p_v) const
			{
				return Vector<3>(DirectX::XMVector3Cross(*this, p_v));
			}
			inline Vector<3> Vector<3>::Reflect(const NormalizedVector<3>& p_reflectionNormal) const
			{
				return Vector<3>(DirectX::XMVector3Reflect(*this, static_cast<Vector<3>>(p_reflectionNormal)));
			}
			inline Vector<3> Vector<3>::Refract(const NormalizedVector<3>& p_refractionNormal, float p_refractionIndex) const
			{
				return Vector<3>(DirectX::XMVector3Refract(*this, static_cast<Vector<3>>(p_refractionNormal), p_refractionIndex));
			}

			template<size_t index>
			inline float Vector<3>::GetFloatByIndex() const
			{
				static_assert(index < 3, "Invalid index given");
				return DirectX::XMVectorGetByIndex(m_vectorArray[0], index);
			}
			template<size_t index, size_t newVectorLength>
			inline Vector<newVectorLength> Vector<3>::SplatFloatByIndex() const
			{
				static_assert(index < 3, "Invalid index given");
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
			inline auto Vector<3>::GetXMVectors() const
				-> const Data::Storage::Array<DirectX::XMVECTOR, 1>&
			{
				return m_vectorArray;
			}
			inline auto Vector<3>::GetXMVectors()
				-> Data::Storage::Array<DirectX::XMVECTOR, 1>&
			{
				return m_vectorArray;
			}

			inline Vector<3> Vector<3>::MemberwiseMultiply(const Vector<3>& p_rhs) const
			{
				return Vector<3>(DirectX::XMVectorMultiply(*this, p_rhs));
			}

			inline void Vector<3>::Load(const Data::Storage::Array<float, 3>& p_array)
			{
				m_vectorArray[0] = DirectX::XMLoadFloat3(reinterpret_cast<const DirectX::XMFLOAT3*>(&p_array));
			}
			inline Data::Storage::Array<float, 3> Vector<3>::Unload() const
			{
				Data::Storage::Array<float, 3> returnValue;
				DirectX::XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(&returnValue), m_vectorArray[0]);
				return returnValue;
			}


			inline float Vector<3>::AngleBetween(const NormalizedVector<3>& vectorA, const NormalizedVector<3>& vectorB)
			{
				return DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenNormals(static_cast<Vector<3>>(vectorA), static_cast<Vector<3>>(vectorB)));
			}
			inline float Vector<3>::AngleBetween(const Vector<3>& vectorA, const Vector<3>& vectorB)
			{
				return DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenVectors(vectorA, vectorB));
			}
		}
	}
}