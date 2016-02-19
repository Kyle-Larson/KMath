#pragma once

#include "Vector.h"
#include "NormalizedVector.h"

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			inline Vector<2>::Vector() : m_vectorArray() {}
			inline Vector<2>::Vector(const Data::Storage::Array<float, 2>& p_array) :
				m_vectorArray({ DirectX::XMLoadFloat2(reinterpret_cast<const DirectX::XMFLOAT2*>(p_array.data())) }) {}
			inline Vector<2>::Vector(float fillValue) : m_vectorArray({ DirectX::XMVectorReplicate(fillValue) }) {}
			inline Vector<2>::Vector(float p_x, float p_y) : m_vectorArray({ DirectX::XMVectorSet(p_x, p_y, 0.0f, 1.0f) }) {}
			inline Vector<2>::Vector(const DirectX::FXMVECTOR p_vector) : m_vectorArray({ p_vector }) {}

			inline Vector<2>::operator DirectX::XMVECTOR() const
			{
				return m_vectorArray[0];
			}
			inline Vector<3> Vector<2>::ToVector3(float p_Z) const
			{
				DirectX::XMVECTOR newVec = m_vectorArray[0];
				DirectX::XMVectorSetZ(newVec, p_Z);
				return Vector<3>(newVec);
			}
			inline Vector<4> Vector<2>::ToVector4(float p_Z, float p_W) const
			{
				Data::Storage::Array<float, 2> ourVec = Unload();
				Data::Storage::Array<float, 4> theirVec;
				std::copy(ourVec.begin(), ourVec.end(), theirVec.begin());
				theirVec[2] = p_Z;
				theirVec[3] = p_W;
				return Vector<4>(theirVec);
			}

			inline Vector<2> Vector<2>::operator-() const
			{
				return Vector<2>(DirectX::XMVectorNegate(m_vectorArray[0]));
			}

			inline bool Vector<2>::operator==(const Vector<2>& p_rhs) const
			{
				return DirectX::XMVector2Equal(m_vectorArray[0], p_rhs);
			}
			inline bool Vector<2>::operator!=(const Vector<2>& p_rhs) const
			{
				return DirectX::XMVector2NotEqual(m_vectorArray[0], p_rhs);
			}

			inline Vector<2> Vector<2>::operator+(const Vector<2>& p_vector) const
			{
				return Vector<2>(DirectX::XMVectorAdd(*this, p_vector));
			}
			inline Vector<2> Vector<2>::operator-(const Vector<2>& p_vector) const
			{
				return Vector<2>(DirectX::XMVectorSubtract(*this, p_vector));
			}
			inline Vector<2> Vector<2>::operator*(float p_scale) const
			{
				return Vector<2>(DirectX::XMVectorScale(*this, p_scale));
			}
			inline Vector<2> Vector<2>::operator/(float p_scale) const
			{
				return operator*(1.0f / p_scale);
			}

			inline Vector<2>& Vector<2>::operator+=(const Vector<2>& p_rhs)
			{
				m_vectorArray[0] = DirectX::XMVectorAdd(*this, p_rhs);
				return *this;
			}
			inline Vector<2>& Vector<2>::operator-=(const Vector<2>& p_rhs)
			{
				m_vectorArray[0] = DirectX::XMVectorSubtract(*this, p_rhs);
				return *this;
			}
			inline Vector<2>& Vector<2>::operator*=(float p_scale)
			{
				m_vectorArray[0] = DirectX::XMVectorScale(*this, p_scale);
				return *this;
			}
			inline Vector<2>& Vector<2>::operator/=(float p_scale)
			{
				m_vectorArray[0] = DirectX::XMVectorScale(*this, 1.0f / p_scale);
				return *this;
			}

			inline Vector<2> Vector<2>::Normalize() const
			{
				return Vector<2>(DirectX::XMVector2Normalize(m_vectorArray[0]));
			}
			inline float Vector<2>::Magnitude() const
			{
				return DirectX::XMVectorGetX(DirectX::XMVector2Length(m_vectorArray[0]));
			}
			inline Vector<2> Vector<2>::Orthogonal() const
			{
				return Vector<2>(DirectX::XMVector2Orthogonal(*this));
			}
			inline Vector<2> Vector<2>::ClampLength(float minLength, float maxLength) const
			{
				return Vector<2>(DirectX::XMVector2ClampLength(*this, minLength, maxLength));
			}
			inline float Vector<2>::Dot(const Vector<2>& p_v) const
			{
				return DirectX::XMVectorGetX(DirectX::XMVector2Dot(*this, p_v));
			}
			inline float Vector<2>::Cross(const Vector<2>& p_v) const
			{
				return DirectX::XMVectorGetX(DirectX::XMVector2Cross(*this, p_v));
			}
			inline Vector<2> Vector<2>::Reflect(const NormalizedVector<2>& p_reflectionNormal) const
			{
				return Vector<2>(DirectX::XMVector2Reflect(*this, static_cast<Vector<2>>(p_reflectionNormal)));
			}
			inline Vector<2> Vector<2>::Refract(const NormalizedVector<2>& p_refractionNormal, float p_refractionIndex) const
			{
				return Vector<2>(DirectX::XMVector2Refract(*this, static_cast<Vector<2>>(p_refractionNormal), p_refractionIndex));
			}

			template<size_t index>
			inline float Vector<2>::GetFloatByIndex() const
			{
				static_assert(index < 2, "Invalid index given");
				return DirectX::XMVectorGetByIndex(m_vectorArray[0], index);
			}
			template<size_t index, size_t newVectorLength>
			inline Vector<newVectorLength> Vector<2>::SplatFloatByIndex() const
			{
				static_assert(index < 2, "Invalid index given");
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
			inline auto Vector<2>::GetXMVectors() const
				-> const Data::Storage::Array<DirectX::XMVECTOR, 1>&
			{
				return m_vectorArray;
			}
			inline auto Vector<2>::GetXMVectors()
				-> Data::Storage::Array<DirectX::XMVECTOR, 1>&
			{
				return m_vectorArray;
			}

			inline Vector<2> Vector<2>::MemberwiseMultiply(const Vector<2>& p_rhs) const
			{
				return Vector<2>(DirectX::XMVectorMultiply(*this, p_rhs));
			}

			inline void Vector<2>::Load(const Data::Storage::Array<float, 2>& p_array)
			{
				m_vectorArray[0] = DirectX::XMLoadFloat2(reinterpret_cast<const DirectX::XMFLOAT2*>(&p_array));
			}
			inline Data::Storage::Array<float, 2> Vector<2>::Unload() const
			{
				Data::Storage::Array<float, 2> returnValue;
				DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(&returnValue), m_vectorArray[0]);
				return returnValue;
			}


			inline float Vector<2>::AngleBetween(const NormalizedVector<2>& vectorA, const NormalizedVector<2>& vectorB)
			{
				return DirectX::XMVectorGetX(DirectX::XMVector2AngleBetweenNormals(static_cast<Vector<2>>(vectorA), static_cast<Vector<2>>(vectorB)));
			}
			inline float Vector<2>::AngleBetween(const Vector<2>& vectorA, const Vector<2>& vectorB)
			{
				return DirectX::XMVectorGetX(DirectX::XMVector2AngleBetweenVectors(vectorA, vectorB));
			}
		}
	}
}