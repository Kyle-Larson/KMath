#pragma once

#include "Vector.h"

#include <functional>
#include <numeric>
#include <malloc.h>

namespace KEngine
{
	namespace Math
	{
		namespace Coordinate
		{
			#pragma region Operator New
			template<size_t vectorLength>
			void* Vector<vectorLength>::operator new(std::size_t size)
			{
				return _aligned_malloc(size, XMVectorAlignment);
			}
			#pragma endregion

			#pragma region Operator New[]
			template<size_t vectorLength>
			void* Vector<vectorLength>::operator new[](std::size_t size)
			{
				return _aligned_malloc(size, XMVectorAlignment);
			}
			#pragma endregion

			#pragma region Operator Delete
			template<size_t vectorLength>
			void Vector<vectorLength>::operator delete(void* ptr, size_t size)
			{
				_aligned_free(ptr);
			}
			#pragma endregion

			#pragma region Operator Delete[]
			template<size_t vectorLength>
			void Vector<vectorLength>::operator delete[](void* ptr, std::size_t size)
			{
				_aligned_free(ptr);
			}
			#pragma endregion

			#pragma region Static Member Initialization
			template<size_t vectorLength>
			const Vector<vectorLength> Vector<vectorLength>::Zero = Vector<vectorLength>(0.0f);
			template<size_t vectorLength>
			const Vector<vectorLength> Vector<vectorLength>::One = Vector<vectorLength>(1.0f);

			template<size_t vectorLength>
			inline Vector<vectorLength>::Vector() : m_vectorArray() {}
			//MARK Constexpr++14
			template<size_t vectorLength>
			inline Vector<vectorLength>::Vector(const Data::Storage::Array<float, vectorLength>& p_array) : m_vectorArray()
			{
				constexpr size_t startLastIndex = (numXMVectors - 1) * 4;

				for (size_t i = 0; i < numXMVectors - 1; ++i)
				{
					m_vectorArray[i] = DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(&p_array[i * 4]));
				}
				switch (vectorLength % 4)
				{
				case 0:
					//Full array
					m_vectorArray[numXMVectors - 1] = DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(&p_array[startLastIndex]));
					break;
				case 1:
					//One float left
					m_vectorArray[numXMVectors - 1] = DirectX::XMLoadFloat(&p_array[startLastIndex]);
					break;
				case 2:
					//Two floats left
					m_vectorArray[numXMVectors - 1] = DirectX::XMLoadFloat2(reinterpret_cast<const DirectX::XMFLOAT2*>(&p_array[startLastIndex]));
					break;
				case 3:
					//Three floats left
					m_vectorArray[numXMVectors - 1] = DirectX::XMLoadFloat3(reinterpret_cast<const DirectX::XMFLOAT3*>(&p_array[startLastIndex]));
					break;
				}
			}
			template<size_t vectorLength>
			inline Vector<vectorLength>::Vector(float fillValue) : m_vectorArray()
			{
				for (auto& vector : m_vectorArray)
				{
					vector = DirectX::XMVectorReplicate(fillValue);
				}
			}
			
			template<size_t vectorLength>
			inline Vector<vectorLength> Vector<vectorLength>::operator-() const
			{
				Vector<vectorLength> returnVector;
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					returnVector.m_vectorArray[i] = DirectX::XMVectorNegate(m_vectorArray[i]);
				}
				return returnVector;
			}
			
			template<size_t vectorLength>
			inline bool Vector<vectorLength>::operator==(const Vector<vectorLength>& p_rhs) const
			{
				Data::Storage::Array<DirectX::XMVECTOR, numXMVectors> resultArray;
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					resultArray[i] = DirectX::XMVectorEqual(m_vectorArray[i], p_rhs.m_vectorArray[i]);
				}
				for (size_t i = 1; i < numXMVectors - 1; ++i)
				{
					resultArray[0] = DirectX::XMVectorAndInt(resultArray[0], resultArray[i]);
				}
				bool currentResult = DirectX::XMVector4EqualInt(resultArray[0], DirectX::XMVectorTrueInt());
				switch (vectorLength % 4)
				{
				default:
					return currentResult && DirectX::XMVector4EqualInt(resultArray[numXMVectors - 1], DirectX::XMVectorTrueInt());
					break;
				case 1:
					return currentResult && DirectX::XMVectorGetIntX(resultArray[numXMVectors - 1]);
					break;
				case 2:
					return currentResult && DirectX::XMVector2EqualInt(resultArray[numXMVectors - 1], DirectX::XMVectorTrueInt());
					break;
				case 3:
					return currentResult && DirectX::XMVector3EqualInt(resultArray[numXMVectors - 1], DirectX::XMVectorTrueInt());
					break;
				}
			}
			template<size_t vectorLength>
			inline bool Vector<vectorLength>::operator!=(const Vector<vectorLength>& p_rhs) const
			{
				return !operator==(p_rhs);
				/*Data::Storage::Array<DirectX::XMVECTOR, numXMVectors> resultArray;
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					resultArray[i] = DirectX::XMVectorNotEqual(m_vectorArray[i], p_rhs.m_vectorArray[i]);
				}
				for (size_t i = 1; i < numXMVectors - 1; ++i)
				{
					resultArray[0] = DirectX::XMVectorOrInt(resultArray[0], resultArray[i]);
				}
				bool currentResult = DirectX::XMVector4EqualInt(resultArray[0], DirectX::XMVectorTrueInt());
				switch (vectorLength % 4)
				{
				default:
					return currentResult && DirectX::XMVector4EqualInt(resultArray[numXMVectors - 1], DirectX::XMVectorTrueInt());
					break;
				case 1:
					return currentResult && DirectX::XMVectorGetIntX(resultArray[numXMVectors - 1]);
					break;
				case 2:
					return currentResult && DirectX::XMVector2EqualInt(resultArray[numXMVectors - 1], DirectX::XMVectorTrueInt());
					break;
				case 3:
					return currentResult && DirectX::XMVector3EqualInt(resultArray[numXMVectors - 1], DirectX::XMVectorTrueInt());
					break;
				}*/
			}

			template<size_t vectorLength>
			inline Vector<vectorLength> Vector<vectorLength>::operator+(const Vector<vectorLength>& p_v) const
			{
				Vector<vectorLength> returnVector;
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					returnVector.m_vectorArray[i] = DirectX::XMVectorAdd(m_vectorArray[i], p_v.m_vectorArray[i]);
				}
				return returnVector;
			}
			template<size_t vectorLength>
			inline Vector<vectorLength> Vector<vectorLength>::operator-(const Vector<vectorLength>& p_v) const
			{
				Vector<vectorLength> returnVector;
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					returnVector.m_vectorArray[i] = DirectX::XMVectorSubtract(m_vectorArray[i], p_v.m_vectorArray[i]);
				}
				return returnVector;
			}
			template<size_t vectorLength>
			inline Vector<vectorLength> Vector<vectorLength>::operator*(float p_scale) const
			{
				Vector<vectorLength> returnVector;
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					returnVector.m_vectorArray[i] = DirectX::XMVectorScale(m_vectorArray[i], p_scale);
				}
				return returnVector;
			}
			template<size_t vectorLength>
			inline Vector<vectorLength> Vector<vectorLength>::operator/(float p_scale) const
			{
				return operator*(1.0f / p_scale);
			}
			
			template<size_t vectorLength>
			inline Vector<vectorLength>& Vector<vectorLength>::operator+=(const Vector<vectorLength>& p_v)
			{
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					m_vectorArray[i] = DirectX::XMVectorAdd(m_vectorArray[i], p_v.m_vectorArray[i]);
				}
				return *this;
			}
			template<size_t vectorLength>
			inline Vector<vectorLength>& Vector<vectorLength>::operator-=(const Vector<vectorLength>& p_v)
			{
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					m_vectorArray[i] = DirectX::XMVectorSubtract(m_vectorArray[i], p_v.m_vectorArray[i]);
				}
				return *this;
			}
			template<size_t vectorLength>
			inline Vector<vectorLength>& Vector<vectorLength>::operator*=(float p_scale)
			{
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					m_vectorArray[i] = DirectX::XMVectorScale(m_vectorArray[i], p_scale);
				}
				return *this;
			}
			template<size_t vectorLength>
			inline Vector<vectorLength>& Vector<vectorLength>::operator/=(float p_scale)
			{
				return operator*=(1.0f / p_scale);
			}
			
			template<size_t vectorLength>
			inline Vector<vectorLength> Vector<vectorLength>::Normalize() const
			{
				assert(Magnitude() > 0.0f);	//Cannot normalize a vector of length Zero.
				Vector<vectorLength> returnVector;
				float scale = 1.0f / Magnitude();
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					returnVector.m_vectorArray[i] = DirectX::XMVectorScale(m_vectorArray[i], scale);
				}
				return returnVector;
			}
			template<size_t vectorLength>
			inline float Vector<vectorLength>::Magnitude() const
			{
				return sqrtf(Dot(*this));
			}
			template<size_t vectorLength>
			inline float Vector<vectorLength>::Dot(const Vector<vectorLength>& p_v) const
			{
				Data::Storage::Array<float, numXMVectors> dotProductStorage;
				for (size_t i = 0; i < numXMVectors - 1; ++i)
				{
					dotProductStorage[i] = DirectX::XMVectorGetX(DirectX::XMVector4Dot(m_vectorArray[i], p_v.m_vectorArray[i]));
				}
				constexpr size_t lastIndex = numXMVectors - 1;
				switch (vectorLength % 4)
				{
				case 0:
					dotProductStorage[lastIndex] = DirectX::XMVectorGetX(DirectX::XMVector4Dot(m_vectorArray[lastIndex], p_v.m_vectorArray[lastIndex]));
					break;
				case 1:
					dotProductStorage[lastIndex] = DirectX::XMVectorGetX(DirectX::XMVectorMultiply(m_vectorArray[lastIndex], p_v.m_vectorArray[lastIndex]));
					break;
				case 2:
					dotProductStorage[lastIndex] = DirectX::XMVectorGetX(DirectX::XMVector2Dot(m_vectorArray[lastIndex], p_v.m_vectorArray[lastIndex]));
					break;
				case 3:
					dotProductStorage[lastIndex] = DirectX::XMVectorGetX(DirectX::XMVector3Dot(m_vectorArray[lastIndex], p_v.m_vectorArray[lastIndex]));
					break;
				}
				return std::accumulate(dotProductStorage.begin(), dotProductStorage.end(), 0.0f);
			}
			
			template<size_t vectorLength>
			template<size_t index>
			inline float Vector<vectorLength>::GetFloatByIndex() const
			{
				static_assert(index < vectorLength, "Invalid index to access!");
				return DirectX::XMVectorGetByIndex(m_vectorArray[index / 4], index % 4);
			}
			template<size_t vectorLength>
			template<size_t index, size_t newVectorLength>
			Vector<newVectorLength> Vector<vectorLength>::SplatFloatByIndex() const
			{
				static_assert(index < vectorLength, "Invalid index to access vector!");
				Vector<newVectorLength> returnVector;
				DirectX::XMVECTOR splatVector;
				switch (index % 4)
				{
				case 0:
					splatVector = DirectX::XMVectorSplatX(m_vectorArray[index / 4]);
					break;
				case 1:
					splatVector = DirectX::XMVectorSplatY(m_vectorArray[index / 4]);
					break;
				case 2:
					splatVector = DirectX::XMVectorSplatZ(m_vectorArray[index / 4]);
					break;
				case 3:
					splatVector = DirectX::XMVectorSplatW(m_vectorArray[index / 4]);
					break;
				}
				auto& vecArrayRef = returnVector.GetXMVectors();
				for (auto& vector : vecArrayRef)
				{
					vector = splatVector;
				}
				return returnVector;
			}
			template<size_t vectorLength>
			inline auto Vector<vectorLength>::GetXMVectors() const
				-> const Data::Storage::Array<DirectX::XMVECTOR, numXMVectors>&
			{
				return m_vectorArray;
			}
			template<size_t vectorLength>
			inline auto Vector<vectorLength>::GetXMVectors() 
				-> Data::Storage::Array<DirectX::XMVECTOR, numXMVectors>& 
			{
				return m_vectorArray;
			}
			
			template<size_t vectorLength>
			Vector<vectorLength> Vector<vectorLength>::MemberwiseMultiply(const Vector<vectorLength>& p_rhs) const
			{
				Vector<vectorLength> returnVector;
				auto& xmVectors = returnVector.GetXMVectors();
				for (size_t i = 0; i < numXMVectors; ++i)
				{
					xmVectors[i] = DirectX::XMVectorMultiply(m_vectorArray[i], p_rhs.m_vectorArray[i]);
				}
				return returnVector;
			}
			
			template<size_t vectorLength>
			inline void Vector<vectorLength>::Load(const KEngine::Data::Storage::Array<float, vectorLength>& p_array)
			{
				constexpr size_t startLastIndex = (numXMVectors - 1) * 4;

				for (size_t i = 0; i < numXMVectors - 1; ++i)
				{
					m_vectorArray[i] = DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(&p_array[i * 4]));
				}
				switch (vectorLength % 4)
				{
				case 0:
					//Full array
					m_vectorArray[numXMVectors - 1] = DirectX::XMLoadFloat4(reinterpret_cast<const DirectX::XMFLOAT4*>(&p_array[startLastIndex]));
					break;
				case 1:
					//One float left
					m_vectorArray[numXMVectors - 1] = DirectX::XMLoadFloat(&p_array[startLastIndex]);
					break;
				case 2:
					//Two floats left
					m_vectorArray[numXMVectors - 1] = DirectX::XMLoadFloat2(reinterpret_cast<const DirectX::XMFLOAT2*>(&p_array[startLastIndex]));
					break;
				case 3:
					//Three floats left
					m_vectorArray[numXMVectors - 1] = DirectX::XMLoadFloat3(reinterpret_cast<const DirectX::XMFLOAT3*>(&p_array[startLastIndex]));
					break;
				}
			}
			template<size_t vectorLength>
			inline KEngine::Data::Storage::Array<float, vectorLength> Vector<vectorLength>::Unload() const
			{
				constexpr size_t lastIndex = numXMVectors - 1;
				Data::Storage::Array<float, vectorLength> dataContainer;
				for (size_t i = 0; i < numXMVectors - 1; ++i)
				{
					DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&dataContainer[i * 4]), m_vectorArray[i]);
				}
				switch (vectorLength % 4)
				{
				case 0:
					DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(&dataContainer[lastIndex * 4]), m_vectorArray[lastIndex]);
					break;
				case 1:
					DirectX::XMStoreFloat(&dataContainer[lastIndex * 4], m_vectorArray[lastIndex]);
					break;
				case 2:
					DirectX::XMStoreFloat2(reinterpret_cast<DirectX::XMFLOAT2*>(&dataContainer[lastIndex * 4]), m_vectorArray[lastIndex]);
					break;
				case 3:
					DirectX::XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(&dataContainer[lastIndex * 4]), m_vectorArray[lastIndex]);
					break;
				}
				return dataContainer;
			}
		}
	}
}